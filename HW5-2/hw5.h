#ifndef _HEADER_H
#define _HEADER_H

#include "Basis.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


namespace X{

class BoardGame2D{


public:
	virtual void playUser(string)=0;
	virtual void playUser()=0;
	virtual int playAuto()=0;
	virtual void playAutoAll()=0;
	virtual void print()=0;
	virtual int endGame()=0;
	virtual int boardScore()=0;
	virtual void initialize()=0;
};

class PegSolitaire:public BoardGame2D
{
	public:
		PegSolitaire();
		
		void display()const;
		const bool play();
		const bool play(const string&);
		void playGame();
		const bool isPlayable()const;
		static vector<string> split(const string&, const char&);
		
		const int getTotalRow()const;
		const int getTotalColumn()const;
		const int getNumberOfPeg()const;
		const int getNumberOfEmpty()const;
		const int getNumberOfTaken()const;
		
		void setTotalRow(int);
		void setTotalColumn(int);
		void setNumberOfPeg(int);
		void setNumberOfEmpty(int);
		void setNumberOfTaken(int);

		void playUser(string);
		void playUser();
		int playAuto();	
		void print();
		int endGame();	 
		int boardScore();
		void initialize();
		void playAutoAll();
		
		static int getTotalNumberOfPeg();
		static void addToTotalNumberOfPeg(int);
		static void decreaseTotalNumberOfPeg(); // Decreases the total number of peg by 1

		const bool isValidMove(int, int, Direction)const;
		void move(int, int, Direction);
		void createBoard(int);
		int countNumberOfPeg()const;
		int countNumberOfEmpty()const;
		friend ostream& operator<<(ostream& , const  PegSolitaire& );


		class Cell
		{
			public:
				Cell(int, int, State);

				const int getRow()const;
				const int getColumn()const;
				const State getState()const;

				void setRow(int);
				void setColumn(int);
				void setState(State);
				
			private:
				int row;
				int column;
				State state;
		};

	private:
		
