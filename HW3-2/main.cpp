#include <iostream>
#include "src/PegSolitaire.h"
#include "src/Basis.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main(void)
{
	srand(time(NULL));

	bool exit = false, subexit = false, flag = false;
	string str;
	char chrChoice;

	int choice,boardNumber;
	vector<string> v;
	string buffer;

	while(!exit)
	{
		PegSolitaire* p = nullptr;
		subexit = flag = false;

		cout << "---MENU---" << endl;
		cout << "1 - Start new game" << endl;
		cout << "2 - Load Game" << endl;
		cout << "3 - Creates square board" << endl;
		cout << "4 - Exit" << endl;
		cout << "Choice: ";
		cin >> choice;
		cin.ignore();

		switch(choice)
		{
			case 1:
				while(!subexit)
				{
					cout << "Please choose a figure between 1-6: ";
					cin >> boardNumber;

					if(boardNumber < 0 || boardNumber > 6)
						cerr << "Invalid choice." << endl;
					else
					{
						p = new PegSolitaire(static_cast<PEGSOLBOARD>(boardNumber));
						subexit = true;	
					}
				}
				break;
			case 2:
				cout << "File name: ";
				cin >> str;

				p = new PegSolitaire(str);
				break;
			case 3:
				cout << "Side: ";
				cin >> choice;

				p = new PegSolitaire(choice);
				break;
			case 4:
				exit = true;
				break;
			default:
				cerr << "Invalid value . Please enter between (1 - 4) numbers" << endl;
				break;
		}

		if(!exit)
		{
			while(p->isPlayable() && !flag)
			{	
				p->display();

				cout << "Who will play ? Enter 'h' for human , 'c' for computer . (h - c) " << endl;
				cin >> chrChoice;
				cin.ignore();
				
				if(chrChoice == 'h')
				{
					cout << "Please enter columnrow-direction ( Format -> ( columnnumberrownumber - direction ) -> ( A2-L ) )"<<endl;
					cout << "If you want to save your current game state , you can save the game with the file name you want by using this command . (SAVE FILENAME.TXT)"<<endl;
					
					getline(cin, buffer);
					v = PegSolitaire::split(buffer, ' ');
					
					if(v[0] == "SAVE")
					{	
						cout<<"The file is being saved..."<<endl;
						cout << "--File Format--\n";
						cout << "board\nnumber of taken pegs\nnumber of pegs\nnumber of empty cells\n";
						p->writeToFile(v[1]);
						flag = true;
					}
					else
						p->play(buffer);
				}
				else if(chrChoice == 'c')
					p->playGame();
			}

			if(!p->isPlayable())
			{
				p->display();
				cout << "WON" << endl;
				cout << p->getNumberOfPeg() << endl;
			}
		}

		delete p;
	}

	return 0;
}