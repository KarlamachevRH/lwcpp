#pragma once
#include "containerTable.h"


containerTable::containerTable()
{
	head = NULL;
	tail = NULL;
	curr = NULL;	
}

void containerTable::addShapeToTable(paintConvexQuad *paintQuad)
{
	createNode(paintQuad->quad->mark);
	if (searchFreeCell() >= 0) curr->quads[searchFreeCell()] = paintQuad;
	else cout << "Нет свободных ячеек, нажмите любую кнопку для возврата" << endl;
	cin.get();
}

void containerTable::searchNode(int mark)
{
	CNode *curr = head;
	while (curr != NULL)
	{
		if (curr->key == mark)
			return;
		curr = curr->next;
	}	
}

int containerTable::searchFreeCell()
{
	for (int i = 0; i < 5; i++)
	{
		if(curr->quads[i] == NULL) return i;
	}
	return -1;
}

void containerTable::createNode(int mark)
{
	CNode *node;
	node = new CNode;
	if (head == NULL)
	{
		head = tail = curr = node;		
		curr->key = mark;
	}
	else
	{
		curr = head;
		while (curr->key != mark && curr->next != NULL)
		{
			curr = curr->next;
		}
		if (curr->key == mark)
		{
			delete node;
		}
		else
		{
			curr->next = node;
			curr->next->prev = curr;
			curr = tail = node;
			curr->key = mark;
		}
	}
}

void containerTable::deleteTableElement()
{
	int mark;
	if (head == NULL)
	{
		cout << "Таблица пуста" << endl;
		return;
	}
	cout << "Введите идентификатор удаляемых фигур:\n"
		<< "Если d1 < d2 - цифра 0\n"
		<< "Если d1 > d2 - цифра 1\n"
		<< "Если d1 = d2 - цифра 2" << endl;
	do {
		cin >> mark;
	} while (mark < 0 && mark > 2);
	searchNode(mark);
	deleteShape();
}

void containerTable::deleteShape()
{
	int choice;		
	cout << "Введите номер удаляемой фигуры 1...5: " << endl;
	do {
		cin >> choice;
	} while (choice < 1 && choice > 5);	
	delete curr->quads[choice];
	curr->quads[choice] = NULL;
}


//распечатка элементов в таблице
void containerTable::showAllListsElements()
{
	if (head != NULL)
	{
		paintConvexQuad *tmp;
		tmp = NULL;
		int choice;
		cout << "Выберите направление вывода данных объектов списка:\n"
			<< "1 - c произвести вывод с начала списка\n"
			<< "2 - с конца списка" << endl;
		do {
			cin >> choice;
		} while (choice < 1 && choice > 2);

		switch (choice)
		{
		case 1: showFromHead(tmp);
			break;
		case 2:showFromTail(tmp);
			break;
		}			
	}
	else cout << "Нет данных в таблице" << endl
		      << "Нажмите Esc для возврата" << endl;
}

void containerTable::showOneListElements(paintConvexQuad *tmp)
{
	for (int i = 0; i < 5; i++)
	{
		while (curr->quads[i] == NULL && i<5) i++;
		if (curr->quads[i] != NULL)
		{
			tmp = curr->quads[i];
			cout << "Длина диагонали 1 выпуклого четырехугольника: " << tmp->quad->Get_diagonal1() << endl
				<< "Длина диагонали 2 выпуклого четырехугольника: " << tmp->quad->Get_diagonal2() << endl
				<< "Величина угла между диагоналями выпуклого четырехугольника: " << tmp->quad->Get_angle() << endl;
		}
	}
}

void containerTable::showFromHead(paintConvexQuad *tmp)
{
	curr = head;	
	while (curr != NULL)
	{
		cout << "Номер категории фигур: " << curr->key << endl;
		showOneListElements(tmp);
		curr=curr->next;
	}
}

void containerTable::showFromTail(paintConvexQuad *tmp)
{
	curr = tail;	
	while (curr != NULL)
	{
		cout << "Номер категории фигур: " << curr->key << endl;
		showOneListElements(tmp);
		curr = curr->prev;
	}
}

void containerTable::saveDataInTableToFile()
{
	paintConvexQuad *tmp;
	ofstream fout("DoubleLinkedListTable.txt");
	curr = head;
	while (curr!=NULL)
	{
		fout << curr->key << " ";
		for (int i = 0; i < 5; i++)
		{
			while (curr->quads[i] == NULL) i++;
			tmp = curr->quads[i];
			fout << tmp->quad->Get_diagonal1() << " "
				 << tmp->quad->Get_diagonal2() << " "
				 << tmp->quad->Get_angle() << endl;			
		}
		curr = curr->next;
	}	
}

void containerTable::writeDataFromFileToTable()
{
	paintConvexQuad *tmp;
	double d1, d2, angle;
	ifstream fin("DoubleLinkedListTable.txt");
	if (!fin.is_open()) throw 1;
	while (fin.peek() != EOF)
	{		
		int mark;
		fin >> mark;
		createNode(mark);
		for (int i = 0; fin.peek() != '\n'&&i < 5; i++)
		{
			tmp = new paintConvexQuad();
			curr->quads[i] = tmp;
			fin >> d1;
			fin >> d2;
			fin >> angle;
			tmp->quad->Set_diagonal1(d1);
			tmp->quad->Set_diagonal2(d2);
			tmp->quad->Set_angle(angle);
		}				
	}
}

containerTable::~containerTable()
{	
	while (head)
	{		
		curr = head->next;		
		delete head;
		head = curr;
	}	
}