		const int MIN_SIZE = 5;
		vector<vector<Cell>> board;
		int totalRow;
		int totalColumn;
		int numberOfPeg;
		int numberOfEmpty;
		int numberOfTaken;
		static int totalNumberOfPeg;
};

const vector<vector<vector<PegSolitaire::Cell>>> PEG_SOL_BOARD = {
	{
		{PegSolitaire::Cell(0,0,State::EMPTY),	PegSolitaire::Cell(0,1,State::EMPTY),	PegSolitaire::Cell(0,2,State::PEG),		PegSolitaire::Cell(0,3,State::PEG),		PegSolitaire::Cell(0,4,State::PEG),		PegSolitaire::Cell(0,5,State::EMPTY),	PegSolitaire::Cell(0,6,State::EMPTY)	},
		{PegSolitaire::Cell(1,0,State::EMPTY),	PegSolitaire::Cell(1,1,State::PEG),		PegSolitaire::Cell(1,2,State::PEG),		PegSolitaire::Cell(1,3,State::PEG),		PegSolitaire::Cell(1,4,State::PEG),		PegSolitaire::Cell(1,5,State::PEG),		PegSolitaire::Cell(1,6,State::EMPTY)	},
		{PegSolitaire::Cell(2,0,State::PEG),	PegSolitaire::Cell(2,1,State::PEG),		PegSolitaire::Cell(2,2,State::PEG),		PegSolitaire::Cell(2,3,State::DOT),		PegSolitaire::Cell(2,4,State::PEG),		PegSolitaire::Cell(2,5,State::PEG),		PegSolitaire::Cell(2,6,State::PEG)		},
		{PegSolitaire::Cell(3,0,State::PEG),	PegSolitaire::Cell(3,1,State::PEG),		PegSolitaire::Cell(3,2,State::PEG),		PegSolitaire::Cell(3,3,State::PEG),		PegSolitaire::Cell(3,4,State::PEG),		PegSolitaire::Cell(3,5,State::PEG),		PegSolitaire::Cell(3,6,State::PEG)		},
		{PegSolitaire::Cell(4,0,State::PEG),	PegSolitaire::Cell(4,1,State::PEG),		PegSolitaire::Cell(4,2,State::PEG),		PegSolitaire::Cell(4,3,State::PEG),		PegSolitaire::Cell(4,4,State::PEG),		PegSolitaire::Cell(4,5,State::PEG),		PegSolitaire::Cell(4,6,State::PEG)		},
		{PegSolitaire::Cell(5,0,State::EMPTY),	PegSolitaire::Cell(5,1,State::PEG),		PegSolitaire::Cell(5,2,State::PEG),		PegSolitaire::Cell(5,3,State::PEG),		PegSolitaire::Cell(5,4,State::PEG),		PegSolitaire::Cell(5,5,State::PEG),		PegSolitaire::Cell(5,6,State::EMPTY)	},
		{PegSolitaire::Cell(6,0,State::EMPTY),	PegSolitaire::Cell(6,1,State::EMPTY),	PegSolitaire::Cell(6,2,State::PEG),		PegSolitaire::Cell(6,3,State::PEG),		PegSolitaire::Cell(6,4,State::PEG),		PegSolitaire::Cell(6,5,State::EMPTY),	PegSolitaire::Cell(6,6,State::EMPTY)	}
	},
	{	
		{PegSolitaire::Cell(0,0,State::EMPTY),	PegSolitaire::Cell(0,1,State::EMPTY),	PegSolitaire::Cell(0,2,State::EMPTY),	PegSolitaire::Cell(0,3,State::PEG),		PegSolitaire::Cell(0,4,State::PEG),		PegSolitaire::Cell(0,5,State::PEG),		PegSolitaire::Cell(0,6,State::EMPTY),	PegSolitaire::Cell(0,7,State::EMPTY),	PegSolitaire::Cell(0,8,State::EMPTY)	},
		{PegSolitaire::Cell(1,0,State::EMPTY),	PegSolitaire::Cell(1,1,State::EMPTY),	PegSolitaire::Cell(1,2,State::EMPTY),	PegSolitaire::Cell(1,3,State::PEG),		PegSolitaire::Cell(1,4,State::PEG),		PegSolitaire::Cell(1,5,State::PEG),		PegSolitaire::Cell(1,6,State::EMPTY),	PegSolitaire::Cell(1,7,State::EMPTY),	PegSolitaire::Cell(1,8,State::EMPTY)	},
		{PegSolitaire::Cell(2,0,State::EMPTY),	PegSolitaire::Cell(2,1,State::EMPTY),	PegSolitaire::Cell(2,2,State::EMPTY),	PegSolitaire::Cell(2,3,State::PEG),		PegSolitaire::Cell(2,4,State::PEG),		PegSolitaire::Cell(2,5,State::PEG),		PegSolitaire::Cell(2,6,State::EMPTY),	PegSolitaire::Cell(2,7,State::EMPTY),	PegSolitaire::Cell(2,8,State::EMPTY)	},
		{PegSolitaire::Cell(3,0,State::PEG),	PegSolitaire::Cell(3,1,State::PEG),		PegSolitaire::Cell(3,2,State::PEG),		PegSolitaire::Cell(3,3,State::PEG),		PegSolitaire::Cell(3,4,State::PEG),		PegSolitaire::Cell(3,5,State::PEG),		PegSolitaire::Cell(3,6,State::PEG),		PegSolitaire::Cell(3,7,State::PEG),		PegSolitaire::Cell(3,8,State::PEG)		},
		{PegSolitaire::Cell(4,0,State::PEG),	PegSolitaire::Cell(4,1,State::PEG),		PegSolitaire::Cell(4,2,State::PEG),		PegSolitaire::Cell(4,3,State::PEG),		PegSolitaire::Cell(4,4,State::DOT),		PegSolitaire::Cell(4,5,State::PEG),		PegSolitaire::Cell(4,6,State::PEG),		PegSolitaire::Cell(4,7,State::PEG),		PegSolitaire::Cell(4,8,State::PEG)		},
		{PegSolitaire::Cell(5,0,State::PEG),	PegSolitaire::Cell(5,1,State::PEG),		PegSolitaire::Cell(5,2,State::PEG),		PegSolitaire::Cell(5,3,State::PEG),		PegSolitaire::Cell(5,4,State::PEG),		PegSolitaire::Cell(5,5,State::PEG),		PegSolitaire::Cell(5,6,State::PEG),		PegSolitaire::Cell(5,7,State::PEG),		PegSolitaire::Cell(5,8,State::PEG)		},
		{PegSolitaire::Cell(6,0,State::EMPTY),	PegSolitaire::Cell(6,1,State::EMPTY),	PegSolitaire::Cell(6,2,State::EMPTY),	PegSolitaire::Cell(6,3,State::PEG),		PegSolitaire::Cell(6,4,State::PEG),		PegSolitaire::Cell(6,5,State::PEG),		PegSolitaire::Cell(6,6,State::EMPTY),	PegSolitaire::Cell(6,7,State::EMPTY),	PegSolitaire::Cell(6,8,State::EMPTY)	},
		{PegSolitaire::Cell(7,0,State::EMPTY),	PegSolitaire::Cell(7,1,State::EMPTY),	PegSolitaire::Cell(7,2,State::EMPTY),	PegSolitaire::Cell(7,3,State::PEG),		PegSolitaire::Cell(7,4,State::PEG),		PegSolitaire::Cell(7,5,State::PEG),		PegSolitaire::Cell(7,6,State::EMPTY),	PegSolitaire::Cell(7,7,State::EMPTY),	PegSolitaire::Cell(7,8,State::EMPTY)	},
		{PegSolitaire::Cell(8,0,State::EMPTY),	PegSolitaire::Cell(8,1,State::EMPTY),	PegSolitaire::Cell(8,2,State::EMPTY),	PegSolitaire::Cell(8,3,State::PEG),		PegSolitaire::Cell(8,4,State::PEG),		PegSolitaire::Cell(8,5,State::PEG),		PegSolitaire::Cell(8,6,State::EMPTY),	PegSolitaire::Cell(8,7,State::EMPTY),	PegSolitaire::Cell(8,8,State::EMPTY)	}
	},
	{
		{PegSolitaire::Cell(0,0,State::EMPTY),	PegSolitaire::Cell(0,1,State::EMPTY),	PegSolitaire::Cell(0,2,State::PEG),		PegSolitaire::Cell(0,3,State::PEG),		PegSolitaire::Cell(0,4,State::PEG),		PegSolitaire::Cell(0,5,State::EMPTY),	PegSolitaire::Cell(0,6,State::EMPTY),	PegSolitaire::Cell(0,7,State::EMPTY)	},
		{PegSolitaire::Cell(1,0,State::EMPTY),	PegSolitaire::Cell(1,1,State::EMPTY),	PegSolitaire::Cell(1,2,State::PEG),		PegSolitaire::Cell(1,3,State::PEG),		PegSolitaire::Cell(1,4,State::PEG),		PegSolitaire::Cell(1,5,State::EMPTY),	PegSolitaire::Cell(1,6,State::EMPTY),	PegSolitaire::Cell(1,7,State::EMPTY)	},
		{PegSolitaire::Cell(2,0,State::EMPTY),	PegSolitaire::Cell(2,1,State::EMPTY),	PegSolitaire::Cell(2,2,State::PEG),		PegSolitaire::Cell(2,3,State::PEG),		PegSolitaire::Cell(2,4,State::PEG),		PegSolitaire::Cell(2,5,State::EMPTY),	PegSolitaire::Cell(2,6,State::EMPTY),	PegSolitaire::Cell(2,7,State::EMPTY)	},
		{PegSolitaire::Cell(3,0,State::PEG),	PegSolitaire::Cell(3,1,State::PEG),		PegSolitaire::Cell(3,2,State::PEG),		PegSolitaire::Cell(3,3,State::PEG),		PegSolitaire::Cell(3,4,State::PEG),		PegSolitaire::Cell(3,5,State::PEG),		PegSolitaire::Cell(3,6,State::PEG),		PegSolitaire::Cell(3,7,State::PEG)		},
		{PegSolitaire::Cell(4,0,State::PEG),	PegSolitaire::Cell(4,1,State::PEG),		PegSolitaire::Cell(4,2,State::PEG),		PegSolitaire::Cell(4,3,State::DOT),		PegSolitaire::Cell(4,4,State::PEG),		PegSolitaire::Cell(4,5,State::PEG),		PegSolitaire::Cell(4,6,State::PEG),		PegSolitaire::Cell(4,7,State::PEG)		},
		{PegSolitaire::Cell(5,0,State::PEG),	PegSolitaire::Cell(5,1,State::PEG),		PegSolitaire::Cell(5,2,State::PEG),		PegSolitaire::Cell(5,3,State::PEG),		PegSolitaire::Cell(5,4,State::PEG),		PegSolitaire::Cell(5,5,State::PEG),		PegSolitaire::Cell(5,6,State::PEG),		PegSolitaire::Cell(5,7,State::PEG)		},
		{PegSolitaire::Cell(6,0,State::EMPTY),	PegSolitaire::Cell(6,1,State::EMPTY),	PegSolitaire::Cell(6,2,State::PEG),		PegSolitaire::Cell(6,3,State::PEG),		PegSolitaire::Cell(6,4,State::PEG),		PegSolitaire::Cell(6,5,State::EMPTY),	PegSolitaire::Cell(6,6,State::EMPTY),	PegSolitaire::Cell(6,7,State::EMPTY)	},
		{PegSolitaire::Cell(7,0,State::EMPTY),	PegSolitaire::Cell(7,1,State::EMPTY),	PegSolitaire::Cell(7,2,State::PEG),		PegSolitaire::Cell(7,3,State::PEG),		PegSolitaire::Cell(7,4,State::PEG),		PegSolitaire::Cell(7,5,State::EMPTY),	PegSolitaire::Cell(7,6,State::EMPTY),	PegSolitaire::Cell(7,7,State::EMPTY)	}
	},
	{
		{PegSolitaire::Cell(0,0,State::EMPTY),	PegSolitaire::Cell(0,1,State::EMPTY),	PegSolitaire::Cell(0,2,State::PEG),		PegSolitaire::Cell(0,3,State::PEG),		PegSolitaire::Cell(0,4,State::PEG),		PegSolitaire::Cell(0,5,State::EMPTY),	PegSolitaire::Cell(0,6,State::EMPTY)	},
		{PegSolitaire::Cell(1,0,State::EMPTY),	PegSolitaire::Cell(1,1,State::EMPTY),	PegSolitaire::Cell(1,2,State::PEG),		PegSolitaire::Cell(1,3,State::PEG),		PegSolitaire::Cell(1,4,State::PEG),		PegSolitaire::Cell(1,5,State::EMPTY),	PegSolitaire::Cell(1,6,State::EMPTY)	},
		{PegSolitaire::Cell(2,0,State::PEG),	PegSolitaire::Cell(2,1,State::PEG),		PegSolitaire::Cell(2,2,State::PEG),		PegSolitaire::Cell(2,3,State::PEG),		PegSolitaire::Cell(2,4,State::PEG),		PegSolitaire::Cell(2,5,State::PEG),		PegSolitaire::Cell(2,6,State::PEG)		},
		{PegSolitaire::Cell(3,0,State::PEG),	PegSolitaire::Cell(3,1,State::PEG),		PegSolitaire::Cell(3,2,State::PEG),		PegSolitaire::Cell(3,3,State::DOT),		PegSolitaire::Cell(3,4,State::PEG),		PegSolitaire::Cell(3,5,State::PEG),		PegSolitaire::Cell(3,6,State::PEG)		},
		{PegSolitaire::Cell(4,0,State::PEG),	PegSolitaire::Cell(4,1,State::PEG),		PegSolitaire::Cell(4,2,State::PEG),		PegSolitaire::Cell(4,3,State::PEG),		PegSolitaire::Cell(4,4,State::PEG),		PegSolitaire::Cell(4,5,State::PEG),		PegSolitaire::Cell(4,6,State::PEG)		},
		{PegSolitaire::Cell(5,0,State::EMPTY),	PegSolitaire::Cell(5,1,State::EMPTY),	PegSolitaire::Cell(5,2,State::PEG),		PegSolitaire::Cell(5,3,State::PEG),		PegSolitaire::Cell(5,4,State::PEG),		PegSolitaire::Cell(5,5,State::EMPTY),	PegSolitaire::Cell(5,6,State::EMPTY)	},
		{PegSolitaire::Cell(6,0,State::EMPTY),	PegSolitaire::Cell(6,1,State::EMPTY),	PegSolitaire::Cell(6,2,State::PEG),		PegSolitaire::Cell(6,3,State::PEG),		PegSolitaire::Cell(6,4,State::PEG),		PegSolitaire::Cell(6,5,State::EMPTY),	PegSolitaire::Cell(6,6,State::EMPTY)	}
	},
	{
		{PegSolitaire::Cell(0,0,State::EMPTY),	PegSolitaire::Cell(0,1,State::EMPTY),	PegSolitaire::Cell(0,2,State::EMPTY),	PegSolitaire::Cell(0,3,State::EMPTY),	PegSolitaire::Cell(0,4,State::PEG),		PegSolitaire::Cell(0,5,State::EMPTY),	PegSolitaire::Cell(0,6,State::EMPTY),	PegSolitaire::Cell(0,7,State::EMPTY),	PegSolitaire::Cell(0,8,State::EMPTY)	},
		{PegSolitaire::Cell(1,0,State::EMPTY),	PegSolitaire::Cell(1,1,State::EMPTY),	PegSolitaire::Cell(1,2,State::EMPTY),	PegSolitaire::Cell(1,3,State::PEG),		PegSolitaire::Cell(1,4,State::PEG),		PegSolitaire::Cell(1,5,State::PEG),		PegSolitaire::Cell(1,6,State::EMPTY),	PegSolitaire::Cell(1,7,State::EMPTY),	PegSolitaire::Cell(1,8,State::EMPTY)	},
		{PegSolitaire::Cell(2,0,State::EMPTY),	PegSolitaire::Cell(2,1,State::EMPTY),	PegSolitaire::Cell(2,2,State::PEG),		PegSolitaire::Cell(2,3,State::PEG),		PegSolitaire::Cell(2,4,State::PEG),		PegSolitaire::Cell(2,5,State::PEG),		PegSolitaire::Cell(2,6,State::PEG),		PegSolitaire::Cell(2,7,State::EMPTY),	PegSolitaire::Cell(2,8,State::EMPTY)	},
		{PegSolitaire::Cell(3,0,State::EMPTY),	PegSolitaire::Cell(3,1,State::PEG),		PegSolitaire::Cell(3,2,State::PEG),		PegSolitaire::Cell(3,3,State::PEG),		PegSolitaire::Cell(3,4,State::PEG),		PegSolitaire::Cell(3,5,State::PEG),		PegSolitaire::Cell(3,6,State::PEG),		PegSolitaire::Cell(3,7,State::PEG),		PegSolitaire::Cell(3,8,State::EMPTY)	},
		{PegSolitaire::Cell(4,0,State::PEG),	PegSolitaire::Cell(4,1,State::PEG),		PegSolitaire::Cell(4,2,State::PEG),		PegSolitaire::Cell(4,3,State::PEG),		PegSolitaire::Cell(4,4,State::DOT),		PegSolitaire::Cell(4,5,State::PEG),		PegSolitaire::Cell(4,6,State::PEG),		PegSolitaire::Cell(4,7,State::PEG),		PegSolitaire::Cell(4,8,State::PEG)		},
		{PegSolitaire::Cell(5,0,State::EMPTY),	PegSolitaire::Cell(5,1,State::PEG),		PegSolitaire::Cell(5,2,State::PEG),		PegSolitaire::Cell(5,3,State::PEG),		PegSolitaire::Cell(5,4,State::PEG),		PegSolitaire::Cell(5,5,State::PEG),		PegSolitaire::Cell(5,6,State::PEG),		PegSolitaire::Cell(5,7,State::PEG),		PegSolitaire::Cell(5,8,State::EMPTY)	},
		{PegSolitaire::Cell(6,0,State::EMPTY),	PegSolitaire::Cell(6,1,State::EMPTY),	PegSolitaire::Cell(6,2,State::PEG),		PegSolitaire::Cell(6,3,State::PEG),		PegSolitaire::Cell(6,4,State::PEG),		PegSolitaire::Cell(6,5,State::PEG),		PegSolitaire::Cell(6,6,State::PEG),		PegSolitaire::Cell(6,7,State::EMPTY),	PegSolitaire::Cell(6,8,State::EMPTY)	},
		{PegSolitaire::Cell(7,0,State::EMPTY),	PegSolitaire::Cell(7,1,State::EMPTY),	PegSolitaire::Cell(7,2,State::EMPTY),	PegSolitaire::Cell(7,3,State::PEG),		PegSolitaire::Cell(7,4,State::PEG),		PegSolitaire::Cell(7,5,State::PEG),		PegSolitaire::Cell(7,6,State::EMPTY),	PegSolitaire::Cell(7,7,State::EMPTY),	PegSolitaire::Cell(7,8,State::EMPTY)	},
		{PegSolitaire::Cell(8,0,State::EMPTY),	PegSolitaire::Cell(8,1,State::EMPTY),	PegSolitaire::Cell(8,2,State::EMPTY),	PegSolitaire::Cell(8,3,State::EMPTY),	PegSolitaire::Cell(8,4,State::PEG),		PegSolitaire::Cell(8,5,State::EMPTY),	PegSolitaire::Cell(8,6,State::EMPTY),	PegSolitaire::Cell(8,7,State::EMPTY),	PegSolitaire::Cell(8,8,State::EMPTY)	}
	},
	{
		{PegSolitaire::Cell(0,0,State::EMPTY),	PegSolitaire::Cell(0,1,State::EMPTY),	PegSolitaire::Cell(0,2,State::EMPTY),	PegSolitaire::Cell(0,3,State::EMPTY),	PegSolitaire::Cell(0,4,State::DOT),		PegSolitaire::Cell(0,5,State::EMPTY),	PegSolitaire::Cell(0,6,State::EMPTY),	PegSolitaire::Cell(0,7,State::EMPTY),	PegSolitaire::Cell(0,8,State::EMPTY)	},
		{PegSolitaire::Cell(1,0,State::EMPTY),	PegSolitaire::Cell(1,1,State::EMPTY),	PegSolitaire::Cell(1,2,State::EMPTY),	PegSolitaire::Cell(1,3,State::PEG),		PegSolitaire::Cell(1,4,State::EMPTY),	PegSolitaire::Cell(1,5,State::PEG),		PegSolitaire::Cell(1,6,State::EMPTY),	PegSolitaire::Cell(1,7,State::EMPTY),	PegSolitaire::Cell(1,8,State::EMPTY)	},
		{PegSolitaire::Cell(2,0,State::EMPTY),	PegSolitaire::Cell(2,1,State::EMPTY),	PegSolitaire::Cell(2,2,State::PEG),		PegSolitaire::Cell(2,3,State::EMPTY),	PegSolitaire::Cell(2,4,State::PEG),		PegSolitaire::Cell(2,5,State::EMPTY),	PegSolitaire::Cell(2,6,State::PEG),		PegSolitaire::Cell(2,7,State::EMPTY),	PegSolitaire::Cell(2,8,State::EMPTY)	},
		{PegSolitaire::Cell(3,0,State::EMPTY),	PegSolitaire::Cell(3,1,State::PEG),		PegSolitaire::Cell(3,2,State::EMPTY),	PegSolitaire::Cell(3,3,State::PEG),		PegSolitaire::Cell(3,4,State::EMPTY),	PegSolitaire::Cell(3,5,State::PEG),		PegSolitaire::Cell(3,6,State::EMPTY),	PegSolitaire::Cell(3,7,State::PEG),		PegSolitaire::Cell(3,8,State::EMPTY)	},
		{PegSolitaire::Cell(4,0,State::PEG),	PegSolitaire::Cell(4,1,State::EMPTY),	PegSolitaire::Cell(4,2,State::PEG),		PegSolitaire::Cell(4,3,State::EMPTY),	PegSolitaire::Cell(4,4,State::PEG),		PegSolitaire::Cell(4,5,State::EMPTY),	PegSolitaire::Cell(4,6,State::PEG),		PegSolitaire::Cell(4,7,State::EMPTY),	PegSolitaire::Cell(4,8,State::PEG)		}
	}
};

static void playVector(vector<BoardGame2D *> game)
{
	for(int i=0;i<2;i++)
	{
		game[i]->initialize();
		cout<<game[i];
		game[i]->playUser("C5-R");
		game[i]->print();
		cout<<endl<<"Remaining peg count : "<<game[i]->boardScore()<<endl;
		
		game[i]->initialize();
		game[i]->playUser();
		game[i]->print();
		cout<<endl<<"Remaining peg count : "<<game[i]->boardScore()<<endl;
		
		game[i]->initialize();
		game[i]->playAutoAll();
		game[i]->print();
		cout<<endl<<"Remaining peg count : "<<game[i]->boardScore()<<endl;
		cout<<endl<<"End Game Value : "<<game[i]->endGame();
		
	}
}

}


#endif