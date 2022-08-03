#include "Robot.h"
#include "Bulldozer.h"
#include "Roomba.h"
#include "Human.h"
#include "Optimusprime.h"
#include "Robocop.h"
#include <cstdlib>
#include <ctime>

using namespace std;



int main()
{	
	srand(time(NULL));
	
	Bulldozer a(20,60);
	Roomba b(60,20);
	Robocop c(70,50);
	Optimusprime d(40,52);
	Roomba e;
	Optimusprime f;

	cout<<"MATCH 1"<<endl<<endl;
	match(a,b);
	
	cout<<endl<<"MATCH 2"<<endl<<endl;
	match(c,d);
	
	cout<<endl<<"MATCH 3"<<endl<<endl;
	match(e,f);

	return 0;

}