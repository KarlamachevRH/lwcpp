#include "hashingWithChains.h"


hashingWithChains::hashingWithChains(int size)
{
	hashTableSize = size;	
	hashTable = new LinkedHashEntry[size];
	curr = hashTable;
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
			tmp = curr->next;
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
		curr = &hashTable[i];
		while (curr->next)
		{
			curr = curr->next;
			cnt++;
		}
		cnt++;
		curr->next = new LinkedHashEntry(i, cnt, paintQuad);
	}		
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
	paintConvexQuad *p = NULL;
	
	curr = &hashTable[hashTableCell];
	LinkedHashEntry *tmp = curr;
	while (curr != NULL && (curr->shapesCnt != cnt || curr->paintconvexQuad == NULL))
	{
		tmp = curr;
		curr = curr->next;
	}

	if (curr == NULL)
	{
		cout << "Нет фигуры с введенным номером!" << endl;
		return;
	}
	
	tmp->next = curr->next;
	while (tmp)
	{			
		tmp = tmp->next;
		if(tmp!=NULL)tmp->shapesCnt--;
	}	
	if(curr != &hashTable[hashTableCell]) delete curr;
	else
	{
		p = curr->paintconvexQuad;
		delete p;
		curr->paintconvexQuad = NULL;
	}
	curr = hashTable;
}

void hashingWithChains::showOneListElements(int key)
{
	curr = &hashTable[key];	
	while (curr)
	{		
		if (curr->paintconvexQuad == NULL) curr = curr->next;
		if (curr == NULL) return;

		cout << "Ключ таблицы: " << curr->key << endl
			<< "Номер фигуры: " << curr->shapesCnt << endl
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
		cout << "Вывод данных из хеш-таблицы" << endl;
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
		while (curr!=NULL)
		{
			if (curr->paintconvexQuad != NULL)
			{
				fout << curr->key << " "
					<< curr->paintconvexQuad->quad->Get_diagonal1() << " "
					<< curr->paintconvexQuad->quad->Get_diagonal2() << " "
					<< curr->paintconvexQuad->quad->Get_angle() << "\n";
			}	
			curr = curr->next;
		}
	}	
}

void hashingWithChains::readDataFromFileToTable()
{	
	double d1 = 0, d2 = 0, angle = 0;
	LinkedHashEntry *tmp = NULL;
	ifstream fin("HashTable.txt");
	if (!fin.is_open()) throw 1;
	int key = 0;
	int shapesCnt = 0;	
	int cnt = 0;

	while (fin.peek() != EOF)
	{		
		fin >> key;		
		fin >> d1;

		while (fin.peek() != '\n' && fin.peek() != EOF)
		{		
							
			fin >> d2;
			fin >> angle;	

			cnt++;			
			curr = &hashTable[key];
			while (curr->next != NULL) curr = curr->next;
							
			shapesCnt = curr->shapesCnt;
			if (curr->paintconvexQuad == NULL) curr->paintconvexQuad = new paintConvexQuad();
			else if(curr->paintconvexQuad != NULL)
			{							
				curr->next = new LinkedHashEntry();
				curr->next->paintconvexQuad = new paintConvexQuad();
				curr = curr->next;
				shapesCnt++;
			}			
			curr->key = key;
			curr->shapesCnt = shapesCnt;			
			curr->paintconvexQuad->quad->Set_diagonal1(d1);
			curr->paintconvexQuad->quad->Set_diagonal2(d2);
			curr->paintconvexQuad->quad->Set_angle(angle);	
			curr->paintconvexQuad->quad->mark = key;	
			if (curr->next != NULL)
			{
				while (curr->next)
				{
					curr = curr->next;
					curr->shapesCnt--;
				}				
			}
			if (fin.peek() == EOF) cout << "Конец файла" << endl;				
		}		
	}
	fin.close();
}