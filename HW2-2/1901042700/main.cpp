#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

enum class state{EMPTY=' ', PEG='P', DOT='.'};
enum direction{LEFT='L', RIGHT='R', UP='U', DOWN='D'};


vector<vector<state>> createFigure(int );	// Takes an integer value and creates the appropriate board
string againString(string ,int);	// Edits the number of rows and columns in the user-entered string for Figure 6
void printFigure(vector<vector<state>> );	// Prints the selected board to the screen 
void printFigureForFigure6(vector<vector<state>> );	// Prints the selected board to the screen for figure 6
string randomStringGenerator(vector<vector<state>> );	// Generates random strings of rows, columns, and directions for the movement of pegs.
int isValidString(vector<vector<state>> ,string );	// Checks if string is valid
int isValidStringForFigure6(vector<vector<state>> ,string );	// Checks if string is valid for figure 6
int isValidMove(vector<vector<state>> ,string );	// Controls whether the move is can made or not.
int	isValidMoveForFigure6(vector<vector<state>> ,string );	// Controls whether the move is can made or not for figure 6.
void moveFunction(vector<vector<state>> & ,string );	// Moves the peg in accordance with the data in the string 
void moveFunctionForFigure6(vector<vector<state>> & ,string );	// Moves the peg in accordance with the data in the string for figure 6
int isThereAnyValidMove(vector<vector<state>> );	// Checks if there are moves that can be made
int isThereAnyValidMoveForFigure6(vector<vector<state>> );	// Checks if there are moves that can be made
int remainderPegNumber(vector<vector<state>> );	// Returns the number of pegs left on the board when there are no moves left
int isFigureTriangle(string,vector<vector<state>>,vector<int>,string);	// Returns the value of whether the shape is triangular or not.
void printFigureToFile(ofstream&,vector<vector<state>> ,string );	// If the user wants to save the file, she enters the file name and thanks to this function, it saves the current state of the board to the target file.
void printFigureForFigure6ToFile(vector<vector<state>> ,string );	//If the user wants to save the file, she enters the file name and thanks to this function, it saves the current state of the board to the target file.For triangle figures.
void functionForHumanGamer(vector<vector<state>> ,int ,int ,int isFigureTriangle=0);	// If a human is selected as a player, it allows the human to continue the game and the game progresses.
void functionForComputerGamer(vector<vector<state>> ,int ,int flag,int isFigureTriangle=0);	//If a computer selected as a player, it allows the computer to continue the game and the game progresses.
vector<string> split(const string &x, char );	// Separates words in a read string.
vector<int> findColumnAndRowSize(string ,vector<int> &vec,string );	// Calculates the number of columns and rows of the game on the board.
void loadFunction(const string& ,vector<vector<state>> &,vector<int> ,string ,vector<int> & );	// If the user wants to continue playing a previously played and saved game, it reads the data in the desired file from the file and loads it into the necessary vectors.


