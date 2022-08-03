#include "hw5.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ostream>

using namespace std;

namespace X{

int PegSolitaire::totalNumberOfPeg = 0;

int firstOccurrenceCharacter(const string&);
int firstOccurrenceInteger(const string&);

PegSolitaire::PegSolitaire()
{
	
}

void PegSolitaire::display()const
{
	cout << "  ";

	for(int i = 'A' ; i < 'A' + getTotalColumn() ; ++i)
		cout << (char)i;

	cout << endl;

	for(int i=0 ; i < getTotalRow() ; ++i)
	{	
		cout << i+1 << " ";
		
		for(int j=0 ; j < (int)board[i].size(); ++j)
			cout << static_cast<char>(board[i][j].getState());

		cout << endl;
	}
}

/*
	Postcondition: Checks movement and plays randomly
*/
const bool PegSolitaire::play()
{
	Direction dirs[] = {Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::DOWN};
	int column = rand() % getTotalColumn();
	int row = rand() % getTotalRow();
	Direction dir = dirs[rand() % 4];

	if(!isValidMove(row, column, dir))
		return false;

	setNumberOfPeg(getNumberOfPeg() - 1);
	setNumberOfEmpty(getNumberOfEmpty() + 1);
	setNumberOfTaken(getNumberOfTaken() + 1);

	move(row, column, dir);
	return true;
}

/*
	Precondition: move -> given movement
	Postcondition: Checks movement and plays
*/
const bool PegSolitaire::play(const string& move)
{
	int row = 0, column = 0;
	Direction dir;
	vector<string> v = split(move, '-');

	int firstCharPos = firstOccurrenceCharacter(move);

	if(firstCharPos != 0) return false;

	column = (int)((char)move[0] - 'A');

	int firstIntPos = firstOccurrenceInteger(move);

	if(firstIntPos != 1) return false;

	row = stoi(v[0].substr(firstIntPos)) - 1;

	dir = static_cast<Direction>(v[1][0]);

	if(!isValidMove(row, column, dir))
		return false;

	setNumberOfPeg(getNumberOfPeg() - 1);
	setNumberOfEmpty(getNumberOfEmpty() + 1);
	setNumberOfTaken(getNumberOfTaken() + 1);

	this->move(row, column, dir);
	return true;
}

/*
	Postconditions: Plays board until end.
*/
void PegSolitaire::playGame()
{
	display();

	while(isPlayable())
	{
		play();
		display();
	}
}

const bool PegSolitaire::isPlayable()const
{
	for(int i=0 ; i < getTotalRow() ; ++i)
		for(int j=0 ; j < (int)board[i].size() ; ++j)
			if(isValidMove(i, j, Direction::LEFT) || isValidMove(i, j, Direction::RIGHT) ||
				isValidMove(i, j, Direction::UP) || isValidMove(i, j, Direction::DOWN))
				return true;
	return false;
}

/*
	Precondition:	row -> row number
					column -> column number
					dir -> direction
	Postcondition: Checks whether move is valid or not. Return true if it is valid. Otherwise returns false.
*/
const bool PegSolitaire::isValidMove(int row, int column, Direction dir)const
{
	int xpos = 0, ypos = 0;

	switch(dir)
	{
		case Direction::LEFT:	xpos = -1; break;
		case Direction::RIGHT:	xpos = 1; break;
		case Direction::UP:		ypos = -1; break;
		default: 				ypos = 1; break;
	}

	if(board[row][column].getState() != State::PEG)
		return false;

	int destX = column + (xpos * 2);
	int destY = row + (ypos * 2);

	if(destY < 0 || destY >= getTotalRow())
		return false;

	if(destX < 0 || destX >= getTotalColumn() || destX >= (int)board[destY].size())
		return false;

	if(board[row + ypos][column + xpos].getState() != State::PEG)
		return false;

	if(board[destY][destX].getState() != State::DOT)
		return false;

	return true;
}

void PegSolitaire::move(int row, int column, Direction dir)
{
	int xpos = 0, ypos = 0;

	switch(dir)
	{
		case Direction::LEFT:	xpos = -1; break;
		case Direction::RIGHT:	xpos = 1; break;
		case Direction::UP:		ypos = -1; break;
		default: 				ypos = 1; break;
	}

	board[row][column].setState(State::DOT);
	board[row + ypos][column + xpos].setState(State::DOT);
	board[row + (ypos * 2)][column + (xpos * 2)].setState(State::PEG);
}

//const bool PegSolitaire::compare(const PegSolitaire& other)const { return this->getNumberOfPeg() > other.getNumberOfPeg(); }

int PegSolitaire::getTotalNumberOfPeg() { return totalNumberOfPeg; }

void PegSolitaire::addToTotalNumberOfPeg(int pegNumber) { totalNumberOfPeg += pegNumber; }

void PegSolitaire::decreaseTotalNumberOfPeg() { --totalNumberOfPeg; }

const int PegSolitaire::getTotalRow()const { return totalRow; }

const int PegSolitaire::getTotalColumn()const { return totalColumn; }

const int PegSolitaire::getNumberOfPeg()const { return numberOfPeg; }

const int PegSolitaire::getNumberOfEmpty()const { return numberOfEmpty; }

const int PegSolitaire::getNumberOfTaken()const { return numberOfTaken; }

void PegSolitaire::setTotalRow(int totalRow) { this->totalRow = totalRow; }

void PegSolitaire::setTotalColumn(int totalColumn) { this->totalColumn = totalColumn; }

void PegSolitaire::setNumberOfPeg(int numberOfPeg) { this->numberOfPeg = numberOfPeg; }

void PegSolitaire::setNumberOfEmpty(int numberOfEmpty) { this->numberOfEmpty = numberOfEmpty; }

void PegSolitaire::setNumberOfTaken(int numberOfTaken) { this->numberOfTaken = numberOfTaken; }

int PegSolitaire::countNumberOfPeg()const
{
	int total = 0;

	for(int i=0 ; i < getTotalRow() ; ++i)
		for(int j=0 ; j < (int)board[i].size() ; ++j)
			if(board[i][j].getState() == State::PEG)
				++total;

	return total;
}

int PegSolitaire::countNumberOfEmpty()const
{
	int total = 0;

	for(int i=0 ; i < getTotalRow() ; ++i)
		for(int j=0 ; j < (int)board[i].size() ; ++j)
			if(board[i][j].getState() == State::DOT)
				++total;

	return total;
}

PegSolitaire::Cell::Cell(int row, int column, State state): row(row), column(column), state(state) {}

const int PegSolitaire::Cell::getRow()const { return row; }

const int PegSolitaire::Cell::getColumn()const { return column; }

const State PegSolitaire::Cell::getState()const { return state; }

void PegSolitaire::Cell::setRow(int row) { this->row = row; }

void PegSolitaire::Cell::setColumn(int column) { this->column = column; }

void PegSolitaire::Cell::setState(State state) { this->state = state; }

vector<string> PegSolitaire::split(const string &str, const char& delimiter)
{
    vector<string> vec;
    stringstream ss (str);
    string buff;

    while(getline(ss, buff, delimiter))
        if(buff.size() != 0)
            vec.push_back(buff);

    return vec;
}

int firstOccurrenceCharacter(const string& str)
{
	for(int i=0 ; i < (int)str.size() ; ++i)
		if(str[i] >= 'A' && str[i] <= 'Z')
			return i;
	return -1;
}

int firstOccurrenceInteger(const string& str)
{
	for(int i=0 ; i < (int)str.size() ; ++i)
		if(str[i] >= '0' && str[i] <= '9')
			return i;
	return -1;
}


void PegSolitaire::playUser(string str){
 	
 	play(str);
}

void PegSolitaire::playUser(){

 	playGame();
}

int PegSolitaire::playAuto(){return play();}

void PegSolitaire::print(){

	cout << "\x1b[2J"; 
    cout << "\033[0;0H"; // move cursor to 0,0
    cout << endl << endl;display();}


int PegSolitaire::endGame(){
 	
 	if(isPlayable()==0)
 		return 1;
 	else
 		return 0;
 }
 
