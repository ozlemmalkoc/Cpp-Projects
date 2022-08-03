#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int generateRandomNumber(int base)	//Generates a random number in the desired digit.
{
	srand(time(NULL));

	return (rand() % ((int)(pow(10,base-1)*9)) + (int)pow(10,base-1)); 
}

int controlRepeatRandomNumber(int number)	//Checks for a large number of duplicate digits.
{	int i,j,temp,num;	
	
	while(number>0){
		temp = number;
		num = temp%10;
		temp = temp/10;
		while(temp>0){
			if(num == temp%10){
				return 0;		//Returns 0 if there are duplicate digit.
			}
			temp = temp/10;
		}
		number= number/10;
	}
	return 1;	//Returns 1 if no duplicate digit.
}

int controlSize(string p,int sizen)		//Checks whether a number has been entered in the desired digit.
{	int len=0,i=0;
	len=p.size();	//len=Carries the size information of the string.

	if(sizen!=len)		//If a number with a length different from the number of digits entered in the command line is entered, an error code E1 is given and the program is terminated.
	{	cout<<"E1"<<endl;
		exit(1);
	}
return 0;	//Returns 0 if a number with the same length as the number of digits entered on the command line is entered.
}

int controlLetter(string p)		//Checks if it contains characters other than digits.
{	int len=0,i=0;
	len=p.size();	//len=Carries the size information of the string.
	for(i=0;i<len;i++)
	{	if(p[i]>57 || p[i] <48 )		//If it contains characters other than digits, it prints the E2 error code and terminates the program.
		{	cout<<"E2"<<endl;
			exit(1);
		}
	}
	return 0;		//Returns 0 if contains only numbers.
}

void firstNumIsZeroForsecondUserEnter(string p)		//Checks if the number entered by the user starts with zero.
{	if(p[0]=='0')
	{	cout<<"E1"<<endl;	//If the number starts with 0, the E1 error code is printed and the program exits.
		exit(1);
	}
}

void firstNumIsZeroForFirstUserEnter(string p)	//Checks whether the number entered in the command line begins with 0.
{	if(p[0]=='0')
	{	cout<<"E0"<<endl;	//If the number starts with 0, the E0 error code is printed and the program exits.
		exit(1);
	}
}

int takeNumberFromUser(int size)	//Takes a number from the user and checks if the number is valid.
{	string number;	//The variable where the number requested by the user is stored.
	cin>>number;
	firstNumIsZeroForsecondUserEnter(number);	//Checks if the number entered by the user starts with zero.If the number starts with 0, the E0 error code is printed and the program exits.
	controlLetter(number);	//Checks if it contains characters other than digits.If it contains characters other than digits, it prints the E2 error code and terminates the program.
	controlSize(number,size);	//Checks whether a number has been entered in the desired digit.If a number with a length different from the number of digits entered in the command line is entered, an error code E1 is given and the program is terminated.Returns 0 if a number with the same length as the number of digits entered on the command line is entered.
	
	if(controlRepeatRandomNumber(stoi(number))==0)	//Checks for a large number of duplicate digits.
	{	cout<<"E1"<<endl;	//Prints E1 error code if there is a duplicate digit and terminates the program.
		exit(1);
	}

return stoi(number);	//If the number is valid, the string number is converted to an integer and this number value is returned.
}

int functionHint(int firstnum,int usernum,int size)	//Prints two hint numbers for the value the user should guess.
{	int db=0,dn=0,tempUser,tempRandom,tempR2;
	
	tempUser = usernum;
	tempRandom = firstnum;
	
	while(tempUser>0)
	{	tempR2 = firstnum;
		if(tempUser%10 == tempRandom%10)	

			db++;				//db=The count of digits of the proposed number that match in place of the secret number.
		else
		{	while(tempR2 > 0)
			{	if(tempR2%10 == tempUser%10)
				{	dn++;		//The count of digits of the proposed number which do exist in the secret number but are not in place.

					break;
				}
				tempR2 = tempR2/10;
			}
		}
		tempUser = tempUser/10;
		tempRandom = tempRandom/10;	
	}
	if(db==size)	//When it is equal to you with db, it means the user has guessed the number correctly.
		return 1;
	else
	cout<<db<<" "<<dn<<endl;

return 0;
}

