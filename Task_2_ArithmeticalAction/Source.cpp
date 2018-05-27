#include <windows.h>
#include <tchar.h>
#include <time.h>
#include "resource.h"
using namespace std;

#define AMOUNT_OF_NUMBERS_START 2
#define AMOUNT_OF_NUMBERS_STOP 4
#define RANGE_OF_NUMBERS_START 1
#define RANGE_OF_NUMBERS_STOP 5

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
	TCHAR szAnswerNumber[6];
	int dResult = 0;	// TODO double

	switch (uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:

		hList = GetDlgItem(hWnd, IDC_LIST);
		hAnswer = GetDlgItem(hWnd, IDC_EDIT_Answer);
		//if (!hList)
		//{
		//	MessageBox(hWnd, L"error", L"error", MB_OK);	// TODO delete
		//}
		/*SendDlgItemMessage(hWnd, IDC_RADIO_SumOfNumbers, BM_SETCHECK, WPARAM(BST_CHECKED), 0);*/
		SetWindowText(hAnswer, L"Выберите одно из действий.");
		return TRUE;

	case WM_COMMAND:

		//TCHAR szAnswerNumber[6];

		if (LOWORD(wParam) == IDC_BUTTON_Start)
		{

			SendMessage(hList, LB_RESETCONTENT, 0, 0);

			TCHAR szTextNumber[5];
			int amountOfNumbers 
				= rand() % (AMOUNT_OF_NUMBERS_STOP - AMOUNT_OF_NUMBERS_START + 1)
				+ AMOUNT_OF_NUMBERS_START;
			//int amountOfNumbers = rand() % (8 - 3) + 3;
			// рандомное кол-во чисел

			// рандомных чисел
			int randNumber;
			for (int i = 0; i < amountOfNumbers; i++)
			{
				randNumber = rand() % (RANGE_OF_NUMBERS_STOP - RANGE_OF_NUMBERS_START + 1)
					+ RANGE_OF_NUMBERS_START;

				_itow(randNumber, szTextNumber, 10);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)szTextNumber);
			}

			/*_itow(randNumber, szTextNumber, 10);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)szTextNumber);*/

			//SendDlgItemMessage(hWnd, IDC_RADIO_SumOfNumbers, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
			LRESULT result = SendDlgItemMessage(hWnd, IDC_RADIO_SumOfNumbers, BM_GETCHECK, 0, 0);
			if (result == BST_CHECKED)
			{
				// repeat
				int length = SendMessage(hList, LB_GETCOUNT, 0, 0);
				for (int i = 0; i < length; i++)
				{

					TCHAR number[5];
					SendMessage(hList, LB_GETTEXT, i, (LPARAM)number);
					dResult += _wtoi(number);
				}
				_itow(dResult, szAnswerNumber, 10);
			}
			else
			{
				result = SendDlgItemMessage(hWnd, IDC_RADIO_ProductOfNumbers, BM_GETCHECK, 0, 0);
				if (result == BST_CHECKED)
				{

				}
				else
				{
					result = SendDlgItemMessage(hWnd, IDC_RADIO_Average, BM_GETCHECK, 0, 0);
					if (result == BST_CHECKED)
					{

					}
				}
			}

			SetWindowText(hAnswer, szAnswerNumber);
			
		}
		else if (LOWORD(wParam) >= IDC_RADIO_SumOfNumbers &&
			LOWORD(wParam) <= IDC_RADIO_Average)
		{
			//TCHAR szAnswerNumber[6];
			//int dResult = 0;	// TODO double

			if (LOWORD(wParam) == IDC_RADIO_SumOfNumbers)
			{
				// считаю
				// гет из списка все
				// плюсуем их
				
				// repeat
				int length = SendMessage(hList, LB_GETCOUNT, 0, 0);
				for (int i = 0; i < length; i++)
				{
					
					TCHAR number[5];
					SendMessage(hList, LB_GETTEXT, i, (LPARAM)number);
					dResult += _wtoi(number);
				}
				_itow(dResult, szAnswerNumber, 10);
				//SendMessage(hList, LB_GETTEXT, 0, (LPARAM)szAnswerNumber);
			}
			else if (LOWORD(wParam) == IDC_RADIO_ProductOfNumbers)
			{

			}
			else if (LOWORD(wParam) == IDC_RADIO_Average)
			{

			}

			// из числа дабл в строку
			// строку в едит
			//SetWindowText(hAnswer, (LPCWSTR)szAnswerNumber);
			SetWindowText(hAnswer, szAnswerNumber);
		}

		

		return TRUE;

	}
	return FALSE;
}