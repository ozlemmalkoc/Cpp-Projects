#ifndef MYCLAS_H_
#define MYCLAS_H_


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Gate
{
	public:
		string getGateName(){return gateName;}
		void setGateName(string name) {gateName=name;}
		virtual int eval()=0;
	
	private:
		string gateName;
};

class Input:public Gate
{	
	public:
		string getOutputName(){return outputName;}
		void setOutputName(string name) {outputName=name;}
		int getOutputValue(){return outputValue;}
		void setOutputValue(int value) {outputValue=value;}
		virtual int eval(){return outputValue;}

	private:
		string outputName;
		int outputValue;
};

class Output:public Gate
{	
	public:
		string getOutputName(){return outputName;}
		void setOutputName(string name) {outputName=name;}
		int getOutputValue(){return outputValue;}
		void setOutputValue(int value) {outputValue=value;}
		virtual int eval(){return outputValue;}

	private:
		string outputName;
		int outputValue;
};

class And:public Gate
{		
	public:
		string getInputName1(){return inputName1;}
		string getInputName2(){return inputName2;}
		string getOutputName(){return outputName;}
		
		void setInputName1(string name) {inputName1=name;}
		void setInputName2(string name) {inputName2=name;}
		void setOutputName(string name) {outputName=name;}

		
		int getOutputValue(){return outputValue;}
		void setOutputValue(int value){outputValue=value;}
		
		Gate* getInput1(){return input1;}
		Gate* getInput2(){return input2;}
		void setGateInput1(Gate* gate){input1=gate;}
		void setGateInput2(Gate* gate){input2=gate;}
		
		virtual int eval()
		{
			int temp1, temp2;
			temp1=input1->eval();			
			temp2=input2->eval();
			outputValue=temp1 && temp2;
			return outputValue;
		}

	private:
		string inputName1;			
		string inputName2;			
		string outputName;			
		int outputValue;			
		Gate *input1;
		Gate *input2;
};

class Or:public Gate
{		
	public:
		string getInputName1(){return inputName1;}
		string getInputName2(){return inputName2;}
		string getOutputName(){return outputName;}
		
		void setInputName1(string name) {inputName1=name;}
		void setInputName2(string name) {inputName2=name;}
		void setOutputName(string name) {outputName=name;}

		
		int getOutputValue(){return outputValue;}
		void setOutputValue(int value){outputValue=value;}
		
		Gate* getInput1(){return input1;}
		Gate* getInput2(){return input2;}
		void setGateInput1(Gate* gate){input1=gate;}
		void setGateInput2(Gate* gate){input2=gate;}
		
		virtual int eval()
		{
			int temp1, temp2;
			
			temp1=input1->eval();			
			temp2=input2->eval();
			
			outputValue=temp1 || temp2;
			
			return outputValue;
		}

	private:
		string inputName1;			
		string inputName2;			
		string outputName;			
		int outputValue;			
		Gate *input1;
		Gate *input2;
};

class Not:public Gate
{		
	public:
		string getInputName1(){return inputName1;}
		
		string getOutputName(){return outputName;}
		
		void setInputName1(string name) {inputName1=name;}
		
		void setOutputName(string name) {outputName=name;}

		
		int getOutputValue(){return outputValue;}
		void setOutputValue(int value){outputValue=value;}
		
		Gate* getInput1(){return input1;}
		
		void setGateInput1(Gate* gate){input1=gate;}
		
		virtual int eval()
		{
			int temp1;
			temp1=input1->eval();			
			
			outputValue=!temp1;
			
			return outputValue;
		}

	private:
		string inputName1;			
		string outputName;			
		int outputValue;			
		Gate *input1;
	
};


class FlipFlop:public Gate
{
	public:
		
		string getInputName1(){return inputName1;}
		
		string getOutputName(){return outputName;}
		
		void setInputName1(string name) {inputName1=name;}
		
		void setOutputName(string name) {outputName=name;}

		
		int getOutputValue(){return outputValue;}
		void setOutputValue(int value){outputValue=value;}
		
		Gate* getInput1(){return input1;}
		
		void setGateInput1(Gate* gate){input1=gate;}
		

    	int eval()
    	{
    		if(input1->eval() == memory){
    	    	memory = 0;
    	    }
    	    else{
    	    	memory = 1;
        	}

        	return memory;
    	}
   
    private:
    	string outputName;
		string inputName1;
    	Gate* input1;
    	int memory = 0;
    	int outputValue;
    	
};

class Decoder:public Gate
{
	public:
		string getNameInput1() { return input1; }
		string getNameInput2() { return input2; }
		string getNameOutput1() { return output1; }
		string getNameOutput2() { return output2; }
		string getNameOutput3() { return output3; }
		string getNameOutput4() { return output4; }

		int getOutput1() { return outputValue1; }
		int getOutput2() { return outputValue1; }
		int getOutput3() { return outputValue1; }
		int getOutput4() { return outputValue1; }
		
		void setInput1Value(int val) { inputValue1 = val; }
		void setInput2Value(int val) { inputValue2 = val; }
		void setOutput1Value(int val) { outputValue1 = val; }
		void setOutput2Value(int val) { outputValue2 = val; }
		void setOutput3Value(int val) { outputValue3 = val; }
		void setOutput4Value(int val) { outputValue4 = val; }

		void setNameInput1(string name) { input1 = name; }
		void setNameInput2(string name) { input2 = name; }
		void setNameOutput1(string name) { output1 = name; }
		void setNameOutput2(string name) { output2 = name; }
		void setNameOutput3(string name) { output3 = name; }
		void setNameOutput4(string name) { output4 = name; }
		void setInput1Gate(Gate* gate) { gateInput1 = gate; }
		void setInput2Gate(Gate* gate) { gateInput2 = gate; }
		void setOutput1Gate(Gate* gate) { gateOutput1 = gate; }
		void setOutput2Gate(Gate* gate) { gateOutput2 = gate; }
		void setOutput3Gate(Gate* gate) { gateOutput3 = gate; }
		void setOutput4Gate(Gate* gate) { gateOutput4 = gate; }

		virtual int eval()
		{
			int in1=gateInput1->eval();
			int in2 = gateInput2->eval();


			if(in1 == 0 && in2 == 0)
				this->setOutput1Value(1);
			else if(in1 == 0 && in2 == 1)
				this->setOutput2Value(1);
			else if(in1 == 1 && in2 == 0)
				this->setOutput3Value(1);
			else if(in1 == 1 && in2 == 1)
				this->setOutput4Value(1);
			return 1;
		}

	private:
		Gate* gateInput1 = nullptr, *gateInput2 = nullptr, *gateOutput1 = nullptr, *gateOutput2 = nullptr, *gateOutput3 = nullptr, *gateOutput4 = nullptr;

		string input1;
		int inputValue1 = 0;

		string input2;
		int inputValue2 = 0;

		string output1;
		int outputValue1 = 0;

		string output2;
		int outputValue2 = 0;

		string output3;
		int outputValue3 = 0;

		string output4;
		int outputValue4 = 0;
};

#endif