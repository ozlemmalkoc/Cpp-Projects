#include "Robot.h"
#include "Bulldozer.h"

Bulldozer::Bulldozer():Robot(){} 
Bulldozer::Bulldozer(int newStrength, int newHit):Robot(newStrength,newHit){}

int Bulldozer::getDamage()	//This function outputs and returns the damage this robot can inflict in one round of combat.
{
	int damage;

	damage = (rand() % Robot::getterStrength()) + 1;	// Bulldozer robot inflicts damage that is a random number r, where 0 < r <= strength
	
	cout << getType() << " attacks for " << damage << " points!" << endl;

	return damage;
}

string Bulldozer::getType()
{
	return "bulldozer";
}

