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

	while (TRUE)
	{
		LPSTR Data = ClipboardOutptText2();
		
		if (*Data != 0)
		{
			switch (*Data)
			{
			case '0':
				ClipboardInputText(L"����");
				break;
			case '1':
				ClipboardInputText(L"����");
				break;
			case '2':
				ClipboardInputText(L"���");
				break;
			case '3':
				ClipboardInputText(L"���");
				break;
			case '4':
				ClipboardInputText(L"������");
				break;
			case '5':
				ClipboardInputText(L"����");
				break;
			case '6':
				ClipboardInputText(L"�����");
				break;
			case '7':
				ClipboardInputText(L"����");
				break;
			case '8':
				ClipboardInputText(L"������");
				break;
			case '9':
				ClipboardInputText(L"������");
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