#ifndef COURSE_H_
#define COURSE_H_

using namespace std;

#include <iostream>


namespace PA3{
	class Student;
class Course
{
	public:
		Course();
		Course(string,string);
		Course(const Course&);
		
		~Course();
		
		Course& operator=(const Course&);

		string getterName()const;
		string getterCode()const;
		int getterUsed()const;
		int getterCapacity()const;

		void setterName(string);
		void setterCode(string);
		void setterUsed(int);
		void setterCapacity(int);


	private:
		string name;
		string code;
		Student** students;
		int used=0;
		int capacity;



};

class Student
{
	public:
		Student();
		Student(string,int);
		Student(const Student&);
		
		~Student();
		
		Student& operator=(const Student& );
		
		string getterName()const;
		int getterID()const;
		int getterUsed()const;
		int getterCapacity()const;

		void setterName(string);
		void setterID(int);
		void setterUsed(int);
		void setterCapacity(int);


	private:
		string name;
		int ID;
		Course* courses;
		int used=0;
		int capacity;



};
}











#endif