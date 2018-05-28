#pragma once
#include "LinkedHashEntry.h"

//класс контейнер - хеш-таблица
class hashingWithChains
{	
	int hashTableSize;	
	LinkedHashEntry *hashTable;
	LinkedHashEntry *curr;

public:

	hashingWithChains(int size);
	~hashingWithChains();

	int searchEntryAddress(int key, int hashTableSize); //хеш-функция поиска адреса ячейки хеш-таблицы
	
	void addShape(paintConvexQuad *paintQuad);//добавление фигуры в хеш-таблицу

	int enterKey(); //методы поиска и удаления фигуры в хеш-таблице
	int enterNodeNumber();	
	void deleteShape();
	
	void showOneListElements(int key); //методы вывода данных объектов-фигур на экран
	void showAllTableElementsData();
	
	void saveDataInTableToFile();
	void readDataFromFileToTable();
};