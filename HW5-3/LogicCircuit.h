#ifndef LOGIC_CIRCUIT_H
#define LOGIC_CIRCUIT_H

#include "MyClass.h"
#include <vector>

using namespace std;

class LogicCircuit
{
	public:
		
		void readAndBuildArray();
		void linkArray();
		void readInputAndRunCircuit();
		void printOutput();
		int size = 0;

	private:
		vector<string> readFromFileLineByLine();
		vector<string> splitString(string source);
		void addGateArray(Gate*);
		void createInputObjectsAndAddGateArray(vector<string> content);
		void createOutputObjectsAndAddGateArray(vector<string> content);
		Gate* searchGateArray(string name);

		Gate** gates = nullptr;
		
};



#endif