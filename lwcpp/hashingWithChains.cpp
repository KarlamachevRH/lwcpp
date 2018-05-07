#pragma once
#include "hashingWithChains.h"


hashingWithChains::hashingWithChains(int size)
{
	hashTableSize = size;
	hashTable = new LinkedHashEntry[size];
	for (int i = 0; i < size; i++)
	{
		hashTable[i].setKey(i);
	}
}

hashingWithChains::~hashingWithChains()
{
	for (int i = 0; i < hashTableSize; i++)
	{
		LinkedHashEntry *curr = hashTable[i].getNext();
		while (curr)
		{
			LinkedHashEntry *tmp;
			tmp = curr->getNext();
			delete curr;
			curr = tmp;
		}		
	}
	delete[]hashTable;
}

int hashingWithChains::searchEntryAddress(int key, int hashTableSize)
{
	return key % hashTableSize;
}

void hashingWithChains::addShape(paintConvexQuad *paintQuad)
{
	int i = searchEntryAddress(paintQuad->quad->mark, hashTableSize);
	int cnt = hashTable[i].shapesCnt;

	if (hashTable[i].paintconvexQuad == NULL) hashTable[i].paintconvexQuad = paintQuad;
	else
	{
		curr = hashTable[i].next;
		while (curr->next)
		{
			curr = curr->next;
			cnt++;
		}
	}
	cnt++;
	curr->next = new LinkedHashEntry(i, cnt, paintQuad);	
}

int hashingWithChains::enterKey()
{
	int key;
	cout << "Введите идентификатор удаляемых фигур:\n"
		<< "Если d1 < d2 - цифра 0\n"
		<< "Если d1 > d2 - цифра 1\n"
		<< "Если d1 = d2 - цифра 2" << endl;
	do {
		cin >> key;
	} while (key < 0 && key > 2);
	return key;
}

int hashingWithChains::enterNodeNumber()
{
	int number;
	cout << "Введите номер удаляемой фигуры: " << endl;
	cin >> number;
	return number;
}

void hashingWithChains::deleteShape()
{
	int key = enterKey(); //ключ - идентификатор объектов
	int hashTableCell = searchEntryAddress(key, hashTableSize);	//поиск хеш-значения по ключу
	int cnt = enterNodeNumber();	

	LinkedHashEntry *tmp;
	curr = &hashTable[hashTableCell];
	while (curr->shapesCnt != cnt)
	{
		tmp = curr;
		curr = curr->next;
	}
	tmp->next = curr->next;
	while (tmp)
	{
		tmp = tmp->next;
		tmp->shapesCnt--;
	}	
	delete curr;
	curr = NULL;
}

void hashingWithChains::showOneListElements(int key)
{
	curr = &hashTable[key];
	while (curr)
	{
		cout << "Номер фигуры: " << curr->shapesCnt << endl
			<< "Длина диагонали 1 выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_diagonal1() << endl
			<< "Длина диагонали 2 выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_diagonal2() << endl
			<< "Величина угла между диагоналями выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_angle() << endl;
		curr = curr->next;
	}
}

void hashingWithChains::showAllTableElementsData()
{
	int key;
	if (hashTable)
	{	
		for (int i = 0; i < hashTableSize; i++)
		{
			key = searchEntryAddress(i, hashTableSize);
			showOneListElements(key);
		}		
	}
	else cout << "Нет данных в хеш-таблице" << endl
		<< "Нажмите Esc для возврата" << endl;
}

void hashingWithChains::saveDataInTableToFile()
{
	ofstream fout("HashTable.txt");
	for (int i = 0; i < hashTableSize; i++)
	{
		curr = &hashTable[i];
		while (curr)
		{
			fout << curr->key << " " << curr->shapesCnt << " "				
				 << curr->paintconvexQuad->quad->Get_diagonal1() << " "
				 << curr->paintconvexQuad->quad->Get_diagonal2() << " "
				 << curr->paintconvexQuad->quad->Get_angle() << endl;
			curr = curr->next;
		}
	}	
}

void hashingWithChains::readDataFromFileToTable()
{	
	double d1, d2, angle;
	ifstream fin("HashTable.txt");
	if (!fin.is_open()) throw 1;
	while (fin.peek() != EOF)
	{
		int key;
		int shapesCnt;
		
		fin >> key;
		fin >> shapesCnt;
		curr = &hashTable[key];
		curr->key = key;		

		while(fin.peek() != '\n')
		{
			fin >> d1;
			fin >> d2;
			fin >> angle;
			curr->paintconvexQuad->quad->Set_diagonal1(d1);
			curr->paintconvexQuad->quad->Set_diagonal2(d2);
			curr->paintconvexQuad->quad->Set_angle(angle);
			
			paintConvexQuad *paintQuad = new paintConvexQuad();
			curr->next = new LinkedHashEntry(key, shapesCnt, paintQuad);
			curr = curr->next;
			fin >> curr->key >> curr->shapesCnt;
		}
	}
}