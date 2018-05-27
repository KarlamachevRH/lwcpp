#pragma once
#include "containerTable.h"
#include "hashingWithChains.h"
#include "binaryTree.h"

using namespace std;

//основное меню
int mainMenu()
{
	// Варианты меню
	int choice;
	do
	{
		cout << "Введите номер пункта меню:\n"
			<< "1. Ввод сохраненных данных из файла\n"
			<< "2. Вывод выпуклого четырехугольника\n"
			<< "3. Вывод закрашенного выпуклого четырехугольника\n"
			<< "4. Вывод фигуры внутри выпуклого четырехугольника\n"
			<< "5. Изменение размеров фигуры\n"
			<< "6. Перемещение фигуры\n"
			<< "7. Вывод данных в файл\n"
			<< "8. В меню выбора контейнеров для фигур и работы с ними\n"			
			<< "9. Выход\n"
			<< "ESC для повтора выбора пункта меню\n"
			<< ">:";
		cin >> choice;
	} while (choice < 1 || choice > 9);
	return choice;
}

//меню выбора типа контейнера
int containerSelection()
{
	int choice;
	do
	{
		cout << "Выберите тип контейнера для фигур:\n"
			<< "1. Таблица на основе двухсвязного списка\n"
			<< "2. Таблица на основе хеш-таблицы\n"
			<< "3. Таблица на основе дерева двоичного поиска\n"			
			<< "4. Выход в основное меню\n"
			<< "ESC для повтора выбора пункта меню\n"
			<< ">:";
		cin >> choice;
	} while (choice < 1 || choice > 4);
	return choice;
}

//меню выбора действий при работе с контейнерами
int menuContainers()
{
	int choice = 0;
	do
	{
		cout << "Введите номер пункта меню выбора действий при работе с контейнерами:\n"
			<< "1. Добавить объект в контейнер - таблицу\n"
			<< "2. Загрузить данные объектов из файла в контейнер - таблицу \n"
			<< "3. Сохранить данные объектов из контейнера в файл\n"
			<< "4. Удалить элемент из таблицы\n"
			<< "5. Вывод данных объектов в таблице на экран\n"
			<< "6. Выход в меню выбора типа контейнера\n"
			<< "ESC для повтора выбора пункта меню\n"
			<< ">:";
		cin >> choice;
	} while (choice < 1 || choice > 6);		

	return choice;
}

paintConvexQuad *createShapeFirstTime()
{
	convexQuad *q = new convexQuad();
	paintConvexQuad *p = new paintConvexQuad(q, 120, 100, 45);
	return p;
}

paintConvexQuad *createShape()
{
	double d1, d2, angle;
	cout << "Введите параметры фигуры: d1, d2, angle\n";
	cin >> d1 >> d2 >> angle;
	convexQuad *q = new convexQuad(d1, d2, angle);
	paintConvexQuad *p = new paintConvexQuad(q, 120, 100, 45);
	return p;
}

//работа с двухсвязным списком
int workingWithDoubleLinkedList()
{
	containerTable *l = new containerTable; //создание объекта-контейнера

	int cnt = 0; //счетчик циклов основного меню в функции

	while (1)
	{
		//выбор действий при работе с контейнером
		int choice = menuContainers();

		paintConvexQuad *p = NULL;

		//начальное создание объекта - фигуры
		if(cnt == 0)	p = createShapeFirstTime();

		//добавить еще одну фигуру
		if (cnt > 0 && choice == 1) p = createShape();		

		switch (choice)
		{
		case 1: l->addShapeToTable(p);
			break;

		case 2:	try
				{
					l->writeDataFromFileToTable();			
				}
				catch (int error)
				{
					if (error == 1)
					{
						cout << "Файл не найден" << endl;
					}
				}
			break;

		case 3: l->saveDataInTableToFile();			
			break;

		case 4: l->deleteTableElement();
			break;

		case 5: l->showAllListsElements();			
			break;

		case 6: delete l;
			return 0;
			break;

		default: break;
		}	
		cnt++;
	}
}

