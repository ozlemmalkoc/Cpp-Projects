#include "Robot.h"

class Bulldozer: public Robot
{	
	public:
		
		Bulldozer();	// Initializes with  10 strength, 10 hit points
		Bulldozer(int newStrength, int newHit);	// Initializes with strength and hit points

		virtual int getDamage();	// Returns amount of damage this robot inflicts in one round of combat
     
    private:
		
		virtual string getType(); //a helper function which returns the robot type
};