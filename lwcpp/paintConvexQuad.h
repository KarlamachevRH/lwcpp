#pragma once
#include "convexQuad.h"

class paintConvexQuad
{
private:
	convexQuad *quad;
	int x, y;	
	double diagonal1Angle;

public:	
	paintConvexQuad(convexQuad *quad, int x, int y, double diagonal1Angle); //конструктор 
	void ReadFile();//считать из файла
	void PrintWindowSize(HDC hdc, HWND hwnd, char *buf);// вывод размера окна	
	int SetBrushColour(); // выбор цвета кисти для заливки
	HBRUSH SetBrush(HDC hdc); //выбор кисти для заливки
	void DelBrush(HDC hdc, HBRUSH hGreenBrush, HBRUSH hOldBrush); //удалить кисть
	void PaintFigure(HDC hdc);//рисовать контур фигуры
	void PaintFigureInside(HDC hdc); //рисовать вложенную фигуру
	double GetNewAngle(RECT &rt, HWND hwnd); //задать новые размеры фигуры
	double GetNewD1(RECT rt, HWND hwnd); 
	double GetNewD2(RECT rt, HWND hwnd);	
	void SetNewSize(double a, double d1, double d2); //изменить размеры фигуры
	int GetNewPositionX(); //получить величину смещения по оси х
	int GetNewPositionY(); //получить величину смещения по оси y
	void SetNewPosition(int coeffX, int coeffY, HWND hwnd); // изменить положение фигуры			
	void SaveFile();//сохранить в файл
	~paintConvexQuad();
};