int main()
{
	int figurechoice=0,flag=1,flag2=1,firstchoice=0,numoffigure=0;
	string movename,computerstring,stry,gamefilename,strload,input;
	char choice=0,choice2;
	vector<int> vec(2),vecExtraKnowledge(2);
	vector<vector<state>> figure;
	vector<string> v(2);
	
	srand (time(NULL));
	while(flag)
	{	
		cout<<"Welcome . Do you want to start a new game or continue where you left off ? "<<endl;
		cout<<"Press 1 if you want to start a new game. Press 2 if you want to continue."<<endl;
		cin>>firstchoice;

		if(firstchoice==1)
		{	while(flag2)
			{
				cout<<"Please choose a figure between 1-6"<<endl;;
				cin>>figurechoice;

				if(figurechoice<=6)
				{	while(flag2)
					{
						cout<<"Who will play ? Enter 'h' for human , 'c' for computer . (h - c) "<<endl;
						cin>>choice;

						if(choice == 'h')
						{
							functionForHumanGamer(figure,figurechoice,flag);
							flag2=0;
						}
						
						
						else if(choice =='c')
						{
							functionForComputerGamer(figure,figurechoice,flag);
							flag2=0;
						}
						else
							cerr<<"Invalid value . Again enter a new value."<<endl<<endl;
					}
				}
				else
					cerr<<"Invalid value . Again enter a new value."<<endl<<endl;
			}	

		}

		else if(firstchoice==2)
		{
			cout<<"For the game you want to continue , enter the name of the game you want to continue as ( LOAD FILENAME.TXT )"<<endl;
			cin.ignore();
			getline(cin,input);

			v = split(input,' ');
			gamefilename=v[1];
			
	   		findColumnAndRowSize(gamefilename,vec,strload);
			
			vector<vector<state>> vecLoad( (vec[0]-2), vector<state> (vec[1]));
			
			loadFunction(gamefilename,vecLoad,vec,strload,vecExtraKnowledge);
			numoffigure=(vecExtraKnowledge[0]);
			
			if(numoffigure>6)
			{
				figurechoice=rand()%3+6;
			}
			
			
			if(isFigureTriangle(gamefilename,vecLoad,vec,strload)==0  )
				printFigure(vecLoad);
			else if(isFigureTriangle(gamefilename,vecLoad,vec,strload)==1)
				printFigureForFigure6(vecLoad);

			cout<<endl;
			cout<<(vecExtraKnowledge[0]-48)<<" -> number of moves made before."<<endl;
			cout<<(vecExtraKnowledge[1]-48)<<" -> type of board played."<<endl;
		
			while(flag2)
			{
				cout<<"Who will continue to game ( h - c ) ?"<<endl;
				cin>>choice2;
				
				if(choice2=='h')
				{
					functionForHumanGamer(vecLoad,vecExtraKnowledge[0],flag,isFigureTriangle(gamefilename,vecLoad,vec,strload));
					flag2=0;
				}
				else if(choice2=='c')
				{
					functionForComputerGamer(vecLoad,vecExtraKnowledge[0],flag,isFigureTriangle(gamefilename,vecLoad,vec,strload));
					flag2=0;
				}
				else
					cerr<<"Invalid value . Again enter a new value."<<endl<<endl;

				vecLoad.clear();
				vecExtraKnowledge.clear();
			}	
		}
			
		else
		cerr<<"Invalid value . Again enter a new value."<<endl<<endl;
		
		if(firstchoice == 1 || firstchoice==2)
			flag=0;
		
		firstchoice=0;
	}

return 0;
}

vector<vector<state>> createFigure(int figurechoicex)
{
	if(figurechoicex==1)
	{
		vector <vector <state> > version1
		{
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::EMPTY},
			{state::PEG,state::PEG,state::PEG,state::DOT,state::PEG,state::PEG,state::PEG},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::EMPTY,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY},
			
		};
		return version1;
	}
	
	else if(figurechoicex==2)
	{
		vector <vector <state> > version2
		{
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::DOT,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
		};
		return version2;
	}

	else if(figurechoicex==3)
	{
		vector <vector <state> > version3
		{
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::PEG,state::PEG,state::PEG,state::DOT,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
		};
		return version3;
	}

	else if(figurechoicex==4)
	{
		vector <vector <state> > version4
		{
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::PEG,state::PEG,state::PEG,state::DOT,state::PEG,state::PEG,state::PEG},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY}
		};
		return version4;
	}

	else if(figurechoicex==5)
	{
		vector <vector <state> > version5
		{
			{state::EMPTY,state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::EMPTY},
			{state::PEG,state::PEG,state::PEG,state::PEG,state::DOT,state::PEG,state::PEG,state::PEG,state::PEG},
			{state::EMPTY,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::PEG,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY,state::EMPTY},
		};
		return version5;
	}

	else if(figurechoicex==6)
	{
		vector <vector <state> > version6
		{
			{state::EMPTY,state::EMPTY,state::EMPTY,state::EMPTY,state::DOT,state::EMPTY,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::EMPTY,state::PEG,state::EMPTY,state::PEG,state::EMPTY,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::EMPTY,state::PEG,state::EMPTY,state::PEG,state::EMPTY,state::PEG,state::EMPTY,state::EMPTY},
			{state::EMPTY,state::PEG,state::EMPTY,state::PEG,state::EMPTY,state::PEG,state::EMPTY,state::PEG,state::EMPTY},
			{state::PEG,state::EMPTY,state::PEG,state::EMPTY,state::PEG,state::EMPTY,state::PEG,state::EMPTY,state::PEG}


		};
		return version6;
	}
	return vector<vector<state>>();
}

