#pragma once

#include"Header.h"
#include"Human.h"

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, unsigned int year, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, year, rating, attendance

class Student :public Human
{
	std::string speciality;
	std::string group;
	unsigned int year;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	unsigned int get_year()const
	{
		return year;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_year(unsigned int year)
	{
		this->year = year;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//			Constructors:

	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_year(year);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	//					Methods:

	std::ostream& print(std::ostream& os)const
	{
		Human::print(os);
		return os << "Специальность: " << speciality + " " + "Группа: " + group << " " << "Курс: " << year << " " << "Рейтинг: " << rating << " " << "Посещаемость: " << attendance << endl;
	}
};

class Teacher :public Human
{
	std::string speciality;
	unsigned int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}

	//			Constructors:

	Teacher
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& speciality, unsigned int experience
	) :Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//					Methods:

	std::ostream& print(std::ostream& os)const
	{
		Human::print(os);
		return os << "Специальность: " << speciality + " " << "Опыт: " << experience << endl;
	}
};

