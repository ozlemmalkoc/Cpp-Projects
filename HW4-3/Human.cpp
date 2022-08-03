#include "Robot.h"
#include "Human.h"


Human::Human():Robot(){}
Human::Human(int newStrength, int newHit):Robot(newStrength,newHit){}

string Human::getType()
{
	return "human";
}
