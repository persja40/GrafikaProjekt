#include "Size.h"


Size::Size(const unsigned & x, const unsigned & y)
{
}

Size::~Size()
{
}

void Size::setSize(const unsigned & x, const unsigned & y)
{
	this->x = x;
	this->y = y;
}

void Size::setX(const unsigned & x)
{
	this->x = x;
}

void Size::setY(const unsigned & y)
{
	this->y = y;
}

unsigned Size::getY() const
{
	return this->y;
}

unsigned Size::getX() const
{
	return this->x;
}
