#pragma warning(disable:4326)
#include<iostream>

using namespace std;


class Shape
{
public:
	virtual ~Shape(){}

	virtual double get_parametr()const = 0;
	virtual double get_area()const = 0;
	virtual void draw()const = 0;
};

class Square :public Shape
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	const double& set_side(double side)
	{
		if (side <= 0)side = 4;
		this->side = side;
		return this->side;
	}
	Square(double size)
	{
		set_side(side);
	}
	~Square(){}
	double get_area()const
	{
		return side * side;
	}
	double get_parametr()const
	{
		return side * 4;
	}
	void draw()const
	{
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
};

class Rectengel :public Shape
{
private:
	double height, width;
public:
	double get_height()
	{
		return height;
	}
	double get_width()
	{
		return width;
	}
	const double& set_height(double height)
	{
		if (height <= 0)height = 5;
		this->height = height;
		return this->height;
	}
	const double& set_width(double width)
	{
		if (width <=0)width = 4;
		this->width = width;
		return this->height;
	}
	Rectengel(double height, double width) :Shape()
	{
		set_height(height);
		set_width(width);
		cout << this << endl;
	}
	~Rectengel(){}
	double get_area()const
	{
		return (height * width);
	}
	double get_parametr()const
	{
		return (height + width) * 2;
	}
	void draw()const
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Square square(4);
	cout << "Сторона квадрата\t" << square.get_side() << endl;
	cout << "Площадь квадрата\t" << square.get_area() << endl;
	cout << "Периметр квадрата\t" << square.get_parametr() << endl;
	square.draw();
	
	Rectengel rectengel(4,7);
	cout << "Сторона квадрата\t" << rectengel.get_height() << endl;
	cout << "Сторона квадрата\t" << rectengel.get_width() << endl;
	cout << "Площадь квадрата\t" << rectengel.get_area() << endl;
	cout << "Периметр квадрата\t" << rectengel.get_parametr() << endl;
	rectengel.draw();
	
}