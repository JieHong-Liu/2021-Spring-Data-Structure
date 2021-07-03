#pragma once

class Point
{
public:
	Point()
	{
		this->x = 0;
		this->y = 0;
	}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	// copy constructor
	Point(const Point &p)
	{
		x = p.x;
		y = p.y;
	}
	// assignment overloading
	Point &operator=(const Point &p)
	{
		if (this == &p)
		{
			return *this;
		}
		else
		{
			x = p.x;
			y = p.y;
			return *this;
		}
	}
	bool operator==(const Point &p)
	{
		if (x == p.x && y == p.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}

	void set_x(int x)
	{
		this->x = x;
	}
	void set_y(int y)
	{
		this->y = y;
	}

	Point Point_right()
	{
		Point p = *this;
		p.x = p.x;
		p.y = p.y + 1;
		return p;
	}
	Point Point_left()
	{
		Point p = *this;
		p.x = p.x;
		p.y = p.y - 1;
		return p;
	}
	Point Point_up()
	{
		Point p = *this;
		p.x = p.x - 1;
		p.y = p.y;
		return p;
	}
	Point Point_down()
	{
		Point p = *this;
		p.x = p.x + 1;
		p.y = p.y;
		return p;
	}

private:
	int x;
	int y;
};