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

int LinkedHashEntry::getKey()
{
	return key;
}

void LinkedHashEntry::setValue(paintConvexQuad *paintconvexQuad)
{
	this->paintconvexQuad = paintconvexQuad;
}

paintConvexQuad* LinkedHashEntry::getValue()
{
	return paintconvexQuad;
}

LinkedHashEntry * LinkedHashEntry::getNext()
{
	return next;
}

void LinkedHashEntry::setNext(LinkedHashEntry * next)
{
	this->next = next;
}

LinkedHashEntry::~LinkedHashEntry()
{
	if (paintconvexQuad) delete paintconvexQuad;
}