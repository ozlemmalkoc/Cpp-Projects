#include "Course.h"
#include <string>
#include<iostream>

using namespace std;
namespace PA3{
Course::Course():name(""),code(""),used(0),capacity(10)
{
	students=new Student*[capacity];
}

Course::Course(string _name,string _code):name(_name),code(_code),used(0),capacity(10)
{
	students=new Student*[capacity];
}

Course::Course(const Course& other):name(other.getterName()),code(other.getterCode()),used(other.getterUsed()),capacity(other.getterCapacity())
{
	students=new Student*[capacity];

	for(int i=0;i<used;i++)
	{	
		students[i]->setterName(other.students[i]->getterName());
		students[i]->setterID(other.students[i]->getterID());
		students[i]->setterUsed(other.students[i]->getterUsed());
		students[i]->setterCapacity(other.students[i]->getterCapacity());
	
	}
}


Course& Course::operator=(const Course& other)
{
	if(capacity!=other.getterCapacity())
	{
		delete [] students;
		students=new Student*[other.getterCapacity()];

	}
	capacity=other.getterCapacity();
	used=other.getterUsed();
	name=other.getterName();
	code=other.getterCode();

	for(int i=0;i<used;i++)
	{	
		students[i]->setterName(other.students[i]->getterName());
		students[i]->setterID(other.students[i]->getterID());
		students[i]->setterUsed(other.students[i]->getterUsed());
		students[i]->setterCapacity(other.students[i]->getterCapacity());
	}
	return *this;
}
Course::~Course()
{
	delete [] students;
}

string Course::getterName()const
{
	return name;
}

int Course::getterCapacity()const
{
	return capacity;
}

string Course::getterCode()const
{
	return code;
}

int Course::getterUsed()const
{
	return used;
}

void Course::setterName(string _name)
{
	name=_name;
}

void Course::setterCode(string _code)
{
	code=_code;
}
void Course::setterUsed(int _used)
{
	used=_used;
}
void Course::setterCapacity(int _capacity)
{
	capacity=_capacity;
}
}