#include<iostream>
#include<Windows.h>
#include <cmath>
using namespace std;

#define PI M_PI

namespace Geometry
{
	enum Color
	{
		red=0x000000FF,
		green = 0x0000FF00,
		blue =0x00FF0000,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0XCC,
		console_yellow = 0xEE,
		console_white = 0xFF
	};

	class Shape
	{
	protected:
		Color color;
	public:
		Color get_color()const
		{
			return color;
		}

		Shape(Color color) :color(color) {}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 10;
			this->side = side;
		}
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, get_color());
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << get_side() << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double side_a, side_b;
	public:
		double get_side_a()const
		{
			return side_a;
		}
		double get_side_b()const
		{
			return side_b;
		}
		void set_side_a(double side_a)
		{
			if (side_a <= 0)side_a = 20;
			this->side_a = side_a;
		}
		void set_side_b(double side_b)
		{
			if (side_b <= 0)side_b = 10;
			this->side_b = side_b;
		}
		Rectangle(double side_a, double side_b, Color color) :Shape(color)
		{
			set_side_a(side_a);
			set_side_b(side_b);
		}
		~Rectangle() {}
		double get_area()const
		{
			return side_a * side_b;
		}
		double get_perimeter()const
		{
			return (side_a + side_b) * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 10, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, 100, 100, 300, 200);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона А: " << side_a << endl;
			cout << "Сторона В: " << side_b << endl;
			Shape::info();
		}
	};

	class Circle :public Shape
	{
	private:
		double x, y, radius;
	public:
		double get_x()
		{
			return x;
		}
		double get_y()
		{
			return y;
		}
		double get_radius()
		{
			return radius;
		}
		void set_x(double x)
		{
			if (x < 100)
			{
				x = 100;
			}
			this->x = x;
		}
		void set_y(double y)
		{
			if (y < 100)
			{
				y = 100;
			}
			this->y = y;
		}
		void set_radius(double radius)
		{
			if (radius == 0 || radius==0.0)
			{
				radius = 1;
			}
			this->radius = radius;
		} 
		double get_area()const
		{
			double area = radius * radius;
			return area;
		}
		double get_diametr()const 
		{
			return 2 * this->radius;
		}
		double get_circumference() const 
		{
			return 2 * radius;
		}
		Circle(double x, double y, double radius) : Shape(x, y)
		{
			this->radius = radius;
			cout << this << endl;
		}

		

		void draw_to_console() 
		{
			
		}
		
	};
}




void main()
{
	setlocale(LC_ALL, "");
	Geometry::Square square(5, Geometry::Color::console_red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(50, 30, Geometry::Color::console_red);
	rect.info();
}