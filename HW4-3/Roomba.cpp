#include "Robot.h"
#include "Roomba.h"

Roomba::Roomba():Robot(){}
Roomba::Roomba(int newStrength, int newHit):Robot(newStrength,newHit){}

int Roomba::getDamage()	//This function outputs and returns the damage this robot can inflict in one round of combat.
{	
	int damage=0;
	
	for(int i=0;i<2;i++)	//  Roomba robots are very fast, so they get to attack twice
	{	
		damage += (rand() % Robot::getterStrength()) + 1;	
	}
	
	cout << getType() << " attacks for " << damage << " points!" << endl;

	return damage;
}

string Roomba::getType()
{
	return "roomba";
}
