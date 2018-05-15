#include "BSTNode.h"


BSTNode::BSTNode() :cnt(1), paintconvexQuad(NULL), parent(NULL), l(NULL), r(NULL) {}

BSTNode::BSTNode(paintConvexQuad * paintconvexQuad)
{
	parent = l = r = NULL;
	cnt = 1;
	this->paintconvexQuad = paintconvexQuad;
}

BSTNode::~BSTNode()
{
	if (paintconvexQuad != NULL) delete paintconvexQuad;
}