string againString(string str,int rownumoffigure)
{
	int firstnum=0,secondnum=0;
	string strx;
	
	firstnum=(int)str[1]-49;
	
	if(str[0]=='A')
		secondnum=rownumoffigure-1-firstnum;
	else if(str[0]=='B')
		secondnum=rownumoffigure+1-firstnum;
	else if(str[0]=='C')
		secondnum=rownumoffigure+3-firstnum;
	else if(str[0]=='D')
		secondnum=rownumoffigure+5-firstnum;
	else if(str[0]=='E')
		secondnum=rownumoffigure+7-firstnum;
	else if(str[0]=='F')
		secondnum=rownumoffigure+9-firstnum;
	else if(str[0]=='G')
		secondnum=rownumoffigure+11-firstnum;
	else if(str[0]=='H')
		secondnum=rownumoffigure+13-firstnum;
	
	strx += (char)secondnum;
	strx +=(char)firstnum;
	strx+="-";
	strx+=str[3];
	
	return strx;
}

void printFigure(vector<vector<state>> figurey)
{	
	int csize = figurey[0].size();
	int rsize = figurey.size();
	  
	   cout<<"";
	   cout<<endl;
	   cout<<"  ";
	    
	    for(int k=65;k<65+csize;k++)
	    {	
	    	cout<<(char)k;
	    }
	    	
	    	cout<<endl;
	   		
		for(int i=0;i<rsize;i++)
		{	
			cout<<i+1<<" ";
			
			for(int j=0;j<csize;j++)
			{	
				cout<<static_cast<char>(figurey[i][j]);
			}
				cout<<endl;
		}

}

void printFigureForFigure6(vector<vector<state>> figurey)
{	
	   int csize = figurey[0].size();
	   int rsize = figurey.size();
	
	    cout<<endl;
	  
		for(int i=0;i<rsize;i++)
		{	
			cout<<i+1<<" ";
			
			for(int j=0;j<csize;j++)
			{	
				cout<<static_cast<char>(figurey[i][j]);

			}
				cout<<endl;
		}

}

string randomStringGenerator(vector<vector<state>> va)
{
	direction dirs[] = {LEFT, RIGHT, UP, DOWN};
	string str;
	int csize=va[0].size();
	int rsize=va.size() ;

	str += rand() % csize + 'A';
	str += rand() % rsize+ '1';
	str += '-';
	str += dirs[rand() % 4];

	return str;
}

int isValidString(vector<vector<state>> v0,string stringx)
{	
	int columnnum=0,rownum=0;

	columnnum=v0[0].size();
	rownum=v0.size();

	if((((int)stringx[0])-65)<columnnum && (((int)stringx[1])-48-1)<rownum && (stringx[3]==LEFT || stringx[3]==RIGHT || stringx[3]==UP ||stringx[3]==DOWN ))
		return 1;
	else 
		return 0 ;
}

int isValidStringForFigure6(vector<vector<state>> v0,string stringx)
{	
	int columnnum=v0[0].size(),rownum=v0.size();

	if((((int)stringx[0])-65)<columnnum && (((int)stringx[1])-48-1)<rownum && (stringx[3]==LEFT || stringx[3]==RIGHT || stringx[3]==UP ||stringx[3]==DOWN ))
		return 1;
	else
		return 0 ;
}

int isValidMove(vector<vector<state>> v2,string movenamex)
{	
	int firstnum=0,secondnum=0;
	
	firstnum=(int)movenamex[1]-48-1;
	secondnum=((int)movenamex[0])-65;

	switch(movenamex[3])
	{	
		case 'L':	if(secondnum>1 && v2[firstnum][secondnum-2]==state::DOT && v2[firstnum][secondnum-1]==state::PEG &&v2[firstnum][secondnum]==state::PEG  )
						return 1;
					
					else
						return 0;
					
		case'R':	if(secondnum<static_cast<int>(v2[0].size()-2) && v2[firstnum][secondnum+2]==state::DOT && v2[firstnum][secondnum+1]==state::PEG &&v2[firstnum][secondnum]==state::PEG)
						return 1;
					
					else
						return 0;

		case 'U':	if(firstnum>1 && v2[firstnum-2][secondnum]==state::DOT && v2[firstnum-1][secondnum]==state::PEG &&v2[firstnum][secondnum]==state::PEG)
						return 1;
					else
						return 0;

		case 'D':	if(firstnum<static_cast<int>(v2.size()-2) && v2[firstnum+2][secondnum]==state::DOT &&v2[firstnum+1][secondnum]==state::PEG &&v2[firstnum][secondnum]==state::PEG)
						return 1;
					else
						return 0;
					}
	return 0;
	}

