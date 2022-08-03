#include "SchoolManagementSystem.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace PA3
{	
	int SchoolManagementSystem::courseMenu0()
	{	
		int choice;
		string input;
		
		while(true)
		{
			cout<<"0 up"<<endl;
			cout<<"1 delete_course"<<endl;
			cout<<"2 list_students_registered_to_the_selected_course"<<endl;
		
			cin>>choice;
			
			if(choice==0)
				return 0;
			else if(choice==1)
			{	
				this->delete_course(input);
				return 0;
			}
			else if(choice==3)
			{		
				
			}
		}
	}

	int SchoolManagementSystem::courseMenu()
	{
		int choice=0;
		string input;
		
		while(true)
		{
			cout<<"0 up"<<endl;
			cout<<"1 add_course"<<endl;
			cout<<"2 select_course"<<endl;
			cin>>choice;
			
			if(choice==0)
				return 0;
			else if(choice==1)
			{	
				cin.ignore();
				getline(cin,input);
				this->add_course(input);	
			}
			else if(choice==2)
			{	
				courseMenu0();
			}
		}
	}
	
	int SchoolManagementSystem::studentMenu0()
	{	
		int choice;
		string input;
		
		while(true)
		{
			cout<<"0 up"<<endl;
			cout<<"1 delete_student"<<endl;
			cout<<"3 add_selected_student_to_a_course"<<endl;
			cout<<"4 drop_selected_student_from_a_course"<<endl;
			
			cin>>choice;
			
			if(choice==0)
				return 0;
			else if(choice==1)
			{	
				this->delete_student(input);
				return 0;
			}
			else if(choice==3)
			{	
				
			}
			else if(choice==4)
			{
			}	
		}
	}
	
	int SchoolManagementSystem::studentMenu()
	{	
		int choice=0;
		string input;
		
		while(true)
		{
			cout<<"0 up"<<endl;
			cout<<"1 add_student"<<endl;
			cout<<"2 select_student"<<endl;
			cin>>choice;
			
			if(choice==0)
				return 0;
			else if(choice==1)
			{	
				cin.ignore();
				getline(cin,input);
				this->add_student(input);
			}
			else if(choice==2)
			{	
				studentMenu0();	
			}
		}

	}
	
	SchoolManagementSystem::SchoolManagementSystem():usedofCourse(0),usedofStudent(0),capacityofCourse(10),capacityofStudent(10)
	{
		coursesx= new Course*[capacityofCourse];
		studentsx=new Student*[capacityofStudent];
	}
	
	SchoolManagementSystem::~SchoolManagementSystem()
	{
		delete [] coursesx;
		delete [] studentsx;
	}

	int SchoolManagementSystem::getterUsedofCourse()const{return usedofCourse;}
	int SchoolManagementSystem::getterUsedofStudent()const{return usedofStudent;}
	int SchoolManagementSystem::getterCapacityofStudent()const{return capacityofStudent;}
	int SchoolManagementSystem::getterCapacityofCourse()const{return capacityofCourse;}

	void SchoolManagementSystem::setterUsedofCourse(int _usedofCourse)
	{
		usedofCourse=_usedofCourse;
	}

	void SchoolManagementSystem::setterUsedofStudent(int _usedofStudent)
	{
		usedofStudent=_usedofStudent;
	}

	void SchoolManagementSystem::setterCapacityofStudent(int _capacityofStudent)
	{
		capacityofStudent=_capacityofStudent;
	}

	void SchoolManagementSystem::setterCapacityofCourse(int _capacityofCourse)
	{
		capacityofCourse=_capacityofCourse;
	}

	void SchoolManagementSystem::add_student(string input)
	{	
		string token,nameofStudent;
		int IDofStudent;
		
		istringstream ss(input);
		
		getline(ss,token,' ');
		nameofStudent=token;
		nameofStudent+=' ';
		getline(ss,token,' ');
		nameofStudent+=token;
		
		getline(ss, token);
		
		IDofStudent=stoi(token);
		
		Student * n=new Student(nameofStudent,IDofStudent);
		
		if(usedofStudent<capacityofStudent)
		{	
			studentsx[usedofStudent]=n;
		}
		else
		{
			Student ** temp=new Student*[capacityofStudent*2];

			for(int i=0;i<usedofStudent;i++)
			{
				temp[i]=studentsx[i];
			}
			delete [] studentsx;
			studentsx=temp;
			capacityofStudent*=2;
			studentsx[usedofStudent]=n;
			
		}
		usedofStudent++;
	}

int SchoolManagementSystem::delete_student(string input)
{	if(usedofStudent==0)
	{
	
		return 0;
	}
	string token,nameofStudent;
		int IDofStudent;
		
	
		
		istringstream ss(input);
		
		getline(ss,token,' ');
		nameofStudent=token;
		nameofStudent+=' ';
		getline(ss,token,' ');
		nameofStudent+=token;
		
		getline(ss, token);
		
		IDofStudent=stoi(token);
		
	for(int i=0;i<usedofStudent;i++)
	{
		if(studentsx[i]->getterName()==nameofStudent && studentsx[i]->getterID()==IDofStudent)
			studentsx[i]=nullptr;
	

	}
	Student ** temp=new Student*[capacityofStudent-1];
	for(int i=0,k=0;i<usedofStudent;i++)
	{	
		if(studentsx[i]!=nullptr)
			temp[k++]=studentsx[i];
	}
	delete [] studentsx;
	studentsx=temp;
	capacityofStudent--;
	usedofStudent--;
	return 1;

}

void SchoolManagementSystem::delete_course(string input)
{
	string token,nameofCourse,CodeofCourse;
	
	istringstream ss(input);
		
	getline(ss,token,' ');
	CodeofCourse=token;
	
	for(int i=0;i<2;i++)
	{
		getline(ss,token,' ');
		nameofCourse+=token;
		nameofCourse+=' ';
	}
	getline(ss,token,' ');
	nameofCourse+=token;

	for(int i=0;i<usedofCourse;i++)
	{
		if(coursesx[i]->getterName()==nameofCourse && coursesx[i]->getterCode()==CodeofCourse)
			coursesx[i]=nullptr;
		
	}
	
	Course ** temp=new Course*[capacityofCourse-1];
	
	for(int i=0,k=0;i<usedofCourse;i++)
	{	
		if(coursesx[i]!=nullptr)
			temp[k++]=coursesx[i];
	}
	
	delete [] coursesx;
	coursesx=temp;
	capacityofCourse--;
	usedofCourse--;

}

void SchoolManagementSystem::add_course(string input)
{	
		string token,nameofCourse,CodeofCourse;
	
		istringstream ss(input);
		
		getline(ss,token,' ');
		CodeofCourse=token;
		
		for(int i=0;i<2;i++)
		{
			getline(ss,token,' ');
			nameofCourse+=token;
			nameofCourse+=' ';
		}
		getline(ss,token,' ');
		nameofCourse+=token;
		
		Course * n=new Course(nameofCourse,CodeofCourse);
		
		if(usedofCourse<capacityofCourse)
		{	
			coursesx[usedofCourse]=n;
		}
		else
		{
			Course ** temp=new Course*[capacityofCourse*2];

			for(int i=0;i<usedofCourse;i++)
			{
				temp[i]=coursesx[i];
				

			}
			delete [] coursesx;
				coursesx=temp;
				capacityofCourse*=2;
				coursesx[usedofCourse]=n;
		}
		usedofCourse++;
		
}

void SchoolManagementSystem::list_all_students()
{	
	for(int i=0;i<usedofStudent;i++)
	{	
		cout<<this->studentsx[i]->getterName()<<endl;
	}
}
void SchoolManagementSystem::list_all_courses()
{
	for(int i=0;i<usedofCourse;i++)
	{	
		cout<<this->coursesx[i]->getterName()<<endl;
	}
}


void SchoolManagementSystem::menu()
{
	int choice;

	while (true)
	{
		cout<< "0 exit" << endl
			<< "1 student" << endl
			<< "2 course" << endl
			<< "3 list_all_students " << endl
			<< "4 list_all_courses" << endl << ">>";
		cin >> choice;

		switch (choice)
		{
		case 0: exit(1);
			
			break;

		case 1:	
			studentMenu();
			break;

		case 2: 
			courseMenu();
			
			break;

		case 3:		
			this->list_all_students();
			break;

		case 4:		
			this->list_all_courses();
			break;
		
		}
	}
}



}
