#ifndef _BASIS_H_
#define _BASIS_H_

namespace X{

enum class State
{
	EMPTY = ' ',
	PEG = 'P',
	DOT = '.'
};

enum class Direction
{
	LEFT = 'L',
	RIGHT = 'R',
	UP = 'U',
	DOWN = 'D'
};

enum class PEGSOLBOARD
{
	board1 = 1,
	board2,
	board3,
	board4,
	board5,
	board6
};
}

#endif