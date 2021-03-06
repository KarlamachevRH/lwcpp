﻿#pragma once
#include "paintConvexQuad.h"

//элемент хеш - таблицы
class LinkedHashEntry
{
	friend class hashingWithChains;
private:

	int key;
	int shapesCnt; //счетчик фигур в цепочке
	paintConvexQuad *paintconvexQuad;
	LinkedHashEntry *next;

public:	

	LinkedHashEntry();

	LinkedHashEntry(int key, int shapesCnt, paintConvexQuad *paintconvexQuad);

	void setKey(int key);			

	LinkedHashEntry *getNext();
	
	~LinkedHashEntry();
};