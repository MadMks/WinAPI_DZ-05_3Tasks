#include <windows.h>
#include <tchar.h>
#include "resource.h"
using namespace std;

HWND hComboBox;
HINSTANCE hInstance;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{

	MSG msg;
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_Main), NULL, DlgProc);
	ShowWindow(hDialog, nCmdShow);

	hInstance = hInst;

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



BOOL CALLBACK DlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR szElements[5][10] =
	{
		L"BUTTON", L"EDIT", L"LISTBOX", L"COMBOBOX", L"STATIC"
	};
	TCHAR szSelectElement[10];

	switch (uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:

		hComboBox = GetDlgItem(hWnd, IDC_COMBO);

		for (int i = 0; i < 5; i++)
		{
			SendMessage(hComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)szElements[i]);
		}
		SendMessage(hComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

		return TRUE;

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BUTTON_Create)
		{
			int iNumberElement = SendMessage(hComboBox, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			switch (iNumberElement)
			{
			case 0:
				CreateWindowEx(WS_EX_DLGMODALFRAME,
					szElements[iNumberElement], L"Button",
					WS_CHILD | WS_VISIBLE,
					50, 50, 70, 25,
					hWnd, 0, hInstance, 0);
				break;
			case 1:
				CreateWindowEx(WS_EX_CLIENTEDGE,
					szElements[iNumberElement], L"Edit",
					WS_CHILD | WS_VISIBLE,
					150, 50, 70, 25,
					hWnd, 0, hInstance, 0);
				break;
			case 2:
				CreateWindowEx(WS_EX_CLIENTEDGE,
					szElements[iNumberElement], 0,
					WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOTIFY,
					200, 50, 70, 50,
					hWnd, 0, hInstance, 0);
				break;
			case 3:
				CreateWindowEx(WS_EX_CLIENTEDGE,
					szElements[iNumberElement], 0,
					WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOTIFY | CBS_DROPDOWNLIST,
					250, 50, 70, 25,
					hWnd, 0, hInstance, 0);
				break;
			case 4:
				CreateWindowEx(WS_EX_CLIENTEDGE,
					szElements[iNumberElement], L"Static",
					WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER,
					300, 50, 70, 25,
					hWnd, 0, hInstance, 0);
				break;
			default:
				break;
			}

			/*hEdit1 = *//*CreateWindowEx(0,
				szElements[iNumberElement], 0, WS_CHILD | WS_VISIBLE,
				50, 50, 100, 50,
				hWnd, 0, hInstance, 0);*/
		}
		else if (LOWORD(wParam) == IDC_BUTTON_Delete)
		{

		}

		return TRUE;

	}
	return FALSE;
}