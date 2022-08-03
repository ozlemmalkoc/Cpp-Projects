#include <iostream>
#include <vector>
#include "DayofYearSet.h"

using namespace std;
using namespace X;

int DayofYearSet::DayofYear::objectCount=0;

int main(void)
{
    vector<DayofYearSet::DayofYear> v;
    v.push_back((DayofYearSet::DayofYear(5,10)));
    v.push_back((DayofYearSet::DayofYear(3,10)));
    v.push_back((DayofYearSet::DayofYear(4,10)));
    v.push_back((DayofYearSet::DayofYear(7,10)));
    v.push_back((DayofYearSet::DayofYear(8,11)));

   
    vector<DayofYearSet::DayofYear> c;
    c.push_back((DayofYearSet::DayofYear(6,10)));
    c.push_back((DayofYearSet::DayofYear(3,10)));
    c.push_back((DayofYearSet::DayofYear(4,10)));
    c.push_back((DayofYearSet::DayofYear(8,11)));
    c.push_back((DayofYearSet::DayofYear(9,12)));
   
    DayofYearSet* d = new DayofYearSet(v);
    DayofYearSet* k = new DayofYearSet(c);
 
    cout<<"<< Operator"<<endl;
    cout << *d<<endl<<endl;// << operator

    cout<<"== Operator"<<endl;
    if(*d == *d)    //  == operator
    cout<<"objects are same"<<endl<<endl;
   
    cout<<"+ Operator"<<endl;
    cout << (*d + *k)<<endl<<endl; // + operator

    cout<<"- Operator"<<endl;
    cout<< (*d - *k)<<endl<<endl;   // - operator

    cout<<"Add operation"<<endl;
    d->add(3,8);   // add 
    cout<< *d<<endl<<endl;

    cout<<"!= Operator"<<endl;
    if(*d != *k)    // != operator
    cout<<"objects are different"<<endl<<endl;

    cout<<"Remove Operation"<<endl;
    d->remove(3,8);    // remove
    cout<< *d<<endl<<endl;

    cout<<"Size : "<<d->getSize()<<endl<<endl;

    cout<<"^ Operator"<<endl;
    cout<< (*d ^ *k)<<endl<<endl;

    cout<<"!  Operator"<<endl;
    //cout<<!*d<<endl<<endl;
    cout<<endl;

    cout<<"!(s1+s2) ==  !s1 ^ !s2   "<<endl;
    if(!((*d)+(*k)) == (!(*d) ^ !(*k)))
    cout<<"expression is succesfull!!!"<<endl<<endl;

   


        
    
    return 0;
}