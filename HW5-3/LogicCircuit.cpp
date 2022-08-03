#include"LogicCircuit.h"


#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void LogicCircuit::printOutput()
{	
	for(int i=0 ; i < size -1; ++i)
		if(gates[i]->getGateName() == "OUTPUT")
			cout << ((Output*)gates[i])->getOutputValue() << ' ';
	cout << endl;
}


void LogicCircuit::readAndBuildArray()
{
	vector<string> fileContent = readFromFileLineByLine();
	
	for(int i=0 ; i < fileContent.size() ; ++i)
	{
		vector<string> content = splitString(fileContent[i]);

		if(content[0] == "INPUT")
		{
			createInputObjectsAndAddGateArray(content);
			continue;
		}
		else if(content[0] == "OUTPUT")
		{
			createOutputObjectsAndAddGateArray(content);
			continue;
		}

		Gate* gate = nullptr;

		if(content[0] == "AND")
		{
			And* andGate = new And;

			andGate->setGateName("AND");
			andGate->setOutputName(content[1]);
			andGate->setInputName1(content[2]);
			andGate->setInputName2(content[3]);

			gate = (Gate*)andGate;
		}

		if(content[0] == "OR")
		{
			Or* orGate = new Or;

			orGate->setGateName("OR");
			orGate->setOutputName(content[1]);
			orGate->setInputName1(content[2]);
			orGate->setInputName2(content[3]);

			gate = (Gate*)orGate;
			gate = (Gate*)orGate;
		}

		if(content[0] == "NOT")
		{
			Not* notGate = new Not;

			notGate->setGateName("NOT");
			notGate->setOutputName(content[1]);
			

			gate = (Gate*)notGate;
		}

		if(content[0] == "FLIPFLOP")
		{
			FlipFlop* flipflopGate = new FlipFlop;

			flipflopGate->setGateName("FLIPFLOP");
			flipflopGate->setOutputName(content[1]);
			flipflopGate->setInputName1(content[2]);
			gate = (Gate*)flipflopGate;
		}

		if(content[0] == "DECODER")
		{
			Decoder* decoderGate = new Decoder;

			decoderGate->setGateName("DECODER");
			decoderGate->setNameOutput1(content[1]);
			decoderGate->setNameOutput2(content[2]);
			decoderGate->setNameOutput3(content[3]);
			decoderGate->setNameOutput4(content[4]);

			decoderGate->setNameInput1(content[5]);
			decoderGate->setNameInput2(content[6]);

			gate = (Gate*)decoderGate;
		}

		addGateArray(gate);

	}
	


}

vector<string> LogicCircuit::readFromFileLineByLine()
{
	vector<string> vec;
	ifstream circuitFile("circuit.txt");

	for(string buffer ; getline(circuitFile, buffer) ;)
		vec.push_back(buffer);

	circuitFile.close();
	return vec;
}

vector<string> LogicCircuit::splitString(string source)
{
	vector<string> vec;
	istringstream myStream(source);
	string buffer;

	while(getline(myStream, buffer, ' '))
		vec.push_back(buffer);

	return vec;
}

void LogicCircuit::addGateArray(Gate* gate)
{
	if(gates == nullptr)
		gates = new Gate*[size + 1];
	else
	{
		Gate** temp = new Gate*[size + 1];

		for(int i=0 ; i < size ; ++i)
			temp[i] = gates[i];
		
		delete [] gates;
		gates = temp;
	}

	gates[size++] = gate;
}

void LogicCircuit::createInputObjectsAndAddGateArray(vector<string> content)
{
	for(int i=1 ; i < content.size() ; ++i)
	{
		Input* inputGate = new Input();

		inputGate->setGateName("INPUT");
		inputGate->setOutputName(content[i]);

		addGateArray(inputGate);
	}
}

void LogicCircuit::createOutputObjectsAndAddGateArray(vector<string> content)
{
	for(int i=1 ; i < content.size() ; ++i)
	{
		Output* outputGate = new Output();

		outputGate->setGateName("OUTPUT");
		outputGate->setOutputName(content[i]);

		addGateArray(outputGate);
	}
}

