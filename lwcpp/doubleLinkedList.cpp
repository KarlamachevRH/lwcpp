#include "doubleLinkedList.h"

CNode::CNode()
{
	key = 0;
	next = NULL;
	prev = NULL;
	for (int i = 0; i < 5; i++)
	{
		quads[i] = NULL;
	}
}
CNode::~CNode()
{
	for (int i = 0; i < 5; i++)
	{
		if (quads[i] != NULL) delete quads[i];
	}
}