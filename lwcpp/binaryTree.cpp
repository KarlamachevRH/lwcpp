#include "binaryTree.h"


binaryTree::binaryTree() :root(NULL), temp(NULL){}

binaryTree::binaryTree(paintConvexQuad *p)
{
	root = new BSTNode(p);
	temp = root;
}

void binaryTree::clearTree(BSTNode *&root)
{			
	if (root!= NULL)
	{
		clearTree(root->l);
		clearTree(root->r);
		delete root;
		root = NULL;
	}	
}

binaryTree::~binaryTree()
{
	clearTree(root);
}

BSTNode *&binaryTree::getRoot() { return root; }

void binaryTree::insert(BSTNode *&root, BSTNode *parent, paintConvexQuad *paintconvexQuad)
{			
	if (root == NULL)
	{
		root = new BSTNode(paintconvexQuad);			
		root->parent = parent;				
		return;
	}
	
	parent = root;
	root->cnt++;		

	if (root->paintconvexQuad->quad->mark >= paintconvexQuad->quad->mark) insert(root->l, parent, paintconvexQuad);
		
	else insert(root->r, parent, paintconvexQuad);	
}

void binaryTree::scan(BSTNode *&root)
{		
	if (root == NULL) return;	

	cout << "Признак-метка фигуры: " << root->paintconvexQuad->quad->mark << endl
		<< "Длина диагонали 1 выпуклого четырехугольника: " << root->paintconvexQuad->quad->Get_diagonal1() << endl
		<< "Длина диагонали 2 выпуклого четырехугольника: " << root->paintconvexQuad->quad->Get_diagonal2() << endl
		<< "Величина угла между диагоналями выпуклого четырехугольника: " << root->paintconvexQuad->quad->Get_angle() << endl;

	scan(root->l);

	scan(root->r);	
}

int binaryTree::writeChoiceToDeleteShape()
{
	int mark;	
	cout << "Введите идентификатор удаляемых фигур:\n"
	<< "Если d1 < d2 - цифра 0\n"
	<< "Если d1 > d2 - цифра 1\n"
	<< "Если d1 = d2 - цифра 2" << endl;
	do {
		cin >> mark;
	} while (mark < 0 && mark > 2);
	return mark;
}

BSTNode *&binaryTree::search(BSTNode *&node, int key)
{
	if (node == NULL) return node;

	if (node->paintconvexQuad->quad->mark == key) return node;

	if (node->paintconvexQuad->quad->mark > key)
	{
		return search(node->l, key);
	}
	else if(node->paintconvexQuad->quad->mark < key)
	{
		return search(node->r, key);
	}
}

void binaryTree::deleteShape(BSTNode *&root, int k)
{	
	/*BSTNode *node = NULL;*/
	if (root == NULL)
	{
		cout << "Лист дерева" << endl;
		return;
	}
	
	BSTNode *&node = search(root, k);
	deleteNode(node);
}

//Удаление узла
void binaryTree::deleteNode(BSTNode *&node)
{	
	if (node->l == NULL && node->r == NULL)
	{
		if(node->parent->l == node) node->parent->l = NULL;
		else node->parent->r = NULL;
		delete node;
		return;
	}
	else if (node->l == NULL) //Если нет левого поддерева
	{		
		BSTNode *right = node->r;
		delete node;
		node = right;		
		return;
	}
	else if(node->r == NULL) //Если нет правого поддерева
	{
		BSTNode *left = node->l;
		delete node;
		node = left;
		return;
	}
	else //Есть оба поддерева
	{ //Ищем минимальный элемент и его родителя
		BSTNode *minParent = node;
		BSTNode *min = node->r;
		while (min->l != NULL)
		{
			minParent = min;
			min = min->l;
		}
		//Удаляем min, подставляя на его место min->r
		if(minParent->l == min)minParent->l = min->r;
		else minParent->r = min->r;	
		node->paintconvexQuad = min->paintconvexQuad;
		delete min;
	}
}

void binaryTree::saveData(BSTNode *&root)
{
	int cnt = 0;
	saveDataInTreeToFile(root, cnt);
}

void binaryTree::saveDataInTreeToFile(BSTNode *&root, int cnt)
{	
	if (cnt == 0) ofstream fout("BinaryTree.txt", ios_base::trunc);
	ofstream fout("BinaryTree.txt", ios_base::app);
	
	if (root == NULL)
	{
		cout << "Лист дерева" << endl;
		return;
	}	

	fout << root->paintconvexQuad->quad->mark << " "		
		<< root->paintconvexQuad->quad->Get_diagonal1() << " "
		<< root->paintconvexQuad->quad->Get_diagonal2() << " "
		<< root->paintconvexQuad->quad->Get_angle() << endl;
	cnt++;
		
	saveDataInTreeToFile(root->l, cnt);
	
	saveDataInTreeToFile(root->r, cnt);
}

void binaryTree::readData(BSTNode *&root, BSTNode *parent, ifstream &fin, int ch, int mark, int readCnt)
{
	double d1, d2, angle;	

	if (ch = fin.get() == EOF) return;

	cout << "Загрузка из файла" << endl;

	if (root == NULL)
	{
		root = new BSTNode();
		root->parent = parent;
	}
	fin.seekg(-1, ios::cur);
	if(readCnt == 0) fin >> mark;
	parent = root;
	root->cnt++;
	
	while (ch = fin.get() != '\n')
	{
		fin.seekg(-1, ios::cur);		
		fin >> d1;
		fin >> d2;
		fin >> angle;

		paintConvexQuad *paintQuad = new paintConvexQuad();
		root->paintconvexQuad = paintQuad;
		root->paintconvexQuad->quad->mark = mark;
		root->paintconvexQuad->quad->Set_diagonal1(d1);
		root->paintconvexQuad->quad->Set_diagonal2(d2);
		root->paintconvexQuad->quad->Set_angle(angle);			
	}	
	readCnt++;
	fin >> mark;

	if (root->paintconvexQuad->quad->mark >= mark) readData(root->l, parent, fin, ch, mark, readCnt);
	if (root->paintconvexQuad->quad->mark < mark) readData(root->r, parent, fin, ch, mark, readCnt);
}

void binaryTree::readDataFromFileToTree(BSTNode *&root, BSTNode *parent)
{		
	ifstream fin("BinaryTree.txt");

	int ch = 0;
	int mark = -1;
	int readCnt = 0;

	if (!fin.is_open()) throw 1;
	else readData(root, parent, fin, ch, mark, readCnt);
	
	cout << "Конец файла данных для бинарного дерева" << endl;	
	fin.close();
}