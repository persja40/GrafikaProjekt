#pragma once
class Size
{
private:
	unsigned x, y;

public:
	
	Size(const unsigned & x,const unsigned & y);
	~Size();

	void setSize(const unsigned & x, const unsigned & y);
	void setX(const unsigned & x);
	void setY(const unsigned & y);
	unsigned getY() const;
	unsigned getX() const;
};

