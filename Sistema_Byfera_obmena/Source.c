#define _CRT_SECURE_NO_WARNINGS


#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ClipboardInputText(LPWSTR buffer);
int ClipboardOutptText();
TCHAR* ClipboardOutptText2();
char* my_strcat(char* destination, const char* source);

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
	
	LPSTR Data = ClipboardOutptText2();

	ClipboardInputText(Data);	
	Sleep(100000);
	return 0;
}

char* my_strcat(char* destination, const char* source)
{
	// делаем так, чтобы `ptr` указывал на конец строки назначения
	char* ptr = destination + strlen(destination);

	// добавляет символы источника к строке назначения
	while (*source != '\0') {
		*ptr++ = *source++;
	}

	// нулевая завершающая строка назначения
	*ptr = '\0';

	// пункт назначения возвращается стандартной функцией `strcat()`
	return destination;
}

TCHAR* ClipboardOutptText2()
{
	TCHAR* Mess = NULL;
	OpenClipboard(NULL);
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	Mess = (TCHAR*)GlobalLock(hClipboardData);
	char* token1;
	char* token,* last;
	token = strtok(Mess, L" ", &last);
	char* str2 = (char*)calloc(100, 1);
	while (token != NULL)
	{
		char str1[1024];
		swprintf(str1, sizeof Mess, L"%s%s", "", token);
	
		int i = 0;
		int n = strlen(str1);

		for (i = 0; i != n; i++)
		{
			if (str1[i] == '0')
			{
				token1= "ноль";
				
			}
			else if (str1[i] == '1')
			{
				token1 = "один";
				
			}
			else if (str1[i] == '2')
			{
				token1 = "два";
				
			}
			else if (str1[i] == '3')
			{
				token1 = "три";
				
			}
			else if (str1[i] == '4')
			{
				token1 = "четыре";
				
			}
			else if (str1 == '5')
			{
				token1 = "пять";
				
			}
			else if (str1[i] == '6')
			{
				token1 = "шесть";
			
			}
			else if (str1[i] == '7')
			{
				token1 = "семь";
			
			}
			else if (str1[i] == '8')
			{
				token1 = "восемь";
			
			}
			else if (str1[i] == '9')
			{
				token1 = "девять";
				
			}
			else
			{
				if (i == n - 1)
				{
					token1 = token;
					
				}
			
			}
			

		}
		strcat(str2, &token1);
		token = strtok(NULL, " ", &last);
	}
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	//EmptyClipboard();
	return str2;
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