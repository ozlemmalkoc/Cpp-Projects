#include <fstream>
#include <vector>
#include "SparseVector.h"

using namespace std;

SparseVector::SparseVector(string fileName) // A constructor which takes a string filenamedata, opens the file, reads the contents, creates and populates an object.
{
	ifstream myfile;
	myfile.open(fileName);

	string str;
	Vec temp; // Holds index and data varlues
	
	while(getline(myfile,str,':') && !myfile.eof())	// If it can be read up to the ':' character and the end of the file is not reached, the loop is entered.
	{
		temp.index=stoi(str);
	
		getline(myfile,str,' ');
		temp.data=stod(str);
	
		vec.push_back(temp);
	}	
}

SparseVector SparseVector::operator+(const SparseVector & obj)const	// Adds two SparseVectors. Creates another SparseVector object.
{	
	Vec temp;	// Holds index and data varlues
	SparseVector a; 
	int j=0;
	bool flag=0;

	for(int i=0;i<static_cast<int>(vec.size());i++)
	{	for(;j<static_cast<int>(obj.vec.size());j++)
		{	if(vec[i].index==obj.vec[j].index)	// if index values are equal
			{	
				flag=1;
				break;
			}
		}
		
		if(flag==1)
			temp.data=vec[i].data+obj.vec[j].data;	// Values in the same index are summed.
		else
		temp.data=vec[i].data;
		temp.index=vec[i].index;

		a.vec.push_back(temp);
		flag=0;
	}

	for(int i=0;i<static_cast<int>(obj.vec.size());i++)
	{	for(j=0;j<static_cast<int>(vec.size());j++)
		{	if(obj.vec[i].index==vec[j].index)
			{
				flag=1;
				break;
			}
		}
		
		if(flag==0)
		{	temp.data=obj.vec[i].data;
			temp.index=obj.vec[i].index;
			a.vec.push_back(temp);
		}
		flag=0;
	}

for(int k=0;k<static_cast<int>(a.vec.size());k++)	// The resulting vector data is ordered from smallest to largest.
{	for(int h=1;h<static_cast<int>(a.vec.size());h++)	
	{	if(a.vec[h-1].index>a.vec[h].index)
		{
			temp=a.vec[h];
			a.vec[h]=a.vec[h-1];
			a.vec[h-1]=temp;
		}	
	}
}
return a;
}
SparseVector SparseVector::operator-(const SparseVector & obj)const	// Subtracts one SparseVector from another. Creates another SparseVector object.
{	
	Vec temp;	
	SparseVector a; 
	int j=0;
	bool flag=0;

	for(int i=0;i<static_cast<int>(vec.size());i++)
	{	for(;j<static_cast<int>(obj.vec.size());j++)
		{	if(vec[i].index==obj.vec[j].index)	// if index values are equal
			{	
				flag=1;
				break;
			}
		}
		
		if(flag==1)
			temp.data=vec[i].data-obj.vec[j].data;	// Values in the same index are subtracted.
		else	// if index values aren't equal
		temp.data=-vec[i].data;
		temp.index=vec[i].index;

		a.vec.push_back(temp);
		flag=0;
	}

	for(int i=0;i<static_cast<int>(obj.vec.size());i++)
	{	for(j=0;j<static_cast<int>(vec.size());j++)
		{	if(obj.vec[i].index==vec[j].index)
			{
				flag=1;
				break;
			}
		}
		
		if(flag==0)
		{	temp.data=-obj.vec[i].data;
			temp.index=obj.vec[i].index;
			a.vec.push_back(temp);
		}
		flag=0;
	}

for(int k=0;k<static_cast<int>(a.vec.size());k++)	// The resulting vector data is ordered from smallest to largest.
{	for(int h=1;h<static_cast<int>(a.vec.size());h++)	
	{	if(a.vec[h-1].index>a.vec[h].index)
		{
			temp=a.vec[h];
			a.vec[h]=a.vec[h-1];
			a.vec[h-1]=temp;
		}	
	}
}
return a;
}

ostream & operator<<(ostream& output,const SparseVector & obj)	 // Creates the text representation of a SparseVector and sends it to a std::ostream object.
{
	for(int i=0;i<static_cast<int>(obj.vec.size());i++)
	{
		output<<obj.vec[i].index<<':';
		output<<obj.vec[i].data<<' ';

	}
	return output;
}

SparseVector& SparseVector::operator=(const SparseVector& obj)	 // Assigns one SparseVector to another.
{	
	Vec temp;

	
	for(int i=0;i<static_cast<int>(obj.vec.size());i++)
	{
		temp.index=obj.vec[i].index;
		temp.data=obj.vec[i].data;
		this->vec.push_back(temp);
	}
	return *this;
}

SparseVector SparseVector::operator-()	// Creates another SparseVector object which is element-by-element negative of the operant.
{	
	for(int i=0;i<static_cast<int>(vec.size());i++)
	{	
		this->vec[i].data=-(this->vec[i].data);
	}
	return *this;
}

double dot(const SparseVector& obj2,const SparseVector& obj)	// Calculates the dot product(inner product) of two SparseVectors. Returns a real number.
{
	
	double sum=0;	// Variable that holds the sum of the products of the numbers in the same index.
	SparseVector a; 
	int j=0;
	bool flag=0;

	for(int i=0;i<static_cast<int>(obj2.vec.size());i++)
	{	for(;j<static_cast<int>(obj.vec.size());j++)
		{	if(obj2.vec[i].index==obj.vec[j].index)	// If index values are equal
			{	
				flag=1;
				break;
			}
		}
		
		if(flag==1)
			sum=sum+obj2.vec[i].data*obj.vec[j].data;	// Multiplies numbers in the same directory and adds them to the sum variable.
		flag=0;
	}

	return sum;

}









