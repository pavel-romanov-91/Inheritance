#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
#include <math.h>
using namespace std;


namespace Geometry
{
	enum Color
	{
		red=0x000000FF,
		green = 0x0000FF00,
		blue =0x00FF0000,
		yellow = 0x0000FFFF,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0XCC,
		console_yellow = 0xEE,
		console_white = 0xFF
	};

	enum Defaults
	{
		min_start_x = 100,
		max_start_x = 800,
		min_start_y = 50,
		max_start_y = 800,
		min_line_width = 5,
		max_line_width = 20,
		min_line_length = 10,
		max_line_length = 500
	};

	class Shape
	{
	protected:
		Color color;
		int start_x;
		int start_y;
		unsigned int line_width;
	public:
		Color get_color()const
		{
			return color;
		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(int start_x)
		{
			if (start_x < Defaults::min_start_x)this->start_x = Defaults::min_start_x;
			else if (start_x > Defaults::max_start_x)this->start_x = Defaults::min_start_x;
			else this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y < Defaults::min_start_y)this->start_y = Defaults::min_start_y;
			else if (start_y > Defaults::max_start_y)this->start_y = Defaults::min_start_y;
			else this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width < Defaults::min_line_width)this->line_width = Defaults::min_line_width;
			else if (line_width > Defaults::max_line_width)this->line_width = Defaults::max_line_width;
			else this->line_width = line_width;
		}

		Shape(int start_x, int start_y, unsigned int line_width, Color color) :color(color) 
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
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
		Square(double side, int start_x, int start_y, unsigned int line_width, Color color) 
			:Shape(start_x, start_y, line_width, color)
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
		Rectangle(double side_a, double side_b, int start_x, int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
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
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, start_x, start_y, start_x + side_a, start_y + side_b);

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
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius >= 0 && radius <= 500)this->radius = radius;
			else if (radius < 10)this->radius = 10;
			else this->radius = 500;
		} 
		Circle(double radius, int start_x, int start_y, unsigned int line_width, Color color) 
			:Shape(start_x, start_y, line_width, color)
		{
			set_radius(radius);
		}
		~Circle(){}
		double get_area()const
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const
		{
			return M_PI * radius * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, red);
			HBRUSH hBrush = CreateSolidBrush(yellow);
			
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x+radius*2, start_y+radius*2);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << get_radius() << endl;
			Shape::info();
		}
	};


	class Tringel :public Shape
	{
	private:
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		Tringel(double side, double start_x, double start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
		{
			this->side = side;
			cout << this << endl;
		}
		~Tringel() {}

		double get_height()const
		{
			return (sqrt(3) / 2) * side;
		}
		double get_area()const
		{
			return (sqrt(3) / 4) * side * side;
		}
		double get_perimeter()const
		{
			return 3 * side;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, red);
			HBRUSH hBrush = CreateSolidBrush(red);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] = { {start_x, start_y + side}, {start_x + side, start_y + side}, {start_x + side / 2, start_y + side - get_height()} };

			Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника: " << side << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			cout << "Площадь триугольника: " << get_area() << endl;
			cout << "Периметр треугольника: " << get_perimeter() << endl;
			draw();
		}
	};



	class Triangle :public Shape
	{
	public:
		Triangle(int start_x, int start_y, unsigned int line_width, Color color)
			:Shape(start_x,start_y,line_width, color){}
		~Triangle(){}
		virtual double get_height()const = 0;
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < Defaults::min_line_length)this->side = Defaults::min_line_length;
			else if (side > Defaults::max_line_length)this->side = Defaults::max_line_length;
			else this->side = side;
		}
		EquilateralTriangle(double side, int start_x, int start_y, unsigned int line_width, Color color)
			:Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~EquilateralTriangle(){}
		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x, start_y + side},		
				{start_x + side, start_y + side},	
				{start_x + side / 2, start_y + side - get_height()}	
			};

			::Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника: " << side << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
	class IsoscalesTringle :public Triangle
	{
		double base;
		double side;
	public:
		double get_base()const
		{
			return base;
		}
		double get_side()const
		{
			return side;
		}
		void set_base(double base)
		{
			if (base < Defaults::min_line_length)base = Defaults::min_line_length;
			else if (base > Defaults::max_line_length)base = Defaults::max_line_length;
			//if (base >= side * 2)base /= 2;
			this->base = base;
		}
		void set_side(double base)
		{
			if (side < Defaults::min_line_length)side = Defaults::min_line_length;
			else if (side > Defaults::max_line_length)side = Defaults::max_line_length;
			if (side * 2<=base)side *= 2;
			this->side = side;
		}
		IsoscalesTringle& operator()(double base, double side)
		{
			if (base >= side * 2)base = side;
			set_base(base);
			set_side(side);
			return *this;
		}
		IsoscalesTringle(double base, double side, int start_x, int start_y, unsigned int line_width, Color color)
			:Triangle(start_x, start_y, line_width, color)
		{
			operator()(base, side);
		}
		~IsoscalesTringle(){}
		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}
		double get_area()const
		{
			return base * get_height() / 2;
		}
		double get_perimeter()const
		{
			return base + side * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x, start_y + side},
				{start_x + base, start_y + side},
				{start_x + base / 2, start_y + side - get_height()}
			};

			::Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание треунольника: " << base << endl;
			cout << "Сторона треугольника: " << side << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
	class RectangularTringle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < Defaults::min_line_length)this->side = Defaults::min_line_length;
			else if (side > Defaults::max_line_length)this->side = Defaults::max_line_length;
			else this->side = side;
		}
		RectangularTringle(double side, int start_x, int start_y, unsigned int line_width, Color color) :
			Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~RectangularTringle(){}
		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, green);
			HBRUSH hBrush = CreateSolidBrush(green);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x, start_y + side},		
				{start_x + side, start_y + side},	
				{start_x, start_y + side - get_height()}	
			}; 

			::Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника: " << side << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};


}

#define HOM_WORK

void main()
{
	setlocale(LC_ALL, "");
	Geometry::Square square(5, 50, 10, 5, Geometry::Color::console_red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(50, 200, 110, 50, 5, Geometry::Color::console_red);
	rect.info();

	Geometry::Circle circ(50, 650, 150, 15, Geometry::Color::console_red);
	circ.info();
	
	Geometry::Tringel trin(150, 250, 250, 15, Geometry::Color::console_green);
	trin.info();

	Geometry::EquilateralTriangle qtri(150, 700, 300, 5, Geometry::Color::green);
	qtri.info();

	Geometry::IsoscalesTringle itri1(100, 150, 400, 300, 5, Geometry::Color::blue);
	itri1.info();

	Geometry::IsoscalesTringle itri2(100, 175, 900, 200, 5, Geometry::Color::blue);
	itri2.info();
	
	Geometry::RectangularTringle rtri(175, 900, 200, 5, Geometry::Color::console_green);
	rtri.info();

}