#include "Human.h"
#include "Optimusprime.h"


Optimusprime::Optimusprime():Human(){}
Optimusprime::Optimusprime(int newStrength, int newHit):Human(newStrength,newHit){}


int Optimusprime::getDamage()	//This function outputs and returns the damage this robot can inflict in one round of combat.
{
	int damage;

	if(rand()%100<10)	// Robocop robots have a 10% chance of inflicting a tactical nuke attack which is an additional 50 damage points.
	{	
		damage=((rand() % Human::getterStrength()) + 1)+50;
		
		if(rand()%100<15)	//  With a 15% chance optimusprime robots inflict a strong attack that doubles the normal amount of damage.
			damage*=2;
	}
	else
	{	
		damage=(rand() % Human::getterStrength()) + 1 ;
		
		if(rand()%100<15)	 // With a 15% chance optimusprime robots inflict a strong attack that doubles the normal amount of damage.
			damage*=2;
	}
	
	cout << getType() << " attacks for " << damage << " points!" << endl;

	return damage;
}

string Optimusprime::getType()
{
	return "optimusprime";
}
