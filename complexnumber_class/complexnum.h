//kelvin silva march 12 2013
#ifndef COMPLEXNUM_H_INCLUDED
#define COMPLEXNUM_H_INCLUDED

#include <iostream>
#include <cctype>

using std::string;
using std::stringstream;


    class complexnum {

        private:
            int x, y;

        public:
            int getx(){ return x ;};
            int gety(){ return y; };
                complexnum(int, int);
                ~complexnum();
            void setx(int a);
            void sety(int b);


            complexnum operator+(complexnum& );
            complexnum operator-(complexnum& );
            complexnum operator*(complexnum& );
            friend complexnum operator*(int, complexnum&);
            friend std::ostream& operator<<(std::ostream& os, const complexnum&);
            friend std::istream& operator>>(std::istream& os, complexnum&);

            void operator~();


};
#endif // COMPLEXNUM_H_INCLUDED