int	isValidMoveForFigure6(vector<vector<state>> v2,string movenamex)
{	
	int firstnum=0,secondnum=0;
	secondnum=movenamex[0];
	firstnum=movenamex[1];
	
	switch(movenamex[3])
	{	
		case 'L':	if(secondnum>2 && v2[firstnum][secondnum-4]==state::DOT && v2[firstnum][secondnum-2]==state::PEG &&v2[firstnum][secondnum]==state::PEG  )
						return 1;
					else
						return 0;
					
		case'R':	if(secondnum<static_cast<int>(v2[0].size()-2) && v2[firstnum][secondnum+4]==state::DOT && v2[firstnum][secondnum+2]==state::PEG &&v2[firstnum][secondnum]==state::PEG)
						return 1;
					else
						return 0;

		case 'U':	if((firstnum>1 && v2[firstnum-2][secondnum-2]==state::DOT && v2[firstnum-1][secondnum-1]==state::PEG &&v2[firstnum][secondnum]==state::PEG) ||
						(firstnum>1 && v2[firstnum-2][secondnum+2]==state::DOT && v2[firstnum-1][secondnum+1]==state::PEG &&v2[firstnum][secondnum]==state::PEG))
						return 1;
					else
						return 0;
						

		case 'D':	if((firstnum<static_cast<int>(v2.size()-2) && v2[firstnum+2][secondnum-2]==state::DOT &&v2[firstnum+1][secondnum-1]==state::PEG &&v2[firstnum][secondnum]==state::PEG )||
						(firstnum<static_cast<int>(v2.size()-2) && v2[firstnum+2][secondnum+2]==state::DOT &&v2[firstnum+1][secondnum+1]==state::PEG &&v2[firstnum][secondnum]==state::PEG))
						return 1;
					else
						return 0;
		}

return 0;
}

void moveFunction(vector<vector<state>> & figurez,string movenamey)
{
 	int firstnum2=0,secondnum2=0;

 	firstnum2=(int)movenamey[1]-48-1;
	secondnum2=((int)movenamey[0])-65;
	
	switch(movenamey[3])
	{
		case 'L':	figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2][secondnum2-1]=state::DOT;
					figurez[firstnum2][secondnum2-2]=state::PEG;	
					break;
							
		case'R':	figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2][secondnum2+1]=state::DOT;
					figurez[firstnum2][secondnum2+2]=state::PEG;	
					break;

		case 'U':	figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2-1][secondnum2]=state::DOT;
					figurez[firstnum2-2][secondnum2]=state::PEG;	
					break;

		case 'D':	figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2+1][secondnum2]=state::DOT;
					figurez[firstnum2+2][secondnum2]=state::PEG;	
					break;

	}
}

 void moveFunctionForFigure6(vector<vector<state>> & figurez,string movenamey)
 {
 	int firstnum2=0,secondnum2=0;
	
	secondnum2=movenamey[0];
	firstnum2=movenamey[1];
	
	switch(movenamey[3])
	{
		case 'L':	figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2][secondnum2-2]=state::DOT;
					figurez[firstnum2][secondnum2-4]=state::PEG;	
					break;
							

		case'R':	figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2][secondnum2+2]=state::DOT;
					figurez[firstnum2][secondnum2+4]=state::PEG;	
					break;

		case 'U':	if(figurez[firstnum2-2][secondnum2-2]==state::DOT && figurez[firstnum2-1][secondnum2-1]==state::PEG &&figurez[firstnum2][secondnum2]==state::PEG){

					figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2-1][secondnum2-1]=state::DOT;
					figurez[firstnum2-2][secondnum2-2]=state::PEG;
					}
					
					else if(figurez[firstnum2-2][secondnum2+2]==state::DOT && figurez[firstnum2-1][secondnum2+1]==state::PEG &&figurez[firstnum2][secondnum2]==state::PEG){
					
					figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2-1][secondnum2+1]=state::DOT;
					figurez[firstnum2-2][secondnum2+2]=state::PEG;	
					}
					break;

		case 'D':	if(figurez[firstnum2+2][secondnum2-2]==state::DOT && figurez[firstnum2+1][secondnum2-1]==state::PEG &&figurez[firstnum2][secondnum2]==state::PEG){

					figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2+1][secondnum2-1]=state::DOT;
					figurez[firstnum2+2][secondnum2-2]=state::PEG;	
					}
					else if(figurez[firstnum2+2][secondnum2+2]==state::DOT && figurez[firstnum2+1][secondnum2+1]==state::PEG &&figurez[firstnum2][secondnum2]==state::PEG)
						{

					figurez[firstnum2][secondnum2]=state::DOT;
					figurez[firstnum2+1][secondnum2+1]=state::DOT;
					figurez[firstnum2+2][secondnum2+2]=state::PEG;	
					}
					break;

	}
}

