#pragma once
#include "doubleLinkedList.h"


class containerTable
{
private:		
	CNode *head, *tail;
	CNode *curr;	 

public:
	containerTable();
	void addShapeToTable(paintConvexQuad *paintQuad);
	void searchNode(int mark);
	int searchFreeCell();
	void createNode(int mark);	
	void deleteTableElement(); //удаление фигуры в таблице
	void deleteShape();	
	void showAllListsElements();
	void showOneListElements(paintConvexQuad *tmp);
	void showFromHead(paintConvexQuad *tmp);
	void showFromTail(paintConvexQuad *tmp);
	void saveDataInTableToFile();
	void writeDataFromFileToTable();	
	~containerTable();
};