#ifndef _DAY_OF_YEAR_SET_
#define _DAY_OF_YEAR_SET_

#include <string>
#include <vector>
#include <ostream>
using namespace std;


namespace X
{
class DayofYearSet
{
    public:
        class DayofYear
        {
            public:
                DayofYear(int, int);

                bool equal(int, int)const;

                int getDay()const;
                int getMonth()const;
                static int getobjectCount();

                bool setDay(int);
                bool setMonth(int);

                string getString()const;
                ~DayofYear(){objectCount--;}
                
            private:
                int month;
                int day;
                static int objectCount;

                const int MONTH_BOUND = 12;
                const int DAY_BOUND = 31;
                
        };
        
        DayofYearSet();
        DayofYearSet(const DayofYearSet&);
        DayofYearSet(const vector<DayofYear>&);
        
        DayofYearSet& operator=(const DayofYearSet&);

        bool add(int, int);
        bool remove(int, int);
        int contains(int, int)const;

        bool operator==(const DayofYearSet& other)const;
        bool operator!=(const DayofYearSet& other)const;
        const DayofYear& operator[](int)const;
        DayofYear operator[](int );
        friend ostream& operator<<(ostream&, const DayofYearSet&);
        DayofYearSet operator+(const DayofYearSet& other);
        DayofYearSet operator^(const DayofYearSet& other);
        DayofYearSet operator-(const DayofYearSet& other);
        DayofYearSet operator!();

        int getSize()const;
        int getCapacity()const;

        std::string getString()const;
      
        
        ~DayofYearSet();
    private:
        void setSize(int);
        void setCapacity(int);

        DayofYear** arr = nullptr;
        int size;
        int capacity;
};

}
#endif