#include <windows.h>
#include <tchar.h>
#include <time.h>
#include "resource.h"
using namespace std;

#define AMOUNT_OF_NUMBERS_START 10
#define AMOUNT_OF_NUMBERS_STOP 20
#define RANGE_OF_NUMBERS_START -10
#define RANGE_OF_NUMBERS_STOP 10

HWND hList, hAnswer;


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	srand(time(NULL));

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
	TCHAR szAnswerNumber[25];
	int dResult = 0;

	switch (uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:

		hList = GetDlgItem(hWnd, IDC_LIST);
		hAnswer = GetDlgItem(hWnd, IDC_EDIT_Answer);

		SetWindowText(hAnswer, L"Выберите одно из действий.");

		return TRUE;

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BUTTON_Start)
		{

			SendMessage(hList, LB_RESETCONTENT, 0, 0);

			TCHAR szTextNumber[5];
			// Рандомное кол-во чисел.
			int amountOfNumbers 
				= rand() % (AMOUNT_OF_NUMBERS_STOP - AMOUNT_OF_NUMBERS_START + 1)
				+ AMOUNT_OF_NUMBERS_START;

			// Рандомных чисел.
			int randNumber;
			for (int i = 0; i < amountOfNumbers; i++)
			{
				randNumber = rand() % (RANGE_OF_NUMBERS_STOP - RANGE_OF_NUMBERS_START + 1)
					+ RANGE_OF_NUMBERS_START;

				if (randNumber != 0)
				{
					_itow(randNumber, szTextNumber, 10);
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)szTextNumber);
				}
			}


			LRESULT result;
			
			// Считаем при нажатии на "Старт" (новые числа).
			int length = SendMessage(hList, LB_GETCOUNT, 0, 0);
			for (int i = 0; i < length; i++)
			{

				TCHAR number[5];
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)number);
				result = SendDlgItemMessage(hWnd, IDC_RADIO_SumOfNumbers, BM_GETCHECK, 0, 0);
				if (result == BST_CHECKED)
				{
					dResult += _wtoi(number);
				}
				else
				{
					result = SendDlgItemMessage(hWnd, IDC_RADIO_ProductOfNumbers, BM_GETCHECK, 0, 0);
					if (result == BST_CHECKED)
					{
						if (dResult == 0)
						{
							dResult = 1;
						}
						dResult *= _wtoi(number);
					}
					else
					{
						result = SendDlgItemMessage(hWnd, IDC_RADIO_Average, BM_GETCHECK, 0, 0);
						if (result == BST_CHECKED)
						{
							dResult += _wtoi(number);
							if (i == length - 1)
							{
								dResult /= length;
							}
						}
					}
				}
			}
			//_itow(dResult, szAnswerNumber, 10);
			_itot(dResult, szAnswerNumber, 10);
			

			SetWindowText(hAnswer, szAnswerNumber);
			
		}
		else if (LOWORD(wParam) >= IDC_RADIO_SumOfNumbers &&
			LOWORD(wParam) <= IDC_RADIO_Average)
		{
			// Считаем при изменении выбора радиоБаттон.
			int length = SendMessage(hList, LB_GETCOUNT, 0, 0);
			for (int i = 0; i < length; i++)
			{

				TCHAR number[5];
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)number);

				if (LOWORD(wParam) == IDC_RADIO_SumOfNumbers)
				{
					dResult += _wtoi(number);
				}
				else if (LOWORD(wParam) == IDC_RADIO_ProductOfNumbers)
				{
					if (dResult == 0)
					{
						dResult = 1;
					}
					dResult *= _wtoi(number);
				}
				else if (LOWORD(wParam) == IDC_RADIO_Average)
				{
					dResult += _wtoi(number);
					if (i == length - 1)
					{
						dResult /= length;
					}
				}
			}
			_itot(dResult, szAnswerNumber, 10);

			SetWindowText(hAnswer, szAnswerNumber);
		}

		

		return TRUE;

	}
	return FALSE;
}