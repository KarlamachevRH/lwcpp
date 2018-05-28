#include "LinkedHashEntry.h"


LinkedHashEntry::LinkedHashEntry():key(0), shapesCnt(1), paintconvexQuad(NULL), next(NULL){}

LinkedHashEntry::LinkedHashEntry(int key, int shapesCnt, paintConvexQuad *paintconvexQuad)
{
	this->key = key;
	this->shapesCnt = shapesCnt;
	this->paintconvexQuad = paintconvexQuad;
	this->next = NULL;
}

void LinkedHashEntry::setKey(int key)
{
	this->key = key;
}

LinkedHashEntry * LinkedHashEntry::getNext()
{
	return next;
}

LinkedHashEntry::~LinkedHashEntry()
{
	if (paintconvexQuad) delete paintconvexQuad;
}