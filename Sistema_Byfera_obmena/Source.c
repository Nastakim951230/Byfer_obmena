#define _CRT_SECURE_NO_WARNINGS


#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ClipboardInputText(LPWSTR buffer);
int ClipboardOutptText();
char* strncat(char* dest, const char* src, size_t n);
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
	
	LPSTR Data = ClipboardOutptText2();

	ClipboardInputText(Data);	
	Sleep(100000);
	return 0;
}



TCHAR* ClipboardOutptText2()
{
	TCHAR* Mess = NULL;
	OpenClipboard(NULL);
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	Mess = (TCHAR*)GlobalLock(hClipboardData);
		char* token1=L"";
		char* token;
	token = strtok(Mess, L" ");
	char* str2 = (char*)calloc(100, 1);
	while (token != NULL)
	{
		char str1[1024];
		swprintf(str1, sizeof Mess, L"%s%s", L"", token);


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
				token1 ="семь";
			
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
		
		snprintf(str2, 120, "%s", token1);
		token = strtok(NULL, " ");
	}
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	//EmptyClipboard();
	return str2;
}

char*strncat(char* dest, const char* src, size_t n)
{
	size_t dest_len = strlen(dest);
	size_t i;
	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return dest;
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