#include "paintConvexQuad.h"


paintConvexQuad::paintConvexQuad(convexQuad *quad, int x, int y, double diagonal1Angle)
{
	this->quad = quad;
	this->x = x; //�������� ��� ��������� ��������� ����� ��� ���������� ������
	this->y = y;
	this->diagonal1Angle = diagonal1Angle; // �������� ���� ��������� 1 � ��� �
}

void paintConvexQuad::ReadFile()
{	
	double diagonal1;
	double diagonal2;
	double angle;
	ifstream fin("ConvexQuad.txt");
	if (!fin.is_open()) throw 1; //���� ���� �� ����� ���� ������ ��������� ��� ������

	fin >> diagonal1;
	fin >> diagonal2;
	fin >> angle;

	quad->Set_diagonal1(diagonal1);
	quad->Set_diagonal2(diagonal2);
	quad->Set_angle(angle);

	fin.close(); // ������� ����
	cout << "������ ���������" << endl;
}

void paintConvexQuad::PrintWindowSize(HDC hdc, HWND hwnd, char *buf)
{
	RECT rt;
	// �������� ������ ����
	GetClientRect(hwnd, &rt);
	// ������������� ���� ����
	SetBkColor(hdc, RGB(0, 0, 0));
	// ������������� ���� ������
	SetTextColor(hdc, RGB(202, 120, 186));	
	// ��������� ��������� ������
	sprintf_s(buf, 100, "������ ���� %d �� %d ��������", rt.right, rt.bottom);
	// ������� ������ ������������ ����������
	TextOutA(hdc, 10, 10, buf, strlen(buf));
}

//����� ����� ��� �������
int paintConvexQuad::SetBrushColour()
{
	int choice;
	cout << "������� ����� ��������� ����� ������� ������:\n" 
		 << "1. �������\n"
		 << "2. �������\n"
		 << "3. �����\n" 
	     << ">";
	cin >> choice;
	return choice;
}

HBRUSH paintConvexQuad::SetBrush(HDC hdc)
{
	HBRUSH hSomeBrush;
	int choice = SetBrushColour();
	switch(choice)
	{
		case 1: hSomeBrush = CreateSolidBrush(RGB(250, 30, 65)); //�������
				break;

		case 2: hSomeBrush = CreateSolidBrush(RGB(90, 250, 80)); //�������
				break;

		case 3: hSomeBrush = CreateSolidBrush(RGB(90, 80, 250)); //�����
			break;
	}
	return hSomeBrush;
}

void paintConvexQuad::DelBrush(HDC hdc, HBRUSH hSomeBrush, HBRUSH hOldBrush)
{
	DeleteBrush(hSomeBrush);
	hOldBrush = SelectBrush(hdc, hOldBrush);
}

void paintConvexQuad::PaintFigure(HDC hdc)
{		
	double diagonal1 = quad->Get_diagonal1();
	double diagonal2 = quad->Get_diagonal2();
	double angle = quad->Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180; // 1 ������ � ��������

	POINT ppt[4] = { { x, 
					   y },
					 { x + lround((diagonal1/2) * cos(diagonal1Angle * deg) + (diagonal2 * 5 / 8)*cos((angle - diagonal1Angle) * deg)),
					   y + lround((diagonal1 / 2) * cos(diagonal1Angle * deg) - (diagonal2 * 5 / 8) * sin((angle - diagonal1Angle) * deg)) },
					 { x + lround(diagonal1 * cos(diagonal1Angle * deg)),
					   y + lround(diagonal1 * sin(diagonal1Angle * deg)) },
					 { x + lround((diagonal1 / 2) * sin(diagonal1Angle * deg) - (diagonal2 * 3 / 8)*cos((angle - diagonal1Angle)*deg)),
					   y + lround((diagonal1 / 2) * cos(diagonal1Angle * deg) + (diagonal2 * 3 / 8) * sin((angle - diagonal1Angle)*deg))} };
	// ������ �������� ���������������
	Polygon(hdc, ppt, 4);
}

void paintConvexQuad::PaintFigureInside(HDC hdc)
{
	double diagonal1 = quad->Get_diagonal1();
	double diagonal2 = quad->Get_diagonal2();
	double angle = quad->Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180; 
	int c = 20; // ����������� ��� ����������� ������������ �������������� ������������ �������� ������
	Rectangle(hdc, x + c, y + c, x + lround(diagonal1 * cos(diagonal1Angle * deg)) - c, y + lround(diagonal1 * sin(diagonal1Angle * deg) - c));
}

double paintConvexQuad::GetNewAngle(RECT &rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double a;
	double angleMax = 180;
	cout << "������� �������� ���� ����� ����������� ��������� ����������������" << endl
		<< "> ";
	cin >> a;
	if (a <= 0 || a >= angleMax - diagonal1Angle) throw 1;
	return a;
}

double paintConvexQuad::GetNewD1(RECT rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double d1;
	double PI = 3.14159265;
	double deg = PI / 180;
	cout << "������� ����� ��������� 1" << endl
		 << ">";
	cin >> d1;

	if (d1<=0 || d1>(rt.right*cos(diagonal1Angle * deg) - x*sqrt(2))) throw 1;
	return d1;
}

double paintConvexQuad::GetNewD2(RECT rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double d2;
	double angle = quad->Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180;
	cout << "������� ����� ��������� 1" << endl
		<< ">";
	cin >> d2;

	if (d2 <= 0 || d2 * cos((angle - diagonal1Angle) * deg) > rt.right || d2 * sin((angle - diagonal1Angle) * deg) > rt.bottom) throw 1;
	return d2;
}

void paintConvexQuad::SetNewSize(double d1, double d2, double a)
{
	quad->Set_diagonal1(d1);
	quad->Set_diagonal2(d2);
	quad->Set_angle(a);
}

int paintConvexQuad::GetNewPositionX()
{
	int coeffX;	
	cout << "������� �������� �� ��� �" << endl
		 << "> ";
	cin >> coeffX;
	return coeffX;
}

int paintConvexQuad::GetNewPositionY()
{
	int coeffY;
	cout << "������� �������� �� ��� y" << endl
		<< "> ";
	cin >> coeffY;
	return coeffY;
}

void paintConvexQuad::SetNewPosition(int coeffX, int coeffY, HWND hwnd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	x += coeffX;
	y += coeffY;
	if (x<=0 || x>rt.right) throw 1;
	if (y<=0 || y>rt.bottom) throw 1;

}

void paintConvexQuad::SaveFile()
{
	ofstream fout("ConvexQuad.txt"); // ������� ����

	fout << quad->Get_diagonal1() << " ";
	fout << quad->Get_diagonal2() << " ";
	fout << quad->Get_angle() << endl;

	fout.close(); 
	cout << "���� �������\n" << endl;
}

paintConvexQuad::~paintConvexQuad()
{
}