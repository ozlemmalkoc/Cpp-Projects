#include "Robot.h"

Robot::Robot()
{
	strength=10;
	hitpoints=10;
}

Robot::Robot(int newStrength, int newHit)
{
	strength=newStrength;
	hitpoints=newHit;
}

string Robot::getType()
{
	return "unknown";
}

//int Robot::getterType(){ return type; }
int Robot::getterStrength(){ return strength; }
int Robot::getterHitpoints(){ return hitpoints; }

//void Robot::setterType(int newType){ type=newType; }
void Robot::setterStrength(int newStrength){ strength=newStrength; }
void Robot::setterHitpoints(int newHit){ hitpoints=newHit; }

void match(Robot& obj1,Robot & obj2)	// Makes two robots fight. It suppresses hitpoints and attack values, battle result and totaldamage value at each step.
{	
	bool isFirstStage=true;
	int obj1Damage,obj2Damage;
	int hitPoints1= obj1.getterHitpoints();
	int hitPoints2= obj2.getterHitpoints();

	
	if(hitPoints1<=0 && hitPoints2<=0)	// if one or two of the objects have hitpoints of 0 or minus then there is no match.
		cout<<endl<<obj1.getType()<<" and "<<obj2.getType()<<" objects with minus or 0  hitpoints value cannot match!"<<endl;
	else if(hitPoints1<=0)
		cout<<endl<<obj1.getType()<<" object with minus or 0  hitpoints value cannot match!"<<endl;
	else if(hitPoints2<=0)
		cout<<endl<<obj2.getType()<<" object with minus or 0  hitpoints value cannot match!"<<endl;

	while(hitPoints1>0 && hitPoints2>0)	// Hitpoints values must be greater than 0 for the match to take place
	{	
		if(isFirstStage==true)	// if it is the first stage of the match
		{
			cout<<obj1.getType()<<" hitpoints is "<<obj1.getterHitpoints()<<endl;
			cout<<obj2.getType()<<" hitpoints is "<<obj2.getterHitpoints()<<endl<<endl;
			cout<<obj1.getType()<<" will do the first attack"<<endl<<endl;
			isFirstStage=false;
		}
		
		obj1Damage=obj1.getDamage();
		hitPoints2-=obj1Damage;	// Obj2's hitpoints are reduced due to object1's attack
		
		obj2.setterHitpoints(hitPoints2);

		
		cout<<endl;
		cout<<obj2.getType()<<" hitpoints is "<<obj2.getterHitpoints()<<endl;
		cout<<obj1.getType()<<" hitpoints is "<<obj1.getterHitpoints()<<endl<<endl;
		
		if(hitPoints2<=0 )	// If obj2 hitpoints value is minus or zero ,obj1 will win
		{
			cout<<"Winner of the match "<<obj1.getType()<<endl<<endl;
				break;
		}
		
		obj2Damage=obj2.getDamage();
		hitPoints1-=obj2Damage;	// Obj1's hitpoints are reduced due to object2's attack
		
	 	obj1.setterHitpoints(hitPoints1);
		
		cout<<endl<<obj1.getType()<<" hitpoints is "<<obj1.getterHitpoints()<<endl;
		cout<<obj2.getType()<<" hitpoints is "<<obj2.getterHitpoints()<<endl<<endl;
		
		if(hitPoints1<=0)	// If obj1 hitpoints value is minus or zero ,obj2 will win
		{
			cout<<"Winner of the match "<<obj2.getType()<<endl<<endl;
				break;
		}
	}
}