Gate* LogicCircuit::searchGateArray(string name)
{string e;
	for(int i=0 ; i < size - 1 ; ++i)
	{	e=gates[i]->getGateName(); 
		
		if(e=="INPUT")
		{	
			Input* ptr=(Input*) gates[i];
			if((ptr->getOutputName()).compare(name))
			return gates[i];
			
		}	
		else if(e=="OUTPUT")
		{
			Output* ptr=(Output*) gates[i];
			if((ptr->getOutputName()).compare(name))
			return gates[i];
			
		}	
		if(e=="AND")
		{	
			And* ptr=(And*) gates[i];
			if((ptr->getOutputName()).compare(name))
			return gates[i];
			
		}	
		if(e=="OR")
		{
			Or* ptr=(Or*) gates[i];
			if((ptr->getOutputName()).compare(name))
			return gates[i];
			
		}
		if(e=="NOT")
		{
			Not* ptr=(Not*) gates[i];
			if((ptr->getOutputName()).compare(name))
			return gates[i];
			
		}
		if(e=="FLIPFLOP")
		{
			FlipFlop* ptr=(FlipFlop*) gates[i];
			if((ptr->getOutputName()).compare(name))
			return gates[i];
			
		}
		if(e=="DECODER")
		{

			Decoder* ptr=(Decoder*) gates[i];
			if((ptr->getNameOutput1()).compare(name))
			return gates[i];
			if((ptr->getNameOutput2()).compare(name))
			return gates[i];
			if((ptr->getNameOutput3()).compare(name))
			return gates[i];
			if((ptr->getNameOutput4()).compare(name))
			return gates[i];
		}
		
}

	return nullptr;
}

void LogicCircuit::linkArray()
{
	for(int i = 0 ; i < size ; ++i)
	{
		if((gates[i]->getGateName()) == "INPUT" || (gates[i]->getGateName()) == "OUTPUT")
			continue;

		if((gates[i]->getGateName()) == "AND")
		{
			And* gate = (And*)gates[i];
		
			
			gate->setGateInput1(searchGateArray(gate->getInputName1()));
			gate->setGateInput2(searchGateArray(gate->getInputName2()));
			
		}
		if((gates[i]->getGateName() )== "OR")
		{
			Or* gate = (Or*)gates[i];
		
			
			gate->setGateInput1(searchGateArray(gate->getInputName1()));
			gate->setGateInput2(searchGateArray(gate->getInputName2()));
			
		}
		if((gates[i]->getGateName() )== "NOT")
		{
			Not* gate = (Not*)gates[i];
		
			
			gate->setGateInput1(searchGateArray(gate->getInputName1()));
		
			
		}
		if((gates[i]->getGateName() )== "FLIPFLOP")
		{
			FlipFlop* gate = (FlipFlop*)gates[i];
		
			
			gate->setGateInput1(searchGateArray(gate->getInputName1()));
		
			

		}

		if((gates[i]->getGateName() )== "DECODER")
		{
			Decoder* gate = (Decoder*)gates[i];
		
			
	
			gate->setInput1Gate(searchGateArray(gate->getNameInput1()));
			gate->setInput2Gate(searchGateArray(gate->getNameInput1()));
		

		
			
		}
}
}	

void LogicCircuit::readInputAndRunCircuit()
{
	vector<string> inputContent;
	ifstream inputStream("input.txt");
		

	for(string buffer; getline(inputStream, buffer) ;)
		inputContent.push_back(buffer);


	for(int i=0 ; i < inputContent.size(); ++i)
	{	

		vector<string> vec;

		istringstream myStream(inputContent[i]);

		string buffer;

		while(getline(myStream, buffer, ' '))
			vec.push_back(buffer);

		for(int j=0 ; j < vec.size() ; ++j)
			((Input*)gates[j])->setOutputValue(vec[j][0] - '0');
		
		
	
		string e;
		e=gates[size-1]->getGateName();

		if(e=="INPUT")
			{	
				((Input*)gates[size-1])->eval();

			}	
			else if(e=="OUTPUT")
			{
				((Output*)gates[size-1])->eval();
			}	
			if(e=="AND")
			{	((And*)gates[size-1])->eval();
			}	
			if(e=="OR")
			{
				((Or*)gates[size-1])->eval();
			}
			if(e=="NOT")
			{
				((Not*)gates[size-1])->eval();
			}
				
			
			if(e=="FLIPFLOP")
			{
				((FlipFlop*)gates[size-1])->eval();
			}
				
			
			if(e=="DECODER")
			{
				((Decoder*)gates[size-1])->eval();
			}
		printOutput();
}
}


