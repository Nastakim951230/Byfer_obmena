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
	
		TCHAR Alert[] = L"�� �������� ��������� �����, ���������� ��������� ����: ";
		TCHAR third[512];
		swprintf(third, sizeof third, L"%s%s", Alert, Data);
		if (*Data != 0)
		{
			MessageBoxW(NULL, &third, L"��������!! ���������!!", MB_OK | MB_ICONWARNING);
			ClipboardInputText("");
		}
		Sleep(1000);
	}
	return 0;
}

TCHAR* Text(LPSTR Data)
{
	// ������ �� ������� ��� ������
	char str[512] = Data;
	// ����� ��������, ������� ������ ������� � ������� �������
	char sep[512] = " ";
	// ����������, � ������� ����� ���������� ��������� ������ ������
	// ������ str
	char* istr;

	// ��������� ������ ����� ������
	istr = strtok(str, sep);

	// ��������� ����������� ������
	while (istr != NULL)
	{
		char str[512] = istr;
		// ����� ��������, ������� ������ ������� � ������� �������
		char sep[512] = "/0";
		
		
		// ��������� ��������� ����� ������
		istr = strtok(NULL, sep);
	}
	
	
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

TCHAR* ClipboardOutputText()
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