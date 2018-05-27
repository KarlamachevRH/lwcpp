#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#include <cmath>

using namespace std;

class convexQuad
{
	friend class containerTable;
	friend class hashingWithChains;
	friend class binaryTree;
private:
	double *diagonal1, *diagonal2; //диагонали выпуклого четырехугольника
	double *angle; //угол между диагоналями
	int mark; //признак, по которому фигуры делятся на категории и заносятся в массив в соответствующем узле списка			  

public:
	convexQuad(); //конструктор по умолчанию
	convexQuad(double d1, double d2, double angle);  // конструктор с заданными параметрами
	convexQuad(convexQuad &q);  //конструктор копирования
	double Get_diagonal1(); //получить значение
	double Get_diagonal2();
	double Get_angle();
	void Set_diagonal1(double d1); // изменить значение
	void Set_diagonal2(double d2);
	void Set_angle(double h);
	~convexQuad(); //деструктор
};

