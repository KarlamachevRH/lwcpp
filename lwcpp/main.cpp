#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#include <iostream>
#include <tchar.h>

using namespace std;

int main_menu()
{
	// �������� ����
	int choice;
	cout << "������� ����� ������ ����\n" 
	     << "1. ����� ��������� ����������������\n"
		 << "2. ����� ������������ ��������� ����������������\n"
	 	 << "3. ����� ������ ������ ��������� ����������������\n"
		 << "4. �����\n" 
		 << ">";
	cin >> choice;
	return choice;
}

//������� �������� ������� ���� ��������
bool is_finded(HWND hwnd)
{
	bool f = false;
	if (hwnd != NULL)
	{
		f = true;
		cout << "���� �������\n";
		TCHAR name[200];
		GetWindowText(hwnd, name, sizeof(name));
		wcout << name << endl;
	}
	else
	{
		cout << "���� �� �������\n";
		f = false;
	}
	return f;
}

//����� ��������� ����������������
void draw_quad()
{
	bool f = false; //��������� ������� ���� �������� ��� ������ �������
	// �������� �������� �����������
	HWND hwnd = FindWindow(TEXT("Notepad"), NULL);
	f = is_finded(hwnd);	
	if (f == true)
	{
		HDC hdc = GetDC(hwnd);
		RECT rt;
		char buf[100];
		// ������������� ���� ����
		SetBkColor(hdc, RGB(0, 0, 0));
		// ������������� ���� ������
		SetTextColor(hdc, RGB(84, 127, 185));
		// ������� ����� ����
		HPEN hBluePen = CreatePen(PS_SOLID, 5, RGB(69, 87, 234));
		HPEN hOldPen = SelectPen(hdc, hBluePen);
		do
		{
			GetClientRect(hwnd, &rt);
			sprintf_s(buf, "������ ���� %d �� %d ��������", rt.right, rt.bottom);
			TextOutA(hdc, 10, 10, buf, strlen(buf));
			POINT ppt[4] = {{ 120, 40 },{ rt.right - 120, 30 },{ rt.right - 90, rt.bottom - 30 },{ 130,rt.bottom - 50 }};
			//����� ��������� ����������������
			Polygon(hdc, ppt, 4);
		} while (_getch() != 27);
		// �������� � �������� ����������� ���������� ����
		SelectPen(hdc, hOldPen);
		// ������� ����� ����
		DeletePen(hBluePen);
		// ����������� �������� �����������
		ReleaseDC(hwnd, hdc);
	}
	else  exit(0);
}

//����� ������������ ��������� ����������������
void draw_filled_quad()
{
	bool f = false;
	HWND hwnd = FindWindow(TEXT("Notepad"), NULL);	
	f = is_finded(hwnd);
	if (f == true)
	{
		// �������� �������� �����������
		HDC hdc = GetDC(hwnd);
		RECT rt;
		char buf[100];
		// ������������� ���� ����
		SetBkColor(hdc, RGB(0, 0, 0));
		// ������������� ���� ������
		SetTextColor(hdc, RGB(84, 127, 185));
		// ������� ����� ����
		HPEN hBluePen = CreatePen(PS_SOLID, 5, RGB(223, 238, 94));
		// � �������� ��� � �������� �����������, �������� ���������� ����
		HPEN hOldPen = SelectPen(hdc, hBluePen);
		// ������� ������� �����
		HBRUSH hGreenBrush = CreateSolidBrush(RGB(149, 246, 75));
		// � �������� �� � �������� �����������, �������� ���������� �����
		HBRUSH hOldBrush = SelectBrush(hdc, hGreenBrush);
		do
		{
			// �������� ������ ����
			GetClientRect(hwnd, &rt);
			// ��������� ��������� ������
			sprintf_s(buf, "������ ���� %d �� %d ��������", rt.right, rt.bottom);
			// ������� ������ ������������ ����������
			TextOutA(hdc, 10, 10, buf, strlen(buf));
			POINT ppt[4] = { { 120, 40 },{ rt.right - 120, 30 },{ rt.right - 90, rt.bottom - 30 },{ 130,rt.bottom - 50 } };
			// ������ ����������� �������� ���������������
			Polygon(hdc, ppt, 4);
		} while (_getch() != 27);
		// �������� � �������� ����������� ���������� �����
		SelectBrush(hdc, hOldBrush);
		// ������� ������� �����
		DeleteBrush(hGreenBrush);
		// �������� � �������� ����������� ���������� ����
		SelectPen(hdc, hOldPen);
		// ������� ����� ����
		DeletePen(hBluePen);
		// ����������� �������� �����������
		ReleaseDC(hwnd, hdc);
	}
	else  exit(0);
}

//����� ��������������� ������
void draw_combined_figure()
{
	bool f = false; //��������� ������� ���� �������� ��� ������ �������
	HWND hwnd = FindWindow(TEXT("Notepad"), NULL);
	f = is_finded(hwnd);
	if (f == true)
	{
		HDC hdc = GetDC(hwnd);
		RECT rt;
		char buf[100];
		// ������������� ���� ����
		SetBkColor(hdc, RGB(0, 0, 0));
		// ������������� ���� ������
		SetTextColor(hdc, RGB(161, 70, 213));
		// ������� ����� ����
		HPEN hBluePen = CreatePen(PS_SOLID, 5, RGB(223, 238, 94));
		HPEN hOldPen = SelectPen(hdc, hBluePen);
		do
		{
			GetClientRect(hwnd, &rt);
			sprintf_s(buf, "������ ���� %d �� %d ��������", rt.right, rt.bottom);
			TextOutA(hdc, 10, 10, buf, strlen(buf));
			HBRUSH hGreenBrush = CreateSolidBrush(RGB(149, 246, 75));
			HBRUSH hOldBrush = SelectBrush(hdc, hGreenBrush);
			POINT ppt[4] = { { 120, 40 },{ rt.right - 120, 30 },{ rt.right - 90, rt.bottom - 30 },{ 130, rt.bottom - 50 } };
			//�������� ���������������
			Polygon(hdc, ppt, 4);
			SelectBrush(hdc, hOldBrush);
			DeleteBrush(hGreenBrush);
			Rectangle(hdc, 180, 80, rt.right - 180, rt.bottom - 90);
		} while (_getch() != 27);
		// �������� � �������� ����������� ���������� ����
		SelectPen(hdc, hOldPen);
		// ������� ����� ����
		DeletePen(hBluePen);
		// ����������� �������� �����������
		ReleaseDC(hwnd, hdc);
	}
	else  exit(0);
}

void main()
{
	setlocale(LC_ALL, "rus");
	while(1)
	{
		int choice = main_menu();
		switch (choice)
		{
		case 1:	draw_quad();
			break;
		case 2:	draw_filled_quad();
			break;
		case 3:	draw_combined_figure();
			break;
		case 4: exit(0);
		}
	} 
}