 int PegSolitaire::boardScore(){
 	
 	return countNumberOfPeg();
 }
 void PegSolitaire::initialize()
 {
 		int board =2;

 		int boardNumber = static_cast<int>(board);

	if(!2)
	{
		cerr << "ERROR! The board type couldn't founded...\n";
		exit(EXIT_FAILURE);
	}

	this->board = PEG_SOL_BOARD[boardNumber - 1];
	setTotalRow(this->board.size());
	setTotalColumn(this->board[0].size());
	setNumberOfPeg(countNumberOfPeg());
	setNumberOfEmpty(countNumberOfEmpty());
	setNumberOfTaken(0);
	addToTotalNumberOfPeg(getNumberOfPeg());
 }

void PegSolitaire::playAutoAll()
{
	while(isPlayable())
	{
		playAuto();
		display();
	}
}

 ostream& operator<<(ostream& out, const  PegSolitaire& ps)
 {
 	out << "\x1b[2J"; 
    out << "\033[0;0H"; // move cursor to 0,0
    out << endl << endl;
 	
    out << "  ";

	for(int i = 'A' ; i < 'A' + ps.getTotalColumn() ; ++i)
		out << (char)i;

	out << endl;

	for(int i=0 ; i < ps.getTotalRow() ; ++i)
	{	
		out << i+1 << " ";
		
		for(int j=0 ; j < (int)ps.board[i].size(); ++j)
			out << static_cast<char>(ps.board[i][j].getState());

		out << endl;
	}
	return out;
 }



}







