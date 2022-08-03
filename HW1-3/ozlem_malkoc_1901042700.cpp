#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int stringLength(string);	// Returns lenght of string.
int compareString(string,string);	// Returns 0, if both the strings are the same.Otherwise returns 1.
int controlNumberOfCommandlineArguments(int );	// Controls the number of arguments entered from the command line. If number is different from 3,prints "E0" and returns 0.Otherwise returns 1.
int controlFirstArgument(char **);	// It checks the 1st element in the command line. Returns 0 if different from -r or -u.Otherwise returns 1.
int controlSecondArgument(char** );	// Checks the second element entered from the command line.Returns 1 if the value is valid, 0 otherwise.
int controlCommandLineArguments(int,char **);	// Returns 1 if the command line is valid, 0 otherwise.
int generateRandomNumber(int );	// Generates a random number in the desired number of digits.
int controlLength(int );	// Checks if the number of digits is valid.Returns 0 if the number of digits is invalid.
int controlFirstDigitIsZero(string );	// Checks if the first digit of the number is zero.Returns 0 if the first digit value is 0.
int takeNumberFromUser(int );	// Asks the user for a number. Returns the value of the number if the number is valid.
int functionHint(int ,int ,int ); //Prints two hint numbers for the value the user should guess.
int controlRepeatNumber(int );	//Checks for a large number of duplicate digits.
void maxCounterValue(int );	//Checks if the user can find it in 100 iterations.
int power(int , int ) ;

int main(int argc, char *argv[])
{
	string random_str = "-r", user_str = "-u";
	int counter = 0, string_length = 0, random_number = 0;	// Counter value  is number of our guesses.string_length is the number of digits of the value we entered in the command number.random_number the number we randomly generated

	if (controlCommandLineArguments(argc, argv) == 1)		//The number of parameters entered on the command line is checked whether the parameters are -r or -u.
	{
		if (compareString(argv[1], random_str) == 0)		//if the parameter is -r
		{
			random_number = generateRandomNumber(stoi(argv[2]));	//Generates a random number in the desired digit.
			string_length = stoi(argv[2]);

			while (1)	//Allows the game to continue until the correct number is found or the game conditions are not met.
			{
				counter++;
				maxCounterValue(counter);		//Checks if the user can find it in 100 iterations.
				if (functionHint(random_number, takeNumberFromUser(string_length), string_length) == 1)		//If the correct number is found, FOUND and how many times it is found is written and the program is terminated.
				{
					cout << "FOUND " << counter << endl;
					exit(1);
				}
			}
		}
		else
		{
			string_length = stringLength(argv[2]);

			while (1)
			{
				counter++;
				maxCounterValue(counter);
				
				if (functionHint(stoi(argv[2]), takeNumberFromUser(string_length), string_length) == 1)
				{
					cout << "FOUND " << counter << endl;
					exit(1);
				}
			}
		}
	}
	else
		exit(1);

	return 0;
}

int stringLength(string str)	// Returns lenght of string.
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return i;

}

int compareString(string str1, string str2)	// Returns 0, if both the strings are the same.Otherwise returns 1.
{
	int i = 0, j = 0;

	i = stringLength(str1);
	j = stringLength(str2);

	if (i != j)
		return 1;

	for (int k = 0; k < i; k++)
	{
		if (str1[k] != str2[k])
			return 1;
	}

	return 0;

}

int controlFirstDigitIsZero(string str)	// Checks if the first digit of the number is zero.Returns 0 if the first digit value is 0.
{
	if (str[0] == '0')
	{
		return 0;
	}
	else return 1;
}

int controlNumberOfCommandlineArguments(int numberOfArguments)	// Controls the number of arguments entered from the command line. If number is different from 3,prints "E0" and returns 0.Otherwise returns 1.
{
	if (numberOfArguments != 3)
	{
		cout << "E0";
		return 0;
	}
	else
		return 1;

}

int controlFirstArgument(char **str)	// It checks the 1st element in the command line. Returns 0 if different from -r or -u.Otherwise returns 1.
{
	string random_str = "-r", user_str = "-u";

	if (!(compareString(str[1], random_str) == 0 || compareString(str[1], user_str) == 0))	// If random_str is different from -r or -u
	{
		cout << "E0";
		return 0;
	}
	else
		return 1;
}

