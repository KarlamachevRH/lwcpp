#pragma once
#include "paintConvexQuad.h"

struct CNode
{
	int key;
	paintConvexQuad *quads[5];
	CNode *next;
	CNode *prev;
	CNode();	
	~CNode();
};