#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

int ClipboardInputText(LPWSTR buffer);
int ClipboardOutptText();

TCHAR* ClipboardOutptText2();


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR pCmdLine, int nCmdShow)
{
	//while (TRUE)
	//{
	//	LPSTR Data = ClipboardOutputText();
	//
	//	TCHAR Alert[] = L"Вы нарушали Авторские права, скопировав следующий текс: ";
	//	TCHAR third[512];
	//	swprintf(third, sizeof third, L"%s%s", Alert, Data);
	//	if (*Data != 0)
	//	{
	//		MessageBoxW(NULL, &third, L"Внимание!! Нарушение!!", MB_OK | MB_ICONWARNING);
	//		ClipboardInputText("");
	//	}
	//	Sleep(1000);
	//}

	while (TRUE)
	{
		LPSTR Data = ClipboardOutptText2();
		
		if (*Data != 0)
		{
			switch (*Data)
			{
			case '0':
				ClipboardInputText(L"ноль");
				break;
			case '1':
				ClipboardInputText(L"один");
				break;
			case '2':
				ClipboardInputText(L"два");
				break;
			case '3':
				ClipboardInputText(L"три");
				break;
			case '4':
				ClipboardInputText(L"четыре");
				break;
			case '5':
				ClipboardInputText(L"пять");
				break;
			case '6':
				ClipboardInputText(L"шесть");
				break;
			case '7':
				ClipboardInputText(L"семь");
				break;
			case '8':
				ClipboardInputText(L"восемь");
				break;
			case '9':
				ClipboardInputText(L"девять");
				break;
			default:
				ClipboardInputText(Data);
				break;
			}
		}
		Sleep(1000);
	}
	return 0;

}



TCHAR* ClipboardOutptText2()
{
	TCHAR* Mess = NULL;
	OpenClipboard(NULL);
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	Mess = (TCHAR*)GlobalLock(hClipboardData);
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	//EmptyClipboard();
	return Mess;
}


int ClipboardInputText(LPWSTR buffer)
{
	DWORD len;
	HANDLE hMen;
	len = wcslen(buffer) + 1;//определение длины строки в формате юникода
	hMen = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));//выделение памяти в глобальной области вилимости
	memcpy(GlobalLock(hMen),buffer, len * sizeof(LPWSTR));//копирование области памяти из buffer в hMen
	GlobalUnlock(hMen);//разблокировка содержимое этой памяти (сделать доступным для других программ)
	OpenClipboard(0);//открыть буфер обмена 
	EmptyClipboard();//очистить буфер обмена
	SetClipboardData(CF_UNICODETEXT, hMen);//записать в буфур обмена данные соответствующего типа
	CloseClipboard();//закрыть буферб сделать его доступным для других приложений
	return 0;

}

int* ClipboardOutputText()
{
	TCHAR* Mess = NULL;
	OpenClipboard(NULL);//открыть буфер обмена 
	HANDLE hClipboardDate = GetClipboardData(CF_UNICODETEXT);//записать в буфер данные соответствующего типа
	Mess = (TCHAR*)GlobalLock(hClipboardDate);// Считать тз глобального участка память, привести это все к строке
	GlobalUnlock(hClipboardDate);//Освободить глобальных участок памяти 
	CloseClipboard();//Закрытие буфера, сделать его доступным для других приложений
	EmptyClipboard();//очистить буфер
	return Mess;
}