int isThereAnyValidMove(vector<vector<state>> figurek)
{
	for(int i=0;i<static_cast<int>(figurek.size());i++)
		{
			for(int j=0;j<static_cast<int>(figurek[0].size());j++)
			{
				if((j<static_cast<int>(figurek[0].size()-2) && figurek[i][j]==state::PEG && figurek[i][j+1]==state::PEG &&  figurek[i][j+2]==state::DOT) || (j>1 && figurek[i][j]==state::PEG && figurek[i][j-1]==state::PEG && figurek[i][j-2]==state::DOT )|| 
					(i<static_cast<int>(figurek.size()-2) && figurek[i][j]==state::PEG && figurek[i+1][j]==state::PEG && figurek[i+2][j]==state::DOT) ||(i>1 && figurek[i][j]==state::PEG && figurek[i-1][j]==state::PEG && figurek[i-2][j]==state::DOT))
					return 1;
			}
				
		}
	return 0;
}

int isThereAnyValidMoveForFigure6(vector<vector<state>> figurek)
{
	for(int i=0;i<static_cast<int>(figurek.size());i++)
		{
			for(int j=0;j<static_cast<int>(figurek[0].size());j++)
			{
				
				if((j<static_cast<int>(figurek[0].size()-2) && figurek[i][j]==state::PEG && figurek[i][j+2]==state::PEG &&  figurek[i][j+4]==state::DOT) || (j>2 && figurek[i][j]==state::PEG && figurek[i][j-2]==state::PEG && figurek[i][j-4]==state::DOT )|| 
					(i<static_cast<int>(figurek.size()-2) && figurek[i][j]==state::PEG && figurek[i+1][j+1]==state::PEG && figurek[i+2][j+2]==state::DOT) || (i<static_cast<int>(figurek.size()-2) && figurek[i][j]==state::PEG && figurek[i+1][j-1]==state::PEG && figurek[i+2][j-2]==state::DOT)
					||(i>1 && figurek[i][j]==state::PEG && figurek[i-1][j-1]==state::PEG && figurek[i-2][j-2]==state::DOT) || (i>1 && figurek[i][j]==state::PEG && figurek[i-1][j+1]==state::PEG && figurek[i-2][j+2]==state::DOT))
					return 1;
			}
				
		}
	return 0;
}

int remainderPegNumber(vector<vector<state>> figurep)
{	
	auto numberpeg=0;
	
	for(int i=0;i<static_cast<int>(figurep.size());i++)
		{
			for(int j=0;j<static_cast<int>(figurep[0].size());j++)
			{
				if(figurep[i][j]==state::PEG)
					numberpeg++;
			}		
		}
	return numberpeg;
}

