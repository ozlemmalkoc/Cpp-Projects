
#include <vector>
#include <ostream>
#include <iostream>
#include <string>
#include "DayofYearSet.h"

using namespace std;
namespace X{

DayofYearSet::DayofYearSet()
{
    setSize(0);
    setCapacity(1);
    
    arr = new DayofYear*[getCapacity()];
}

DayofYearSet::DayofYearSet(const DayofYearSet& other)
{
    setSize(other.getSize());
    setCapacity(other.getCapacity());

    arr = new DayofYear*[getCapacity()];

    for(int i=0 ; i < getSize() ; ++i)
        arr[i] = new DayofYear(other.arr[i]->getMonth(), other.arr[i]->getDay());
}

DayofYearSet::DayofYearSet(const std::vector<DayofYearSet::DayofYear>& other){
    
    setSize(other.size());
    setCapacity(other.capacity());

    arr = new DayofYear*[getCapacity()];

    for(int i=0 ; i < getSize() ; ++i)
        arr[i] = new DayofYear(other.at(i).getMonth(), other.at(i).getDay());
    
}

DayofYearSet& DayofYearSet::operator=(const DayofYearSet& rightSide)
{
    if(this != &rightSide)
    {
        for(int i=0 ; i < getSize() ; ++i)
            delete arr[i];
        delete[] arr;

        setSize(rightSide.getSize());
        setCapacity(rightSide.getCapacity());

        arr = new DayofYear*[getCapacity()];

        for(int i=0 ; i < getSize() ; ++i)
            arr[i] = new DayofYear(rightSide.arr[i]->getMonth(), rightSide.arr[i]->getDay());
    }

    return *this;
}

bool DayofYearSet::operator==(const DayofYearSet& other)const{
        
        for(int i=0 ; i < getSize() ; ++i)
        {
            if(arr[i]->getMonth() != other.arr[i]->getMonth() || arr[i]->getDay() != other.arr[i]->getDay())
                return 0;
        }
        return 1;

}

bool DayofYearSet::operator!=(const DayofYearSet& other)const{
        
        for(int i=0 ; i < getSize() ; ++i)
        {
            if(arr[i]->getMonth() != other.arr[i]->getMonth() || arr[i]->getDay() != other.arr[i]->getDay())
                return 1;
        }
        return 0;
}

/*
const DayofYearSet::DayofYear& DayofYearSet::operator[](int i)const{
    
    if(i>getSize())
       return *arr[0];

    return *arr[i];
}

 DayofYearSet::DayofYear& DayofYearSet::operator[](int i){
   
    if(i>getSize())
        return *arr[0];

     return *arr[i];
}
*/

DayofYearSet DayofYearSet::operator+(const DayofYearSet& other){
    
    DayofYearSet* d = new DayofYearSet();

    for(int i=0; i<other.getSize();i++)
        d->add(other.arr[i]->getMonth(),other.arr[i]->getDay());
                 
    for(int i=0; i<getSize(); i++){
        for(int j=0; j<other.getSize(); j++){
            if(other.arr[j]->equal(arr[i]->getMonth(),arr[i]->getDay())){
                break;
            }
            if(j = other.getSize()-1){
                d->add(arr[i]->getMonth(),arr[i]->getDay());
            }  
        }  
    }
    return *d;
}

ostream& operator<<(ostream& os, const DayofYearSet& object){
    
    string s;

    for(int i=0 ; i < object.getSize() ; ++i){
        os << "Month=>" << object.arr[i]->getMonth() << "  Day=>" << object.arr[i]->getDay() <<endl;
    }

    return os;
}

DayofYearSet DayofYearSet::operator^(const DayofYearSet& other){
   
    DayofYearSet* d = new DayofYearSet();

    for(int i=0; i<getSize(); i++){
        for(int j=0; j<other.getSize(); j++){
            if(other.arr[j]->equal(arr[i]->getMonth(),arr[i]->getDay())){
                d->add(arr[i]->getMonth(),arr[i]->getDay());
            }
        }  
    }
    return *d;
}


DayofYearSet DayofYearSet::operator-(const DayofYearSet& other){
    
    DayofYearSet* d = new DayofYearSet();

    for(int i=0; i<getSize(); i++){
        for(int j=0; j<other.getSize(); j++){
            if(other.arr[j]->equal(arr[i]->getMonth(),arr[i]->getDay())){
                break;
            }
            if(j == other.getSize()-1){
                d->add(arr[i]->getMonth(),arr[i]->getDay());    
            }
            
        }
    }
    for(int i=0; i<other.getSize(); i++){
        for(int j=0; j<getSize(); j++){
            if(arr[j]->equal(other.arr[i]->getMonth(),other.arr[i]->getDay())){
                break;
            }
            if(j == getSize()-1){
                d->add(other.arr[i]->getMonth(),other.arr[i]->getDay());    
            }
            
        }
    }
    return *d;
}

DayofYearSet DayofYearSet::operator!()
{   
    DayofYearSet* d = new DayofYearSet();
    int flag=0;

    for(int i=1;i<=12;i++)
    {   for(decltype(i) j=1;j<=31;j++)
        { 
         flag=0;
         if(  (i==4 || i==6 || i==9 || i==11) && j>30) break;

         else if(i==2 &&  j>28) break;

         else{   
                for(int k=0;k<getSize();k++)
                {
                    if(arr[k]->equal(i,j))
                        flag=1;
                }
                if(flag==0)

                {d->add(i,j);}
            }
       
        }
    }
    return *d;
}

DayofYearSet::~DayofYearSet()
{
    for(int i=0 ; i < getSize() ; ++i)
        delete arr[i];
        
     delete[] arr;
}

bool DayofYearSet::add(int month, int day)
{
    if(contains(month, day) != -1)
        return false;

    DayofYear* d = new DayofYear(month, day);

    if(size >= capacity)
    {
        setCapacity(getCapacity() * 2);

        DayofYear** a = new DayofYear*[getCapacity()];

        for(int i=0 ;  i < getSize() ; ++i)
            a[i] = arr[i];

        delete[] arr;
        arr = a;
    }

    arr[getSize()] = d;
    setSize(getSize() + 1);

    return true;
}

bool DayofYearSet::remove(int month, int day)
{
    int index;

    if((index = contains(month, day)) == -1)
        return false;

    DayofYear* temp = arr[index];

    for(auto i = index ; i < getSize() - 1 ; ++i)
        arr[i] = arr[i+1];
    
    setSize(getSize() - 1);
    
    delete temp;
    return true;
}

int DayofYearSet::contains(int month, int day)const
{
    for(int i=0 ; i < getSize() ; ++i)
        if(arr[i]->equal(month, day))
            return i;
    return -1;
}

int DayofYearSet::getSize()const { return size; }

int DayofYearSet::getCapacity()const { return capacity; }

void DayofYearSet::setSize(int size) { this->size = size; }

void DayofYearSet::setCapacity(int capacity) { this->capacity = capacity; }

std::string DayofYearSet::getString()const
{
    std::string s;

    for(int i=0 ; i < getSize() ; ++i)
        s.append(arr[i]->getString()).append("\n");

    s.append("Size: ").append(std::to_string(getSize())).append("\n");
    s.append("Capacity: ").append(std::to_string(getCapacity())).append("\n");
    return s;
}

DayofYearSet::DayofYear::DayofYear(int month, int day)
{
    setMonth(month);
    setDay(day);
    objectCount++;
}

bool DayofYearSet::DayofYear::equal(int month, int day)const { return getMonth() == month && getDay() == day; }

int DayofYearSet::DayofYear::getDay()const { return day; }

int DayofYearSet::DayofYear::getMonth()const { return month; }

int DayofYearSet::DayofYear::getobjectCount() { return objectCount; }

bool DayofYearSet::DayofYear::setDay(int day)
{
    if(day <= 0 || day > DAY_BOUND)
    {
        this->day = 1;
        return false;
    }

    this->day = day;
    return true;
}

bool DayofYearSet::DayofYear::setMonth(int month)
{
    if(month <= 0 || month > MONTH_BOUND)
    {
        this->month = 1;
        return false;
    }

    this->month = month;
    return true;
}

string DayofYearSet::DayofYear::getString()const
{
    string s;

    s.append("Month ").append(std::to_string(getMonth())).append(", Day ").append(std::to_string(getDay()));
    return s;
}

}
