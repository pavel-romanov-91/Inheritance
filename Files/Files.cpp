//#define
#include<iostream>
#include<fstream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

void main()
{
	setlocale(LC_ALL, "");

	std::ifstream fin;
	fin.open("File.txt");
	if (fin.is_open())
	{
		//TODO: read file
		const int n = 22256;
		char buffer[n] = {};
		while (!fin.eof()) //eof()-end of file
		{
			//fin >> buffer;
			fin.getline(buffer, n);
			cout << buffer << endl;
		}
	}
	else
	{
		std::cerr << "Error: file not fond" << endl;
	}
	fin.close();
	system("notepad File.txt");
}