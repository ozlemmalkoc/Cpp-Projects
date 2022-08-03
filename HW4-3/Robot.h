#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>

using namespace std;

class Robot
{
	private:

		//int type;
		int strength;	//a member data which stores the strength
		int hitpoints;	//a member data which stores the hitpoints
		virtual string getType();	//a helper function which returns the robot type

	public:
		
		Robot();	// Initializes with  10 strength, 10 hit points
		Robot(int newStrength, int newHit);	// Initializes with strength and hit points
		virtual int getDamage()=0;	// Abstract class on the amount of damage this robot deals in one round
		
		//int getterType();
		int getterStrength();
		int getterHitpoints();
		
		//void setterType(int newType);
		void setterStrength(int newStrength);
		void setterHitpoints(int newHit);
		
		friend void match(Robot& obj1,Robot& obj2);	// Makes two robots fight. It suppresses hitpoints and attack values, battle result and totaldamage value at each step.
};

#endif