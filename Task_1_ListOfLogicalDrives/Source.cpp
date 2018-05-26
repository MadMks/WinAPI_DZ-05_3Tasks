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
	/*TCHAR drive_letter;
	int mask;
	DWORD dr;*/

	int n;
	TCHAR dd[10];
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
			n = ((dr >> i) & 0x00000001);
			if (n == 1)
			{
				//dd[0] = L'\0';

				dd[0] = char(65 + i);
				dd[1] = ':';
				dd[2] = '\\';
				dd[3] = 0;
				//int d = GetDriveType(lstrcat(dd, L"\\"));
				int d = GetDriveType(dd);
				switch (d)
				{
				case DRIVE_FIXED:
					//lstrcat(dd, L" (f)");
					break;
				case 2:
					//lstrcat(dd, L" (f)");
					break;
				default:
					lstrcat(dd, L" (n)");
					break;
				}
				//dd[3] = 0;
				SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)dd);

				
			}
		}
		//dr = GetLogicalDrives();
		//for (int i = 0; i < 26; i++)
		//{
		//	mask = ((dr >> i) & 1);
		//	if (mask)
		//	{
		//		char dl = char((char)(65 + i)); // получаем литеру диска
		//		//TCHAR path = TCHAR((char)(65 + x)) + ":\\";

		//		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)dl);
		//	}
		//}
		

		return TRUE;

	case WM_COMMAND:

		return TRUE;


	}
	return FALSE;
}

// проверка кодировки