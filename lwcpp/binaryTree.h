#pragma once
#include "BSTNode.h"

class binaryTree
{	
	BSTNode *root;	
	BSTNode *temp;

public:
	
	binaryTree();
	binaryTree(paintConvexQuad * p);

	void clearTree(BSTNode *&root);
	~binaryTree();

	BSTNode *&getRoot();	
	
	// Включение в двоичное дерево
	void insert(BSTNode *& root, BSTNode *parent, paintConvexQuad * paintconvexQuad);	

	// Вывод данных объектов в дереве
	void scan(BSTNode *&root);

	int writeChoiceToDeleteShape();	

	// Поиск вершины с заданным значением 
	BSTNode *&search(BSTNode *&node, int key);

	void deleteShape(BSTNode *&root, int k);
	void deleteNode(BSTNode *&node);

	void saveData(BSTNode *& root);

	void saveDataInTreeToFile(BSTNode *&root, int cnt);

	void readData(BSTNode *& root, BSTNode * parent, ifstream &fin, int ch, int mark, int readCnt);
	
	void readDataFromFileToTree(BSTNode *&root, BSTNode *parent);
};