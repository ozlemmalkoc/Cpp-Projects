#include "PegSolitaire.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int PegSolitaire::totalNumberOfPeg = 0;

int firstOccurrenceCharacter(const string&);
int firstOccurrenceInteger(const string&);

/*
	Precondition: board -> One of the board types available
	Postcondition: Checks the board type whenever available or not. Then builds the board with given board type
*/
PegSolitaire::PegSolitaire(PEGSOLBOARD board)
{
	int boardNumber = static_cast<int>(board);

	if(boardNumber < 1 || boardNumber > 6)
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

/*
	Precondition: numberOfRow -> number of row for board
	Postcondition: Compares the number of row and MIN_SIZE. If number of row less than MIN_SIZE, program is terminated
					Otherwise, creates board.
*/
PegSolitaire::PegSolitaire(int numberOfRow)
{
	if(numberOfRow < MIN_SIZE)
	{
		cerr << "ERROR! Board should be larger than 5x5...\n";
		exit(EXIT_FAILURE);
	}

	for(int i=0 ; i < numberOfRow ; ++i)
	{
		vector<Cell> newRow;
		board.push_back(newRow);
	
		for(int j=0 ; j < numberOfRow ; ++j)
		{
			Cell newCell(i, j, State::PEG);
			board[i].push_back(newCell);
		}
	}

	board[numberOfRow / 2][numberOfRow / 2].setState(State::DOT);
	setTotalRow(numberOfRow);
	setTotalColumn(numberOfRow);
	setNumberOfPeg(numberOfRow * numberOfRow -1);
	setNumberOfEmpty(1);
	setNumberOfTaken(0);
	addToTotalNumberOfPeg(getNumberOfPeg());
}

/*
	Precondition: fileName -> given file name
	Postcondition: Reads from file and build board
*/
PegSolitaire::PegSolitaire(const string& fileName)
{
	if(!readFromFile(fileName))
		exit(EXIT_FAILURE);

	addToTotalNumberOfPeg(getNumberOfPeg());
}

/*
	Precondition: fileName -> given file name
	Postcondition: Reads from file and build board
*/
const bool PegSolitaire::readFromFile(const string& fileName)
{
	ifstream stream(fileName);

	if(!stream.is_open())
	{
		cerr << "ERROR! File couldn't be opened...\n";
		return false;
	}

	string buffer;
	int i=0, j=0, maxColumn=0;
	bool flag = true;

	for(i=0 ; getline(stream, buffer) && flag ; ++i)
		if((int)buffer.find('.') != -1 || (int)buffer.find('P') != -1)
		{
			vector<Cell> newRow;
			board.push_back(newRow);

			for(j=0 ; j < (int)buffer.size() ; ++j)
			{
				Cell newCell(i, j, static_cast<State>(buffer[j]));
				board[i].push_back(newCell);
			}

			if(j > maxColumn)
				maxColumn = j;
		}
		else
		{
			setNumberOfTaken(stoi(buffer));
			flag = false;
		}

	setTotalRow(i-1);
	setTotalColumn(maxColumn);
	setNumberOfPeg(countNumberOfPeg());
	setNumberOfEmpty(countNumberOfEmpty());

	stream.close();

	return true;
}

/*
	Precondition: fileName -> given file name
	Postcondition: Writes from file and build board
*/
const bool PegSolitaire::writeToFile(const string& fileName)const
{
	ofstream stream(fileName);

	if(!stream.is_open())
	{
		cerr << "ERROR! File couldn't be opened...\n";
		return false;
	}

	for(int i=0 ; i < getTotalRow() ; ++i)
	{
		for(int j=0 ; j < (int)board[i].size() ; ++j)
			stream << static_cast<char>(board[i][j].getState());

		stream << endl;
	}

	stream << getNumberOfTaken() << endl;
	stream << getNumberOfPeg() << endl;
	stream << getNumberOfEmpty() << endl;
	stream.close();
	
	return true;
}

/*
	Postcondition: Prints the current board on the screen
*/
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

const bool PegSolitaire::compare(const PegSolitaire& other)const { return this->getNumberOfPeg() > other.getNumberOfPeg(); }

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