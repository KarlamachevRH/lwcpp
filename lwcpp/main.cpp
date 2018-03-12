#pragma once
#include "convexQuad.h"
#include "paintConvexQuad.h"

using namespace std;

int mainMenu()
{
	// Варианты меню
	int choice;
	do
	{
		cout << "Введите номер пункта меню\n"
			<< "1. Ввод сохраненных данных из файла\n"
			<< "2. Вывод выпуклого четырехугольника\n"
			<< "3. Вывод закрашенного выпуклого четырехугольника\n"
			<< "4. Вывод фигуры внутри выпуклого четырехугольника\n"
			<< "5. Изменение размеров фигуры\n"
			<< "6. Перемещение фигуры\n"
			<< "7. Вывод данных в файл\n"
			<< "8. Выход\n"
			<< ">";
		cin >> choice;
	} while (choice < 1 || choice > 8);
	return choice;
}

//функция проверки наличия окна блокнота
bool isFinded(HWND hwnd)
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

void main()
{
	setlocale(LC_ALL, "rus");

	double a, d1, d2; //переменные задания новых размеров
	int coeffX, coeffY; //переменные задания смещения по осям x и y
	int err = 0;
	HWND hwnd = FindWindow(TEXT("Notepad"), NULL);
	if (isFinded(hwnd))
	{
		// получаем контекст отображения
		HDC hdc = GetDC(hwnd);
		RECT rt;
		char buf[100];
		HBRUSH hOldBrush;
		HBRUSH hSomeBrush;
		HPEN hBluePen = CreatePen(PS_SOLID, 5, RGB(223, 238, 94));
		HPEN hOldPen = SelectPen(hdc, hBluePen);

		convexQuad *q = new convexQuad();
		paintConvexQuad *p = new paintConvexQuad(q, 120, 200, 45);

		while (1)
		{
			int choice = mainMenu();
			p->PrintWindowSize(hdc, hwnd, buf);
			switch (choice)
			{
			case 1: p->ReadFile();
				break;

			case 2:	do
					{
						p->PaintFigure(hdc);
					} while (_getch() != 27);
				break;

			case 3:	do
					{
						hSomeBrush = p->SetBrush(hdc); //выбрать кисть для заливки
						hOldBrush = SelectBrush(hdc, hSomeBrush);
						p->PaintFigure(hdc);
						p->DelBrush(hdc, hSomeBrush, hOldBrush); //удалить кисть для заливки
					} while (_getch() != 27);
				break;

			case 4: do
					{
						hSomeBrush = p->SetBrush(hdc); //выбрать кисть для заливки
						hOldBrush = SelectBrush(hdc, hSomeBrush);
						p->PaintFigure(hdc);
						p->DelBrush(hdc, hSomeBrush, hOldBrush); //удалить кисть для заливки
						p->PaintFigureInside(hdc);
					} while (_getch() != 27);
				break;

			case 5: do
					{	
						err = 0;
						try
						{
							a = p->GetNewAngle(rt, hwnd);
							d1 = p->GetNewD1(rt, hwnd);
							d2 = p->GetNewD2(rt, hwnd);
						}
						catch (int error)
						{
							if (error == 1)
							{
								cout << "Введенные данные не корректны, повторите ввод" << endl;
								err = error;
							}								
						}
					} while (err == 1);					
					p->SetNewSize(a, d1, d2);
				break;

			case 6:	coeffX = p->GetNewPositionX();
					coeffY = p->GetNewPositionY();
					do
					{
						err = 0;
						try
						{
							p->SetNewPosition(coeffX, coeffY, hwnd);
						}
						catch (int error)
						{
							if (error == 0)
							{
								cout << "Введенные данные не корректны, повторите ввод" << endl;
								err = error;
							}								
						}
					} while (err == 1);
				break;

			case 7:	p->SaveFile();
				break;

			case 8:	exit(0);
				break;
			}
		}
		delete q;
		delete p;
		ReleaseDC(hwnd, hdc);
	}
	else return;
}