void printFigureToFile(ofstream& printToFile,vector<vector<state>> figurey,string gamefilename)
{	
	
	int csize = figurey[0].size();
	decltype(csize) rsize = figurey.size();
	 
	for(int i=0;i<rsize;i++)
	{	
		for(int j=0;j<csize;j++)
		{	
			printToFile<<static_cast<char>(figurey[i][j]);
		}
			printToFile<<endl;
	}
}

void printFigureForFigure6ToFile(vector<vector<state>> figurey,string gamefilename)
{	
    int csize = figurey[0].size();
    int rsize = figurey.size();
	
    ofstream printToFile(gamefilename);
	  
	for(int i=0;i<rsize;i++)
	{	
		for(int j=0;j<csize;j++)
		{	
			printToFile<<static_cast<char>(figurey[i][j]);

		}
			printToFile<<endl;
	}
}

vector<string> split(const string &x, char space)
{
    vector<string> vec;
    stringstream ss (x);
    string str;

    while(getline(ss, str, space))
        if(str.size() != 0)
            vec.push_back(str);

    return vec;
}

void functionForHumanGamer(vector<vector<state>> figure,int figurechoice,int flag,int isFigureTriangle)
{	
	int rownumoffigure,movenumber=0;	
	string input,movename,stry;
	vector<string> v(2);
	ofstream printToFile;
	

	if(figurechoice<=6)
	{	
		figure= createFigure(figurechoice);
	}
	
	rownumoffigure=figure.size();

	if(figurechoice!=6 && isFigureTriangle==0)
		printFigure(figure);
	else if(figurechoice==6||isFigureTriangle==1)
		printFigureForFigure6(figure);
		
	if(figurechoice!=6 && isFigureTriangle==0)
	{	
		cin.ignore();

		while(flag)
		{	
			cout<<endl;
			cout<<"Please enter columnrow-direction ( Format -> ( columnnumberrownumber - direction ) -> ( A2-L ) )"<<endl;
			cout<<"If you want to save your current game state , you can save the game with the file name you want by using this command . (SAVE FILENAME.TXT)"<<endl;
			
			getline(cin,movename);
			v = split(movename,' ');
			
			if(v[0]=="SAVE")
			{	
				printToFile.open(v[1]);
				cout<<"The file is being saved..."<<endl;
				
				printFigureToFile(printToFile,figure,v[1]);
				
				printToFile<<movenumber<<endl;
				printToFile<<figurechoice<<endl;
				
				flag=0;
			}
			else
			{	
				if(isValidString(figure,movename)== 1)
				{
					if(isValidMove(figure,movename)==1)
					{	
						movenumber++;
						
						moveFunction(figure,movename);
						printFigure(figure);
						
						if(isThereAnyValidMove(figure)==0)
							flag=0;
					}		
					else
						cerr<<endl<<"Please enter valid move string"<<endl;
				}	
				else
				cerr<<"Please enter valid string"<<endl;
				}
		}

		cout<<"Remaining peg numbers are "<<remainderPegNumber(figure)<<endl;
	}
		
	else if(figurechoice==6||isFigureTriangle==1)
	{	
		cin.ignore();
		
		while(flag)
		{	
			cout<<endl;
			cout<<"Please enter columnrow-direction (Format -> ( columnnumberrownumber - direction ) -> ( A2-L ) )"<<endl;
			cout<<"If you want to save your current game state , you can save the game with the file name you want by using this command . (SAVE FILENAME.TXT)"<<endl;
			
			getline(cin,movename);
			v = split(movename,' ');
			
			if(v[0]=="SAVE")
			{	printToFile.open(v[1]);
				cout<<"The file is being saved..."<<endl;
				printFigureToFile(printToFile,figure,v[1]);
				
				printToFile<<movenumber<<endl;
				printToFile<<figurechoice<<endl;
				
				flag=0;
			}
			else
			{
				stry=againString(movename,rownumoffigure);

				if(isValidStringForFigure6(figure,stry)==1)
				{	
					if(isValidMoveForFigure6(figure,stry)==1)
					{	
						movenumber++;
						
						moveFunctionForFigure6(figure,stry);
						printFigureForFigure6(figure);
						
						if(isThereAnyValidMoveForFigure6(figure)==0)
							flag=0;
					}
					else
					cerr<<endl<<"Please enter valid move string"<<endl;
				}
				else
				cerr<<"Please enter valid string"<<endl;
			}
		}
		
		cout<<"Remaining peg numbers are "<<remainderPegNumber(figure)<<endl;
	}
}

