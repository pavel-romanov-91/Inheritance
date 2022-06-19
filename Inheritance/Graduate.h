#pragma once

#include"Header.h"
#include"Student.h"

class Graduate :public Student
{
	std::string diplom;
public:
	const std::string& get_diplom()const
	{
		return diplom;
	}
	void set_diplom(const std::string& diplom)
	{
		this->diplom = diplom;
	}

	//			Constructors:

	Graduate
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& speciality, const std::string& group, unsigned int year, double rating, double attendance,
		const std::string& diplom
	) :Student
	(
		last_name, first_name, age,
		speciality, group, year, rating, attendance
	)
	{
		set_diplom(diplom);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//					Methods:

	std::ostream& print(std::ostream& os)const
	{
		return Student::print(os) << "Тема диплома: " << diplom << endl;
	}
};
