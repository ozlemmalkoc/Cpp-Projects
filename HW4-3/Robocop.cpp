#include "Human.h"
#include "Robocop.h"


Robocop::Robocop():Human(){}
Robocop::Robocop(int newStrength, int newHit):Human(newStrength,newHit){}


int Robocop::getDamage()	//This function outputs and returns the damage this robot can inflict in one round of combat.
{	
	int damage;
	
	if(rand()%100<10)	// Robocop robots have a 10% chance of inflicting a tactical nuke attack which is an additional 50 damage points.
	{	
		damage=((rand() % Human::getterStrength()) + 1)+50; 
	}
	else
	{	
		damage=(rand() % Human::getterStrength()) + 1 ;
	}
		cout << getType() << " attacks for " << damage << " points!" << endl;

	return damage;
}

string Robocop::getType()
{
	return "robocop";
}
