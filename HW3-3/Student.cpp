#include "Student.h"
#include <string>
#include<iostream>

using namespace std;

namespace PA3{

Student::Student():name(" "),ID(0),used(0),capacity(10)
{	
	courses=new Course*[capacity];

}

Student::Student(string _name ,int _ID):name(_name),ID(_ID),used(0),capacity(10)
{
	courses=new Course*[capacity];
}

Student::Student(const Student& other):name(other.getterName()),ID(other.getterID()),used(other.getterUsed()),capacity(other.getterCapacity())
{
	courses=new Course*[capacity];

	for(int i=0;i<used;i++)
	{	
		courses[i]->setterName(other.courses[i]->getterName());
		courses[i]->setterCode(other.courses[i]->getterCode());
		courses[i]->setterUsed(other.courses[i]->getterUsed());
		courses[i]->setterCapacity(other.courses[i]->getterCapacity());
	
	}
}

Student& Student::operator=(const Student& other)
{
	if(capacity!=other.getterCapacity())
	{
		delete [] courses;
		courses=new Course*[other.getterCapacity()];
	}
	capacity=other.getterCapacity();
	used=other.getterUsed();
	name=other.getterName();
	ID=other.getterID();

	for(int i=0;i<used;i++)
	{	
		courses[i]->setterName(other.courses[i]->getterName());
		courses[i]->setterCode(other.courses[i]->getterCode());
		courses[i]->setterUsed(other.courses[i]->getterUsed());
		courses[i]->setterCapacity(other.courses[i]->getterCapacity());
	
	}
	return *this;
}

Student::~Student()
{
	delete [] courses;
}
string Student::getterName()const
{
	return name;
}

int Student::getterCapacity()const
{
	return capacity;

}
int Student::getterID()const
{
	return ID;
}
int Student::getterUsed()const
{
	return used;
}

void Student::setterName(string _name)
{
	name=_name;
}
void Student::setterID(int _ID)
{
	ID=_ID;
}
void Student::setterUsed(int _used)
{
	used=_used;
}

void Student::setterCapacity(int _capacity)
{
	capacity=_capacity;
}



}