void functionForComputerGamer(vector<vector<state>> figure,int figurechoice,int flag,int isFigureTriangle)
{	
	int rownumoffigure;	
	string movename,stry;

	
	if(figurechoice<=6)
		figure= createFigure(figurechoice);
		
	printFigure(figure);
	
	rownumoffigure=figure.size();

 	
	if(figurechoice!=6 && isFigureTriangle==0)
	{
		while(flag)
		{
			movename = randomStringGenerator(figure);

			if(isValidString(figure,movename)== 1)
			{
				if(isValidMove(figure,movename)==1)
				{	
					cout<<endl<<movename<<endl;
					
					moveFunction(figure,movename);
					printFigure(figure);
					
					if(isThereAnyValidMove(figure)==0)
						flag=0;
				}
			}
		}
		
		cout<<"Remaining peg numbers are "<<remainderPegNumber(figure)<<endl;
	}
	
	else if(figurechoice==6 || isFigureTriangle==1)
	{	
		while(flag)
		{
			movename = randomStringGenerator(figure);
			stry=againString(movename,rownumoffigure);
			cout<<stry[0]<<endl;
			
			if(isValidStringForFigure6(figure,stry)==1)
			{
				if(isValidMoveForFigure6(figure,stry)==1)
				{	
					cout<<endl<<movename<<endl;
					
					moveFunctionForFigure6(figure,stry);
					printFigureForFigure6(figure);
					
					if(isThereAnyValidMoveForFigure6(figure)==0)
						flag=0;
				}
			}
		}
		
		cout<<"Remaining peg numbers are "<<remainderPegNumber(figure)<<endl;
	}
}

vector<int> findColumnAndRowSize(string gamefilename,vector<int> &vec,string strload)
{	
	ifstream loadfile(gamefilename);
	int j=0,csizeofstrload=0;

	if(loadfile.is_open())
	{
		while (getline(loadfile, strload))
		{		
		 	if(static_cast<int>(strload.size())>csizeofstrload)
		 	{	
		 		csizeofstrload=strload.size();
		 	}
		 	
		 	j++;
		}
	}
			 	
	loadfile.close();

    vec[0]=j;
    vec[1]=csizeofstrload;

    return vec;
}

void loadFunction(const string &gamefilename,vector<vector<state>> &vecLoad,vector<int> vec,string strload,vector<int> & vecExtraKnowledge)
{
	ifstream loadfile(gamefilename);
	int j=0;
	
	vec=findColumnAndRowSize(gamefilename,vec,strload);
	
	
	if(loadfile.is_open())
	{	
		while (getline(loadfile, strload))
		{	
		 	if(j<((vec[0]-2)))
		 	{	
		 		for(int i=0;i<(vec[1]);i++)
				{
		 			state s = static_cast<state> (strload[i]);
		 			
		 			if(i<static_cast<int>(strload.size()))
		 				vecLoad[j][i] = s;

					else
		 				vecLoad[j][i]=state::EMPTY;

		 		}
		 		j++;
		 	}

			else if(j==static_cast<int>(vec[0]-2))
			{	
				vecExtraKnowledge[0]=static_cast<int>(strload[0]);
			 	j++;
			}

		 	else if(j==static_cast<int>(vec[0]-1))
			{	
		 		vecExtraKnowledge[1]=static_cast<int>(strload[0]);
				j++;
		 	}
		}
	}

loadfile.close();
}

int isFigureTriangle(string gamefilename,vector<vector<state>> vecLoad,vector<int> vec,string strload)
{	
	ifstream loadfile(gamefilename);
	
	vec=findColumnAndRowSize(gamefilename,vec,strload);

	for(int i=0;i<static_cast<int>(vec[0]-2);i++)
	{	
		for(int j=0;j<vec[1];j++)
		{
			if(vecLoad[i][j]==state::PEG && vecLoad[i][j+1]==state::EMPTY &&vecLoad[i][j+2]==state::PEG)
				return 1;
		}
	}
			 
loadfile.close();	

return 0;
}
