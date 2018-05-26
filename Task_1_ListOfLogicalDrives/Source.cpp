#include <windows.h>
#include <tchar.h>
#include "resource.h"
using namespace std;

HWND hComboBox;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{

	MSG msg;
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_Main), NULL, DlgProc);
	ShowWindow(hDialog, nCmdShow);


	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



BOOL CALLBACK DlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	int mask;
	TCHAR drive[25];
	DWORD dr;

	switch (uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:

		hComboBox = GetDlgItem(hWnd, IDC_COMBO_ListDrives);

		dr = GetLogicalDrives();
		for (int i = 0; i < 26; i++)
		{
			mask = ((dr >> i) & 0x00000001);
			if (mask == 1)
			{
				drive[0] = 0;

				drive[0] = char(65 + i);
				drive[1] = ':';
				drive[2] = '\\';
				drive[3] = 0;

				int driveType = GetDriveType(drive);
				switch (driveType)
				{
				case DRIVE_UNKNOWN:
					lstrcat(drive, L" (Неизвестный тип накопителя)");
					break;
				case DRIVE_REMOVABLE:
					lstrcat(drive, L" (Съемный диск)");
					break;
				case DRIVE_FIXED:
					lstrcat(drive, L" (Жесткий диск)");
					break;
				case DRIVE_REMOTE:
					lstrcat(drive, L" (Сетевой диск)");
					break;
				case DRIVE_CDROM:
					lstrcat(drive, L" (Компакт-диск)");
					break;
				case DRIVE_RAMDISK:
					lstrcat(drive, L" (Виртуальный диск)");
					break;
				default:
					break;
				}

				SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)drive);
			}
		}

		SendMessage(hComboBox, CB_SETCURSEL, 0, 0L);

		return TRUE;


	}
	return FALSE;
}