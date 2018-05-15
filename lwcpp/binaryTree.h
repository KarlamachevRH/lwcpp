#pragma once
#include "BSTNode.h"

class binaryTree
{	
	BSTNode *root;
	BSTNode *curr; 
	BSTNode *temp;

public:
	
	binaryTree();
	binaryTree(paintConvexQuad * p);

	void clearTree();
	~binaryTree();

	void setTempPtrs();	

	// Поиск вершины с заданным значением 
	void search(int key);

	// Включение в двоичное дерево
	void insert(BSTNode * parent, paintConvexQuad *paintconvexQuad);

	// Вывод данных объектов в дереве
	void scan();

	int writeChoiceToDeleteShape();	
	void deleteShape(int k);
	void deleteNode();

	void saveDataInTreeToFile();
	void readDataFromFileToTree(BSTNode *parent);
};