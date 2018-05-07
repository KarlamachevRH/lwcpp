#pragma once
#include "paintConvexQuad.h"

//структура - элемент таблицы - двунаправленного списка
struct CNode
{
	int key;
	paintConvexQuad *quads[5]; //массив для хранения объектов - фигур
	CNode *next;
	CNode *prev;
	CNode();	
	~CNode();
};