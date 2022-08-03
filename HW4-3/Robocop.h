#include "Human.h"

class Robocop:public Human
{
	public:
		
		Robocop();	// Initializes with  10 strength, 10 hit points
		Robocop(int newStrength, int newHit);	// Initializes with strength and hit points

		virtual int getDamage();	// Returns amount of damage this robot inflicts in one round of combat
     
    private:
		
		virtual string getType();	//a helper function which returns the robot type
};
