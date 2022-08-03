#include "SchoolManagementSystem.h"

using namespace PA3;
using namespace std;

int main()
{	
	SchoolManagementSystem a;
	string input,input2,input3;
	input="ozlem malkoc 19";
	input2="ayse yildiz 20";
	input3="CSE241 Object Oriented Programming";

	a.add_student(input);
	a.add_student(input2);
	
	a.add_course(input3);
	

	a.menu();

return 0;	
}