//работа с хеш-таблицей
int workingWithHashTable()
{
	hashingWithChains *h = new hashingWithChains(3);

	int cnt = 0; //счетчик циклов основного меню в функции

	while (1)
	{
		//выбор действий при работе с контейнером
		int choice = menuContainers();

		paintConvexQuad *p = NULL;

		//начальное создание объекта - фигуры
		if (cnt == 0) p = createShapeFirstTime();

		//добавить еще одну фигуру
		if (cnt > 0 && choice == 1) p = createShape();
		
		switch (choice)
		{
		case 1: h->addShape(p);
			break;

		case 2: try
				{	
					h->readDataFromFileToTable();			
				}
			    catch (int error)
			    {
				    if (error == 1)
				    {
					   cout << "Файл не найден" << endl;
				    }
			    }

			break;

		case 3: h->saveDataInTableToFile();
			break;

		case 4: h->deleteShape();
			break;

		case 5: h->showAllTableElementsData();			
			break;

		case 6: delete h;
			return 0;
			break;

		default: break;
		}
		cnt++;
	}
}

//работа с бинарным деревом
int workingWithBinaryTree()
{
	binaryTree *t = new binaryTree();

	bool isCreated = false; //число фигур, добавленных в контейнер вручную

	BSTNode *parent = NULL;

	BSTNode *root = t->getRoot();

	paintConvexQuad *p = NULL;

	while (1)
	{
		//выбор действий при работе с контейнером
		int choice = menuContainers();

		//начальное создание объекта - фигуры
		if (isCreated == false) p = createShapeFirstTime();

		//добавить еще одну фигуру
		if (isCreated == true && choice == 1) p = createShape();
		
		switch (choice)
		{
		case 1: t->insert(root, parent, p);	
			isCreated = true;
			break;

		case 2: try
				{					
					t->readDataFromFileToTree(root, parent);	
					isCreated = true;
				}
			    catch (int error)
			    {
				    if (error == 1)
			  	    {
					    cout << "Файл не найден" << endl;
				    }
			    }
			break;

		case 3: t->saveData(root);				
			break;

		case 4: t->deleteShape(root, t->writeChoiceToDeleteShape());				
			break;

		case 5: t->scan(root);				
			break;

		case 6: delete t;
			return 0;
			break;

		default: break;
		}		
	}
}

//работа с контейнерами
void workingWithContainers()
{
	while (1)
	{
		//выбор типа контейнера
		int choice = containerSelection();

		switch (choice)
		{
		case 1: workingWithDoubleLinkedList(); //работа с двунаправленным списком
			break;

		case 2:	workingWithHashTable(); //работа с хеш-таблицей
			break;

		case 3:	workingWithBinaryTree(); //работа с бинарным деревом
			break;

		case 4: return;
			break;

		default: break;
		}
	}
}

//функция проверки наличия окна блокнота
bool isFinded(HWND hwnd)
{
	bool f = false;
	if (hwnd != NULL)
	{
		f = true;
		cout << "Окно блокнота найдено\n";
		TCHAR name[200];
		GetWindowText(hwnd, name, sizeof(name));
		wcout << name << endl;
	}
	else

	{
		cout << "Окно блокнота не найдено\n";
		f = false;
		cin.get();
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

		convexQuad *q = new convexQuad;
		paintConvexQuad *p = new paintConvexQuad(q, 120, 100, 45);		

		while (1)
		{
			int choice = mainMenu();
			
			p->PrintWindowSize(hdc, hwnd, buf);
			switch (choice)
			{
			case 1: try
					{
						p->ReadFile();
					}
					catch (int error)
					{
						if (error == 1)
						{
							cout << "Файл не найден" << endl;
						}
					}
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

			case 8:	workingWithContainers();
				break;

			case 9: 		
				delete p;
				ReleaseDC(hwnd, hdc);
				exit(0);
				break;

			default: break;
			}			
		}		
	}
	else return;
}