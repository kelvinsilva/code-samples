//kelvin silva, March 12, 2013
#include "complexnum.h"



complexnum::complexnum(int a, int b){

    x = a;
    y = b;

}

void complexnum::setx(int a){ x = a; }

void complexnum::sety(int b){ y = b; }


complexnum complexnum::operator+(complexnum& operand){

            complexnum answer(this->x + operand.getx(), this->y + operand.gety());
            return answer;
}

complexnum complexnum::operator*(complexnum& operand){

            complexnum answer((this->x * operand.getx()) - (this->y * operand.gety()), (this->x * operand.gety() - this->y * operand.getx() ));
            return answer;
}

complexnum complexnum::operator-(complexnum& operand){

            complexnum answer(this->x - operand.getx(), this->y - operand.gety());
            return answer;
}

complexnum operator*(int loperand, complexnum operand){

            complexnum answer(operand.getx() * loperand, operand.gety() * loperand);
            return answer;

}

//conjugate of the complex number multiply by negative 1
void complexnum::operator~(){

            this->setx(this->getx());
            this->sety( -1*this->gety());

}

//make it cout able

std::ostream & operator << (std::ostream& outstream,const complexnum& outnum){

        outstream << "( " << outnum.x << ", " << outnum.y << "i)";
        return outstream;

}

//enables you to type things like (-4, 3) as input for the number
//an attempt at parsing

std::istream& operator >> (std::istream& instream, complexnum& outnum){

        char archars[9];
        instream.getline(archars, 8);
        int twonums[2];
        int z = 0;
        for (int i = 0; i <8; i++){

            if (isdigit(archars[i]) || archars[i] == '-'){

                if (archars[i] == '-'){

                    twonums[z] = -1*(archars[++i]-'0');

                z++;
                }else {

                    twonums[z] = archars[i++]-'0';
                    z++;

                }
            }
        }

        outnum.setx(twonums[0]);
        outnum.sety(twonums[1]);

        return instream;


}

complexnum::~complexnum(){

}
