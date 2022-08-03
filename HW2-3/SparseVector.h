#ifndef SPARSEVECTOR_H_
#define SPARSEVECTOR_H_

#include <vector>
#include <ostream>

using namespace std;

struct Vec
{
	int index;	
	double data;
};

class SparseVector
{
	public:
		
		SparseVector(){};	// Constructor
		SparseVector(string );	// A constructor which takes a string filenamedata, opens the file, reads the contents, creates and populates an object.
		SparseVector operator+(const SparseVector & )const;	// Adds two SparseVectors. Creates another SparseVector object.
		SparseVector operator-(const SparseVector & )const;	// Subtracts one SparseVector from another. Creates another SparseVector object.
		friend ostream & operator<<(ostream& output,const SparseVector & );	// Creates the text representation of a SparseVector and sends it to a std::ostream object.
		SparseVector& operator=(const SparseVector& );	// Assigns one SparseVector to another.
		SparseVector operator-();	// Creates another SparseVector object which is element-by-element negative of the operant.
		friend double dot(const SparseVector&,const SparseVector&);	//  Calculates the dot product(inner product) of two SparseVectors. Returns a real number.

	private:
		vector<Vec> vec;
		
};

#endif
