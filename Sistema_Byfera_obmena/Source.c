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
	//	TCHAR Alert[] = L"�� �������� ��������� �����, ���������� ��������� ����: ";
	//	TCHAR third[512];
	//	swprintf(third, sizeof third, L"%s%s", Alert, Data);
	//	if (*Data != 0)
	//	{
	//		MessageBoxW(NULL, &third, L"��������!! ���������!!", MB_OK | MB_ICONWARNING);
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
				token1= "����";
				
			}
			else if (str1[i] == '1')
			{
				token1 = "����";
				
			}
			else if (str1[i] == '2')
			{
				token1 = "���";
		
			}
			else if (str1[i] == '3')
			{
				token1 = "���";
				
			}
			else if (str1[i] == '4')
			{
				token1 = "������";
				
			}
			else if (str1 == '5')
			{
				token1 = "����";
				
			}
			else if (str1[i] == '6')
			{
				token1 = "�����";
			
			}
			else if (str1[i] == '7')
			{
				token1 ="����";
			
			}
			else if (str1[i] == '8')
			{
				token1 = "������";
			
			}
			else if (str1[i] == '9')
			{
				token1 = "������";
				
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
	len = wcslen(buffer) + 1;//����������� ����� ������ � ������� �������
	hMen = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));//��������� ������ � ���������� ������� ���������
	memcpy(GlobalLock(hMen),buffer, len * sizeof(LPWSTR));//����������� ������� ������ �� buffer � hMen
	GlobalUnlock(hMen);//������������� ���������� ���� ������ (������� ��������� ��� ������ ��������)
	OpenClipboard(0);//������� ����� ������ 
	EmptyClipboard();//�������� ����� ������
	SetClipboardData(CF_UNICODETEXT, hMen);//�������� � ����� ������ ������ ���������������� ����
	CloseClipboard();//������� ������ ������� ��� ��������� ��� ������ ����������
	return 0;

}

int* ClipboardOutputText()
{
	TCHAR* Mess = NULL;
	OpenClipboard(NULL);//������� ����� ������ 
	HANDLE hClipboardDate = GetClipboardData(CF_UNICODETEXT);//�������� � ����� ������ ���������������� ����
	Mess = (TCHAR*)GlobalLock(hClipboardDate);// ������� �� ����������� ������� ������, �������� ��� ��� � ������
	GlobalUnlock(hClipboardDate);//���������� ���������� ������� ������ 
	CloseClipboard();//�������� ������, ������� ��� ��������� ��� ������ ����������
	EmptyClipboard();//�������� �����
	return Mess;
}