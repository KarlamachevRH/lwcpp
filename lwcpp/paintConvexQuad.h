#pragma once
#include "convexQuad.h"

class paintConvexQuad
{
private:
	convexQuad *quad;
	int x, y;	
	double diagonal1Angle;

public:	
	paintConvexQuad(convexQuad *quad, int x, int y, double diagonal1Angle); //����������� 
	void ReadFile();//������� �� �����
	void PrintWindowSize(HDC hdc, HWND hwnd, char *buf);// ����� ������� ����	
	int SetBrushColour(); // ����� ����� ����� ��� �������
	HBRUSH SetBrush(HDC hdc); //����� ����� ��� �������
	void DelBrush(HDC hdc, HBRUSH hGreenBrush, HBRUSH hOldBrush); //������� �����
	void PaintFigure(HDC hdc);//�������� ������ ������
	void PaintFigureInside(HDC hdc); //�������� ��������� ������
	double GetNewAngle(RECT &rt, HWND hwnd); //������ ����� ������� ������
	double GetNewD1(RECT rt, HWND hwnd); 
	double GetNewD2(RECT rt, HWND hwnd);	
	void SetNewSize(double a, double d1, double d2); //�������� ������� ������
	int GetNewPositionX(); //�������� �������� �������� �� ��� �
	int GetNewPositionY(); //�������� �������� �������� �� ��� y
	void SetNewPosition(int coeffX, int coeffY, HWND hwnd); // �������� ��������� ������			
	void SaveFile();//��������� � ����
	~paintConvexQuad();
};

