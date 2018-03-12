#include "paintConvexQuad.h"


paintConvexQuad::paintConvexQuad(convexQuad *quad, int x, int y, double diagonal1Angle)
{
	this->x = new int;
	this->y = new int;
	this->diagonal1Angle = new double;
	this->quad = quad;
	*this->x = x; //значения для координат начальной точки для построения фигуры
	*this->y = y;
	*this->diagonal1Angle = diagonal1Angle; // значение угла диагонали 1 к оси х
}

void paintConvexQuad::ReadFile()
{	
	double diagonal1;
	double diagonal2;
	double angle;
	ifstream fin("ConvexQuad.txt");
	if (!fin.is_open()) throw 1; //если файл не может быть открыт выбросить код ошибки

	fin >> diagonal1;
	fin >> diagonal2;
	fin >> angle;

	quad->Set_diagonal1(diagonal1);
	quad->Set_diagonal2(diagonal2);
	quad->Set_angle(angle);

	fin.close(); // закрыть файл
	cout << "Данные загружены" << endl;
}

void paintConvexQuad::PrintWindowSize(HDC hdc, HWND hwnd, char *buf)
{
	RECT rt;
	// получаем размер окна
	GetClientRect(hwnd, &rt);
	// устанавливаем цвет фона
	SetBkColor(hdc, RGB(0, 0, 0));
	// устанавливаем цвет текста
	SetTextColor(hdc, RGB(202, 120, 186));	
	// формируем выводимую строку
	sprintf_s(buf, 100, "Размер окна %d на %d пикселей", rt.right, rt.bottom);
	// выводим строку графическими средствами
	TextOutA(hdc, 10, 10, buf, strlen(buf));
}

//выбор кисти для заливки
int paintConvexQuad::SetBrushColour()
{
	int choice;
	cout << "Введите номер желаемого цвета заливки фигуры:\n" 
		 << "1. Красный\n"
		 << "2. Зеленый\n"
		 << "3. Синий\n" 
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
		case 1: hSomeBrush = CreateSolidBrush(RGB(250, 30, 65)); //красный
				break;

		case 2: hSomeBrush = CreateSolidBrush(RGB(90, 250, 80)); //зеленый
				break;

		case 3: hSomeBrush = CreateSolidBrush(RGB(90, 80, 250)); //синий
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
	double deg = PI / 180; // 1 градус в радианах

	POINT ppt[4] = { { *x, 
					   *y },
					 { *x + lround((diagonal1/2) * cos(*diagonal1Angle * deg) + (diagonal2 * 5 / 8)*cos((angle - *diagonal1Angle) * deg)),
					   *y + lround((diagonal1 / 2) * cos(*diagonal1Angle * deg) - (diagonal2 * 5 / 8) * sin((angle - *diagonal1Angle) * deg)) },
					 { *x + lround(diagonal1 * cos(*diagonal1Angle * deg)),
					   *y + lround(diagonal1 * sin(*diagonal1Angle * deg)) },
					 { *x + lround((diagonal1 / 2) * sin(*diagonal1Angle * deg) - (diagonal2 * 3 / 8)*cos((angle - *diagonal1Angle)*deg)),
					   *y + lround((diagonal1 / 2) * cos(*diagonal1Angle * deg) + (diagonal2 * 3 / 8) * sin((angle - *diagonal1Angle)*deg))} };
	// рисуем выпуклый четырехугольник
	Polygon(hdc, ppt, 4);
}

void paintConvexQuad::PaintFigureInside(HDC hdc)
{
	double diagonal1 = quad->Get_diagonal1();
	double diagonal2 = quad->Get_diagonal2();
	double angle = quad->Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180; 
	int c = 20; // коэффициент для внутреннего расположения прямоугольника относительно основной фигуры
	Rectangle(hdc, *x + c, *y + c, *x + lround(diagonal1 * cos(*diagonal1Angle * deg)) - c, *y + lround(diagonal1 * sin(*diagonal1Angle * deg) - c));
}

double paintConvexQuad::GetNewAngle(RECT &rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double a;
	double angleMax = 90;
	cout << "Введите значение угла между диагоналями выпуклого четырехугольника" << endl
		<< "> ";
	cin >> a;
	if (a <= 30 || a >= angleMax - *diagonal1Angle) throw 1;
	return a;
}

double paintConvexQuad::GetNewD1(RECT rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double d1;
	double PI = 3.14159265;
	double deg = PI / 180;
	cout << "Введите длину диагонали 1" << endl
		 << ">";
	cin >> d1;

	if (d1<=0 || d1>(rt.right*cos(*diagonal1Angle * deg) - *x*sqrt(2))) throw 1;
	return d1;
}

double paintConvexQuad::GetNewD2(RECT rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double d2;
	double angle = quad->Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180;
	cout << "Введите длину диагонали 1" << endl
		<< ">";
	cin >> d2;

	if (d2 <= 0 || d2 * cos((angle - *diagonal1Angle) * deg) > rt.right || d2 * sin((angle - *diagonal1Angle) * deg) > rt.bottom) throw 1;
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
	cout << "Задайте смещение по оси х" << endl
		 << "> ";
	cin >> coeffX;
	return coeffX;
}

int paintConvexQuad::GetNewPositionY()
{
	int coeffY;
	cout << "Задайте смещение по оси y" << endl
		<< "> ";
	cin >> coeffY;
	return coeffY;
}

void paintConvexQuad::SetNewPosition(int coeffX, int coeffY, HWND hwnd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	*x += coeffX;
	*y += coeffY;
	if (*x<=0 || *x>rt.right) throw 1;
	if (*y<=0 || *y>rt.bottom) throw 1;

}

void paintConvexQuad::SaveFile()
{
	ofstream fout("ConvexQuad.txt"); // открыть файл

	fout << quad->Get_diagonal1() << " ";
	fout << quad->Get_diagonal2() << " ";
	fout << quad->Get_angle() << endl;

	fout.close(); 
	cout << "Файл записан\n" << endl;
}

paintConvexQuad::~paintConvexQuad()
{
	delete x;
	delete y;
	delete diagonal1Angle;
}
