#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 

using namespace std;

enum class state{EMPTY=' ', PEG='P', DOT='.'};
enum direction{LEFT='L', RIGHT='R', UP='U', DOWN='D'};


vector<vector<state>> createFigure(int );	// Takes an integer value and creates the appropriate board
string againString(string );	// Edits the number of rows and columns in the user-entered string for Figure 6
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


int main()
{
	int figurechoice=0,flag=1;
	string movename,computerstring,stry;
	char choice=0;

	srand (time(NULL));

	cout<<"Please choose a figure between 1-6"<<endl;;
	cin>>figurechoice;
	
	cout<<"Who will play ? Enter h for human,c for computer. "<<endl;
	cin>>choice;

	if(choice == 'h')
	{
		vector<vector<state>> figure= createFigure(figurechoice);
		
		if(figurechoice<6)
			printFigure(figure);
		else if(figurechoice==6)
			printFigureForFigure6(figure);
		
		if(figurechoice<6)
		{
			while(flag)
			{
				cout<<endl<<"Please enter columnrow-direction (Format-> ( columnnumberrownumber-direction )-> (A2-L))"<<endl;
				cin>>movename;
				
				if(isValidString(figure,movename)== 1)
				{
					if(isValidMove(figure,movename)==1)
					{	
						moveFunction(figure,movename);
						printFigure(figure);
						
						if(isThereAnyValidMove(figure)==0)

						flag=0;
					}	
					else
						cout<<endl<<"Please enter valid move string"<<endl;
				}
				else
				cout<<"Please enter valid string"<<endl;
			}

			cout<<"Remaining peg numbers are "<<remainderPegNumber(figure)<<endl;
		}
		
		else if(figurechoice==6)
		{
			
			while(flag)
			{
				cout<<endl<<"Please enter columnrow-direction (Format-> ( columnnumberrownumber-direction )-> (A2-L))"<<endl;
				cin>>movename;
				
				stry=againString(movename);

				if(isValidStringForFigure6(figure,movename)==1)
				{	
					stry=againString(movename);
					
					if(isValidMoveForFigure6(figure,stry)==1)
					{	
						moveFunctionForFigure6(figure,stry);
						printFigureForFigure6(figure);
						
						if(isThereAnyValidMoveForFigure6(figure)==0)
							flag=0;
					}
						else
						cout<<endl<<"Please enter valid move string"<<endl;
				}
				else
				cout<<"Please enter valid string"<<endl;
			}
			
			cout<<"Remaining peg numbers are "<<remainderPegNumber(figure)<<endl;
			
		}
	}
	
	
	else if(choice =='c')
	{
		
		
		vector<vector<state>> figure= createFigure(figurechoice);
		
		printFigure(figure);
 	
 		if(figurechoice<6)
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
		
		else if(figurechoice==6)
		{	
			while(flag)
			{
				movename = randomStringGenerator(figure);
				stry=againString(movename);

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

string againString(string str)
{
	int firstnum=9,secondnum=9;
	string strx;
	
	firstnum=(int)str[1]-49;
	
	if(str[0]=='A')
		secondnum=4-firstnum;
	else if(str[0]=='B')
		secondnum=6-firstnum;
	else if(str[0]=='C')
		secondnum=8-firstnum;
	else if(str[0]=='D')
		secondnum=10-firstnum;
	else if(str[0]=='E')
		secondnum=12-firstnum;
	
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
	   
	    cout<<endl;
	    cout<<"  ";
	    
	    for(int k=65;k<65+csize;k++)
	    	cout<<(char)k;
	    
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
	
	    cout<<endl;

		for(int i=0;i<5;i++)
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
	int columnnum=5,rownum=5;

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
	int numberpeg=0;
	
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
