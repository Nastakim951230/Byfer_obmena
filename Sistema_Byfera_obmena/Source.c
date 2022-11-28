#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <strsafe.h>
LPWSTR ClipboardOutputText();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR pCmdLine, int nCmdShow)
{
	while (TRUE)
	{
		LPSTR Data = ClipboardOutputText();
	
		TCHAR Alert[] = L"Вы нарушали Авторские права, скопировав следующий текс: ";
		TCHAR third[512];
		swprintf(third, sizeof third, L"%s%s", Alert, Data);
		if (*Data != 0)
		{
			MessageBoxW(NULL, &third, L"Внимание!! Нарушение!!", MB_OK | MB_ICONWARNING);
			ClipboardInputText("");
		}
		Sleep(1000);
	}
	return 0;
}

TCHAR* Text(LPSTR Data)
{
	// Массив со строкой для поиска
	char str[512] = Data;
	// Набор символов, которые должны входить в искомый сегмент
	char sep[512] = " ";
	// Переменная, в которую будут заноситься начальные адреса частей
	// строки str
	char* istr;

	// Выделение первой части строки
	istr = strtok(str, sep);

	// Выделение последующих частей
	while (istr != NULL)
	{
		char str[512] = istr;
		// Набор символов, которые должны входить в искомый сегмент
		char sep[512] = "/0";
		
		
		// Выделение очередной части строки
		istr = strtok(NULL, sep);
	}
	
	
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

TCHAR* ClipboardOutputText()
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