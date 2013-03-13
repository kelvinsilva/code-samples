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

  string str;
  string xval = "", yval = "";
  string::iterator it;
  getline(instream, str);
  int index = 0;

  //remove all whitespaces
  for ( it = str.begin() ; it < str.end(); it++ ){

        if (*it == ' '){
            str.erase(it);
            it--;
        }
  }

  //remove everything trailing (
  for ( it = str.begin() ; it < str.end(); it++ ){

        if(*it == '('){
            break;
        }
        str.erase(it);
        it--;

  }

  //remove everything after )
  for (it = str.end()-1; it > str.begin(); it--){


        if(*it == ')'){
            break;
        }
        str.erase(it);
  }

  //remove the parenthesis
  for ( it = str.begin() ; it < str.end(); it++ ){

       if (*it == '(' || *it == ')'){
        str.erase(it);
        it--;
       }

  }
  for (it = str.begin(); it < str.end(); it++){


      if(*it == ','){

        it++;
        for(; it < str.end(); it++){

            yval+=*it;

        }

      }
      xval += *it;


  }

     int xvalint = atoi(xval.c_str());
     int yvalint = atoi(yval.c_str());


        outnum.setx(xvalint);
        outnum.sety(yvalint);

        return instream;


}

complexnum::~complexnum(){

}
