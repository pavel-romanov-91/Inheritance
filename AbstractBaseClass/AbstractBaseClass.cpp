#include<iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0;
};
class GroundVehicle :public Vehicle
{

};

class Car :public GroundVehicle
{
public:
	void move()
	{
		cout << "Машина едит на четырех колесах (как минимум)" << endl;
	}
};

class Bike :public GroundVehicle
{
public:
	void move()
	{
		cout << "Мотоцикл едит на двух колесах" << endl;
	}
};

class AirVehicle :public Vehicle
{
	int height;
public:
	virtual void take_off() = 0;
};
class Helicopter :public AirVehicle
{
public:
	void move()
	{
		cout << "Вертолет на винте" << endl;
	}
	void take_off()
	{
		cout << "" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Vehicle v; //Не возможно создать экземпляр абстрактного класса
	//GroundVehicle gv;
	Car bmw;
	Bike hd;
	bmw.move();
	hd.move();

	Helicopter apache;
	apache.take_off();
	apache.move();
}