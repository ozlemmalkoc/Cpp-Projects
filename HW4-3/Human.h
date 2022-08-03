#ifndef HUMAN_H
#define HUMAN_H

#include "Robot.h"

class Human: public Robot
{	
	public:
		
		Human();	// Initializes with  10 strength, 10 hit points
		Human(int newStrength, int newHit);	// Initializes with strength and hit points

		virtual int getDamage()=0;	// Abstract class on the amount of damage this robot deals in one round
     
  	private:
		
		virtual string getType();	//a helper function which returns the robot type
};

#endif