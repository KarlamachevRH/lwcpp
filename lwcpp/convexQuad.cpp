#include "convexQuad.h"

convexQuad::convexQuad()
{
	diagonal1 = 150;
	diagonal2 = 180;
	angle = 80;
}

convexQuad::convexQuad(int d1, int d2, double angle)
{
	diagonal1 = d1;
	diagonal2 = d2;
	this->angle = angle;
}

convexQuad::convexQuad(convexQuad &q)
{
	diagonal1 = q.diagonal1; // копирование атрибутов экзмепляра класса
	diagonal2 = q.diagonal2;
	angle = q.angle;
}
//получение значений элементов данных класса
double convexQuad::Get_diagonal1() { return diagonal1; }
double convexQuad::Get_diagonal2() { return diagonal2; }
double convexQuad::Get_angle() { return angle; }

//инициализация элементов данных класса
void convexQuad::Set_diagonal1(double d1) { diagonal1 = d1; }
void convexQuad::Set_diagonal2(double d2) { diagonal2 = d2; }
void convexQuad::Set_angle(double angle) {	this->angle = angle; }

//деструктор
convexQuad::~convexQuad()
{
}