int controlContainLetter(string str)		//Checks if it contains characters other than digits.
{
	int len = 0, i = 0;

	len = stringLength(str);		//len=Stores the length information of the string.

	for (i = 0; i < len; i++)
	{
		if (str[i] > 57 || str[i] < 48)
		{
			return 1;
		}
	}

	return 0;
}

int controlRepeatNumber(int number)	//Checks for a large number of duplicate digits.
{
	int i = 0, j = 0, temp = 0, num = 0;

	while (number > 0)
	{
		temp = number;
		num = temp % 10;
		temp = temp / 10;

		while (temp > 0)
		{
			if (num == temp % 10)
				return 1;		//Returns 1 if there are duplicate digit.

			temp = temp / 10;
		}

		number = number / 10;
	}

	return 0;	//Returns 0 if no duplicate digit.
}

int controlLength(int length)	// Checks if the number of digits is valid.Returns 0 if the number of digits is invalid.
{
	if (length < 1 || length > 9)
		return 0;
	else
		return 1;

}

int controlSecondArgument(char **str)		// Checks the second element entered from the command line.Returns 1 if the value is valid, 0 otherwise.
{
	string random_str = "-r", user_str = "-u";

	if (compareString(str[1], random_str) == 0 && (controlLength(stoi(str[2])) == 0))	// If str is -r and str[2] value is valid
	{	
		cout << "EO";
		return 0;
	}
	else if (compareString(str[1], user_str) == 0)	// If str is -u
	{
		if ((stringLength(str[2]) > 9 || stringLength(str[2]) < 1) || controlFirstDigitIsZero(str[2]) == 0 || controlContainLetter(str[2]) == 1 || controlRepeatNumber(stoi(str[2])) == 1)
		{	
			cout << "EO";
			return 0;
		}

		return 1;
	}
	else
		return 1;

}

int controlCommandLineArguments(int numberOfArguments, char **str)	// Returns 1 if the command line is valid, 0 otherwise.
{
	if (controlNumberOfCommandlineArguments(numberOfArguments) == 1 && controlFirstArgument(str) == 1 && controlSecondArgument(str) == 1)
		return 1;
	else
		return 0;

}

int generateRandomNumber(int base)		//Generates a random number in the desired digit.
{
	int random_number = 0;
	srand(time(NULL));

	do {
		random_number = (rand() % ((int)(power(10, base - 1) *9)) + (int) power(10, base - 1));

		if (controlRepeatNumber(random_number) == 0 && controlLength(base) == 1)
			break;
		else
			random_number = 0;

	} while (1);

	return random_number;
}

int takeNumberFromUser(int length)	//Takes a number from the user and checks if the number is valid.
{
	string number;		//The variable where the number requested by the user is stored.
	cin >> number;

	if (controlFirstDigitIsZero(number) == 0 || controlLength(stringLength(number) == 0) || stringLength(number) != length || controlRepeatNumber(stoi(number)) == 1)
	{
		cout << "E1";
		exit(1);
	}
	else if (controlContainLetter(number) == 1)
	{
		cout << "E2";
		exit(1);

	}

	return stoi(number);
}

int functionHint(int firstnum, int usernum, int size)	//Prints two hint numbers for the value the user should guess.
{
	int db = 0, dn = 0, tempUser = 0, tempRandom = 0, tempR2 = 0;

	tempUser = usernum;
	tempRandom = firstnum;

	while (tempUser > 0)
	{
		tempR2 = firstnum;

		if (tempUser % 10 == tempRandom % 10)
			db++;		//db=The count of digits of the proposed number that match in place of the secret number.
		else
		{
			while (tempR2 > 0)
			{
				if (tempR2 % 10 == tempUser % 10)
				{
					dn++;	//The count of digits of the proposed number which do exist in the secret number but are not in place.
					break;
				}

				tempR2 = tempR2 / 10;
			}
		}

		tempUser = tempUser / 10;
		tempRandom = tempRandom / 10;
	}

	if (db == size)	//When it is equal to you with db, it means the user has guessed the number correctly.
		return 1;
	else
		cout << db << " " << dn << endl;

	return 0;
}
void maxCounterValue(int size)	//Checks if the user can find it in 100 iterations.
{	
	if(size>100)
	{	
		cout<<"FAILED"<<endl;	//If the forecast exceeds 100 iterations, FAILED will be printed and the program will be terminated.
		exit(1);
	}
}

int power(int value, int power) {
	int result = 1;

	for (int i = 0; i < power; ++i) {
		result *= value;
	}

	return (result);
}
