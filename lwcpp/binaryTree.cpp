#include "binaryTree.h"


binaryTree::binaryTree() :root(NULL), curr(NULL), temp(NULL){}

binaryTree::binaryTree(paintConvexQuad *p)
{
	root = new BSTNode(p);
	curr = temp = root;
}

void binaryTree::clearTree()
{	
	temp = curr->parent;
	if (curr->l != NULL || curr->r != NULL)
	{
		curr = curr->l;
		clearTree();
		curr = curr->r;
		clearTree();		
	}
	delete curr;
	curr = temp;
}

binaryTree::~binaryTree()
{
	clearTree();
}

void binaryTree::setTempPtrs()
{
	curr = temp = root;
}

void binaryTree::search(int key)
{
	if (root == NULL) return;	

	if (curr->paintconvexQuad->quad->mark == key) return;

	if (curr->paintconvexQuad->quad->mark > key)
	{
		curr = curr->l; 
		search(key);
	}

	curr = curr->r;
	search(key);
}

void binaryTree::insert(BSTNode * parent, paintConvexQuad * paintconvexQuad)
{		
	if (curr == NULL)
	{
		curr = new BSTNode(paintconvexQuad);
		curr->parent = parent;
		return;
	}
	
	parent = curr;
	curr->cnt++;

	if (curr->paintconvexQuad->quad->mark > paintconvexQuad->quad->mark)
	{
		curr = curr->l;
		insert(parent, paintconvexQuad);
	}
	
	else 
	{		
		curr = curr->r;
		insert(parent, paintconvexQuad);
	}
}

void binaryTree::scan()
{	
	if (curr == NULL)
	{
		cout << "Дерево не содержит данных" << endl;
		return;
	}

	cout << "Признак-метка фигуры: " << curr->paintconvexQuad->quad->mark << endl
		<< "Длина диагонали 1 выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_diagonal1() << endl
		<< "Длина диагонали 2 выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_diagonal2() << endl
		<< "Величина угла между диагоналями выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_angle() << endl;

	curr=curr->l;
	scan();

	curr = curr->r;
	scan();
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

void binaryTree::deleteShape(int k)
{
	if (root == NULL)
	{
		cout << "Дерево не содержит данных" << endl;
		return;
	}
	
	search(k);
	deleteNode();	
}

//Удаление узла
void binaryTree::deleteNode()
{
	BSTNode *node = curr;
	if (node->l == NULL) //Если нет левого поддерева
	{		
		BSTNode *right = node->r;
		delete node;
		node = right;
	}
	else if(node->r == NULL) //Если нет правого поддерева
	{
		BSTNode *left = node->l;
		delete node;
		node = left;
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

void binaryTree::saveDataInTreeToFile()
{
	ofstream fout("BinaryTree.txt");
	
	if (root == NULL)
	{
		cout << "Нет данных в дереве" << endl;
		return;
	}

	if (curr == NULL) return;	

	fout << "Признак-метка фигуры: " << curr->paintconvexQuad->quad->mark << " "
		<< "Счетчик фигур: " << curr->cnt << " "
		<< "Длина диагонали 1 выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_diagonal1() << " "
		<< "Длина диагонали 2 выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_diagonal2() << " "
		<< "Величина угла между диагоналями выпуклого четырехугольника: " << curr->paintconvexQuad->quad->Get_angle() << endl;

	curr = curr->l;
	saveDataInTreeToFile();

	curr = curr->r;
	saveDataInTreeToFile();
}

void binaryTree::readDataFromFileToTree(BSTNode *parent)
{
	double d1, d2, angle;
	int mark;
	int cnt;	
	ifstream fin("BinaryTree.txt");
	if (!fin.is_open()) throw 1;

	if (fin.peek() == EOF) return;

	if (curr == NULL)
	{
		curr = new BSTNode;
		curr->parent = parent;
	}
	parent = curr;
	
	while (fin.peek() != '\n')
	{		
		fin >> mark;
		fin >> cnt;
		fin >> d1;
		fin >> d2;
		fin >> angle;

		paintConvexQuad *paintQuad = new paintConvexQuad();
		curr->paintconvexQuad = paintQuad;
		curr->paintconvexQuad->quad->mark = mark;
		curr->cnt = cnt;
		curr->paintconvexQuad->quad->Set_diagonal1(d1);
		curr->paintconvexQuad->quad->Set_diagonal2(d2);
		curr->paintconvexQuad->quad->Set_angle(angle);
	}
	
	curr = curr->l;
	readDataFromFileToTree(parent);

	curr = curr->r;
	readDataFromFileToTree(parent);
}
