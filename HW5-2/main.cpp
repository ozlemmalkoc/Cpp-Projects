#include <iostream>
#include "hw5.h"
#include "Basis.h"
#include <ctime>
#include <cstdlib>
#include <vector>


using namespace std;
using namespace X;

int main(void)
{	
	srand(time(0));

	PegSolitaire ps,ps2;

	vector<BoardGame2D *> games;
	games.push_back(&ps);
	games.push_back(&ps2);
	playVector(games);

	return 0;
}