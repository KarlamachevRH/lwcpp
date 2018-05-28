#pragma once
#include "paintConvexQuad.h"

struct BSTNode
{
	int cnt;							 // Количество вершин в дереве

	paintConvexQuad *paintconvexQuad;	// Данные - объект - фигура

	BSTNode *parent;

	BSTNode *l, *r;					// Левый и правый потомки

	BSTNode();
	BSTNode(paintConvexQuad * paintconvexQuad);
	~BSTNode();
};