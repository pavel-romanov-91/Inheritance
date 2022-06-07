#include<iostream>
#include<string>
using std::cin;
using std::cout;

class Human
{
	std::string last_name;
	std::string First_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
};

void main()
{
	setlocale(LC_ALL, "");

}