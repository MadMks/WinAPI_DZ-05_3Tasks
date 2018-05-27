#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
#include <time.h>
using namespace std;

#define WIDTH_OF_ELEMENTS 70
#define HEIGHT_OF_ELEMENTS 50
#define INDENT_FOR_CONTROL_ELEMENTS 50

HWND hComboBox;
HINSTANCE hInstance;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	srand(time(NULL));

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
	static TCHAR szElements[5][10] =
	{
		L"BUTTON", L"EDIT", L"LISTBOX", L"COMBOBOX", L"STATIC"
	};
	TCHAR szSelectElement[10];
	static vector<HWND> aButtons,
		aEdits,
		aListBox,
		aComboBox,
		aStatics;
	static RECT rcClientRect;

	switch (uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:

		hComboBox = GetDlgItem(hWnd, IDC_COMBO);
		GetClientRect(hWnd, &rcClientRect);

		for (int i = 0; i < 5; i++)
		{
			SendMessage(hComboBox, CB_ADDSTRING, (WPARAM)0, (LPARAM)szElements[i]);
		}
		SendMessage(hComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

		return TRUE;

	case WM_COMMAND:

		// Create
		if (LOWORD(wParam) == IDC_BUTTON_Create)
		{
			int nRandLeft = rand() % (rcClientRect.right - WIDTH_OF_ELEMENTS);
			int nRandTop = rand() 
				% (rcClientRect.bottom - HEIGHT_OF_ELEMENTS - INDENT_FOR_CONTROL_ELEMENTS)
				+ INDENT_FOR_CONTROL_ELEMENTS;

			int iNumberElement = SendMessage(hComboBox, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			switch (iNumberElement)
			{
			case 0:
				aButtons.push_back(
					CreateWindowEx(WS_EX_DLGMODALFRAME,
						szElements[iNumberElement], L"Button",
						WS_CHILD | WS_VISIBLE,
						nRandLeft, nRandTop, WIDTH_OF_ELEMENTS, HEIGHT_OF_ELEMENTS,
						hWnd, 0, hInstance, 0)
				);
				break;
			case 1:
				aEdits.push_back(
					CreateWindowEx(WS_EX_CLIENTEDGE,
						szElements[iNumberElement], L"Edit",
						WS_CHILD | WS_VISIBLE,
						nRandLeft, nRandTop, WIDTH_OF_ELEMENTS, HEIGHT_OF_ELEMENTS,
						hWnd, 0, hInstance, 0)
				);
				break;
			case 2:
				aListBox.push_back(
					CreateWindowEx(WS_EX_CLIENTEDGE,
						szElements[iNumberElement], 0,
						WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOTIFY,
						nRandLeft, nRandTop, WIDTH_OF_ELEMENTS, HEIGHT_OF_ELEMENTS,
						hWnd, 0, hInstance, 0)
				);
				break;
			case 3:
				aComboBox.push_back(
					CreateWindowEx(WS_EX_CLIENTEDGE,
						szElements[iNumberElement], 0,
						WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOTIFY | CBS_DROPDOWNLIST,
						nRandLeft, nRandTop, WIDTH_OF_ELEMENTS, HEIGHT_OF_ELEMENTS,
						hWnd, 0, hInstance, 0)
				);
				break;
			case 4:
				aStatics.push_back(
					CreateWindowEx(WS_EX_CLIENTEDGE,
						szElements[iNumberElement], L"Static",
						WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER,
						nRandLeft, nRandTop, WIDTH_OF_ELEMENTS, HEIGHT_OF_ELEMENTS,
						hWnd, 0, hInstance, 0)
				);
				break;
			default:
				break;
			}
		}
		// Delete
		else if (LOWORD(wParam) == IDC_BUTTON_Delete)
		{
			int iNumberElement = SendMessage(hComboBox, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			switch (iNumberElement)
			{
			case 0:
				if (!aButtons.empty())
				{
					DestroyWindow(aButtons.back());
					aButtons.pop_back();
				}
				break;
			case 1:
				if (!aEdits.empty())
				{
					DestroyWindow(aEdits.back());
					aEdits.pop_back();
				}
				break;
			case 2:
				if (!aListBox.empty())
				{
					DestroyWindow(aListBox.back());
					aListBox.pop_back();
				}
				break;
			case 3:
				if (!aComboBox.empty())
				{
					DestroyWindow(aComboBox.back());
					aComboBox.pop_back();
				}
				break;
			case 4:
				if (!aStatics.empty())
				{
					DestroyWindow(aStatics.back());
					aStatics.pop_back();
				}
				break;
			default:
				break;
			}
		}

		return TRUE;

	}
	return FALSE;
}