void maxCounterValue(int size)	//Checks if the user can find it in 100 iterations.
{	if(size>100)
	{	cout<<"FAILED"<<endl;	//If the forecast exceeds 100 iterations, FAILED will be printed and the program will be terminated.
		exit(1);
	}
}

void controlLen(int size)	//Checks whether the number  entered from the command line is more than 9 number of digits.
{	if(size>9)
	{	cout<<"E0"<<endl;	//If the number of digits is more than 9, an E0 error message is written and the program is terminated.
		exit(1);
	}
}

int controlParameter(int size)	//Checks the number of parameters entered on the command line.
{	if(size!=3)
	{	cout<<"E0"<<endl;	//If the number of parameters is different from 3, an E0 error message is written and the program is terminated.
		exit(1);
	}
	return 1;
}

int main(int argc, char *argv[])
{	string ramdom ="-r",user="-u";
	int counter=0,randomnumber=0,result=0,len=0; //counter=The variable that holds the number of iterations.

	if(ramdom.compare(argv[1]) == 0 || user.compare(argv[1]) == 0 && controlParameter(argc))	//The number of parameters entered on the command line is checked whether the parameters are -r or -u.
	{	
		if(ramdom.compare(argv[1]) == 0)	//if the parameter is -r
		{	while(1)
			{	randomnumber=generateRandomNumber(stoi(argv[2]));	//Generates a random number in the desired digit.
				result=controlRepeatRandomNumber(randomnumber);	////Checks for a large number of duplicate digits.
				
					if(result==1)	//If a valid random number is generated the loop terminates.
						break;
				else
				{	randomnumber=0;	//The loop continues as no valid random number can be generated.
					result=0;	//The variable values of result and randomnumber are set to 0 for the loop to be smooth.
				}
			}
			len=stoi(argv[2]);	//The value of string type is converted to integer type.
			controlLen(len);	//Checks whether the number  entered from the command line is more than 9 number of digits.
		
			while(1)	//Allows the game to continue until the correct number is found or the game conditions are not met.
			{	counter++;	//The variable that holds the number of iterations.
				maxCounterValue(counter);	//Checks if the user can find it in 100 iterations.
				if(functionHint(randomnumber,takeNumberFromUser(len),len)==1)	//If the correct number is found, FOUND and how many times it is found is written and the program is terminated.
				{	cout<<"FOUND "<<counter<<endl;
					exit(1);
				}
			}
		}
		
		else if(user.compare(argv[1]) == 0)	//if the parameter is -u
		{	len=strlen(argv[2]);	//Finds the length of the number the user enters on the command line.
			controlLen(len);	//Checks whether the number  entered from the command line is more than 9 number of digits.
			firstNumIsZeroForFirstUserEnter(argv[2]);	//Checks whether the number entered in the command line begins with 0.
			controlLetter(argv[2]);	//Checks if it contains characters other than digits.
			controlRepeatRandomNumber(stoi(argv[2]));	//Checks for a large number of duplicate digits.
			
			while(1)	//Allows the game to continue until the correct number is found or the game conditions are not met.
			{	counter++;	//The variable that holds the number of iterations.
				maxCounterValue(counter);	//Checks if the user can find it in 100 iterations.
				if(functionHint(stoi(argv[2]),takeNumberFromUser(len),len)==1)
				{	cout<<"FOUND "<<counter<<endl;	//If the correct number is found, FOUND and how many times it is found is written and the program is terminated.
					exit(1);
				}
			}
		}
	}
	else	//If there are errors in the parameters in the command line, the E0 error code is printed and the program is exited.
	{	cout<<"E0"<<endl;	
		exit(1);
	}
	return 0;
}