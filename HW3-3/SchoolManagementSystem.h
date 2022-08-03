#ifndef SCHOOLMANAGEMENTSYSTEM_H_
#define SCHOOLMANAGEMENTSYSTEM_H_

using namespace std;

#include <iostream>
#include "Student.h"

namespace PA3
{
	class SchoolManagementSystem
	{	
		public:
		SchoolManagementSystem();
		~SchoolManagementSystem();

		int getterUsedofCourse()const;
		int getterUsedofStudent()const;
		int getterCapacityofStudent()const;
		int getterCapacityofCourse()const;

		void setterUsedofCourse(int);
		void setterUsedofStudent(int);
		void setterCapacityofStudent(int);
		void setterCapacityofCourse(int);

		void add_student(string );
		void add_course(string);
		int delete_student(string);
		void delete_course(string);
		void list_all_students();
		void list_all_courses();
		void menu();
		int studentMenu();
		int studentMenu0();
		int courseMenu();
		int courseMenu0();

		private:
			Course ** coursesx;
			Student ** studentsx;
			int usedofCourse;
			int usedofStudent;
			int capacityofCourse;
			int capacityofStudent;
	};

}

#endif