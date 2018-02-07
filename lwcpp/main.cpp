#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#include <iostream>
#include <tchar.h>

using namespace std;

int main_menu()
{
	// Варианты меню
	int choice;
	cout << "Введите номер пункта меню\n" 
	     << "1. Вывод выпуклого четырехугольника\n"
		 << "2. Вывод закрашенного выпуклого четырехугольника\n"
	 	 << "3. Вывод фигуры внутри выпуклого четырехугольника\n"
		 << "4. Выход\n" 
		 << ">";
	cin >> choice;
	return choice;
}

//функция проверки наличия окна блокнота
bool is_finded(HWND hwnd)
{
	bool f = false;
	if (hwnd != NULL)
	{
		f = true;
		cout << "Окно найдено\n";
		TCHAR name[200];
		GetWindowText(hwnd, name, sizeof(name));
		wcout << name << endl;
	}
	else
	{
		cout << "Окно не найдено\n";
		f = false;
	}
	return f;
}

//Вывод выпуклого четырехугольника
void draw_quad()
{
	bool f = false; //индикатор наличия окна блокнота для вывода графики
	// получаем контекст отображения
	HWND hwnd = FindWindow(TEXT("Notepad"), NULL);
	f = is_finded(hwnd);	
	if (f == true)
	{
		HDC hdc = GetDC(hwnd);
		RECT rt;
		char buf[100];
		// устанавливаем цвет фона
		SetBkColor(hdc, RGB(0, 0, 0));
		// устанавливаем цвет текста
		SetTextColor(hdc, RGB(84, 127, 185));
		// создаем синее перо
		HPEN hBluePen = CreatePen(PS_SOLID, 5, RGB(69, 87, 234));
		HPEN hOldPen = SelectPen(hdc, hBluePen);
		do
		{
			GetClientRect(hwnd, &rt);
			sprintf_s(buf, "Размер окна %d на %d пикселей", rt.right, rt.bottom);
			TextOutA(hdc, 10, 10, buf, strlen(buf));
			POINT ppt[4] = {{ 120, 40 },{ rt.right - 120, 30 },{ rt.right - 90, rt.bottom - 30 },{ 130,rt.bottom - 50 }};
			//вывод выпуклого четырехугольника
			Polygon(hdc, ppt, 4);
		} while (_getch() != 27);
		// выбираем в контекст отображения предыдущее перо
		SelectPen(hdc, hOldPen);
		// удаляем синее перо
		DeletePen(hBluePen);
		// освобождаем контекст отображения
		ReleaseDC(hwnd, hdc);
	}
	else  exit(0);
}

//Вывод закрашенного выпуклого четырехугольника
void draw_filled_quad()
{
	bool f = false;
	HWND hwnd = FindWindow(TEXT("Notepad"), NULL);	
	f = is_finded(hwnd);
	if (f == true)
	{
		// получаем контекст отображения
		HDC hdc = GetDC(hwnd);
		RECT rt;
		char buf[100];
		// устанавливаем цвет фона
		SetBkColor(hdc, RGB(0, 0, 0));
		// устанавливаем цвет текста
		SetTextColor(hdc, RGB(84, 127, 185));
		// создаем синее перо
		HPEN hBluePen = CreatePen(PS_SOLID, 5, RGB(223, 238, 94));
		// и выбираем его в контекст отображения, сохраняя предыдущее перо
		HPEN hOldPen = SelectPen(hdc, hBluePen);
		// создаем зеленую кисть
		HBRUSH hGreenBrush = CreateSolidBrush(RGB(149, 246, 75));
		// и выбираем ее в контекст отображения, сохраняя предыдущую кисть
		HBRUSH hOldBrush = SelectBrush(hdc, hGreenBrush);
		do
		{
			// получаем размер окна
			GetClientRect(hwnd, &rt);
			// формируем выводимую строку
			sprintf_s(buf, "Размер окна %d на %d пикселей", rt.right, rt.bottom);
			// выводим строку графическими средствами
			TextOutA(hdc, 10, 10, buf, strlen(buf));
			POINT ppt[4] = { { 120, 40 },{ rt.right - 120, 30 },{ rt.right - 90, rt.bottom - 30 },{ 130,rt.bottom - 50 } };
			// рисуем закрашенный выпуклый четырехугольник
			Polygon(hdc, ppt, 4);
		} while (_getch() != 27);
		// выбираем в контекст отображения предыдущую кисть
		SelectBrush(hdc, hOldBrush);
		// удаляем зеленую кисть
		DeleteBrush(hGreenBrush);
		// выбираем в контекст отображения предыдущее перо
		SelectPen(hdc, hOldPen);
		// удаляем синее перо
		DeletePen(hBluePen);
		// освобождаем контекст отображения
		ReleaseDC(hwnd, hdc);
	}
	else  exit(0);
}

//Вывод комбинированной фигуры
void draw_combined_figure()
{
	bool f = false; //индикатор наличия окна блокнота для вывода графики
	HWND hwnd = FindWindow(TEXT("Notepad"), NULL);
	f = is_finded(hwnd);
	if (f == true)
	{
		HDC hdc = GetDC(hwnd);
		RECT rt;
		char buf[100];
		// устанавливаем цвет фона
		SetBkColor(hdc, RGB(0, 0, 0));
		// устанавливаем цвет текста
		SetTextColor(hdc, RGB(161, 70, 213));
		// создаем синее перо
		HPEN hBluePen = CreatePen(PS_SOLID, 5, RGB(223, 238, 94));
		HPEN hOldPen = SelectPen(hdc, hBluePen);
		do
		{
			GetClientRect(hwnd, &rt);
			sprintf_s(buf, "Размер окна %d на %d пикселей", rt.right, rt.bottom);
			TextOutA(hdc, 10, 10, buf, strlen(buf));
			HBRUSH hGreenBrush = CreateSolidBrush(RGB(149, 246, 75));
			HBRUSH hOldBrush = SelectBrush(hdc, hGreenBrush);
			POINT ppt[4] = { { 120, 40 },{ rt.right - 120, 30 },{ rt.right - 90, rt.bottom - 30 },{ 130, rt.bottom - 50 } };
			//выпуклый четырехугольник
			Polygon(hdc, ppt, 4);
			SelectBrush(hdc, hOldBrush);
			DeleteBrush(hGreenBrush);
			Rectangle(hdc, 180, 80, rt.right - 180, rt.bottom - 90);
		} while (_getch() != 27);
		// выбираем в контекст отображения предыдущее перо
		SelectPen(hdc, hOldPen);
		// удаляем синее перо
		DeletePen(hBluePen);
		// освобождаем контекст отображения
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