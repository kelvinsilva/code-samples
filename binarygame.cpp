//By kelvin silva, march 10th 2013

#include <iostream>
#include <limits>


int main(){

        //set namespaces for cout, cin and limits
        using std::cout;
        using std::cin;
        using std::numeric_limits;

            //binary search, from 0-100
            int lowerbound = 0, upperbound = 100;
            int firstguess = (lowerbound + upperbound)/2;

            //input state
            int quit = 0;

            do{

                cout << "Is your number higher or lower than (limit 0-100): " << firstguess << "? (1 lower 2 higher 3 quit):\n";

                //check for cin fail
                if (cin >> quit){

                        //decide if lower or higher
                        switch(quit){

                            case 1: upperbound = firstguess;
                            break;
                            case 2: lowerbound = firstguess;
                            break;
                            case 3: break;
                            default:
                            break;
                        }

                }else {
                    //if cin fails, then clear failbit, and ignore remaining characters in the buffer
                    cin.clear();
                    //numeric limits..
                    cin.ignore(numeric_limits<int>::max(), '\n');

                    cout << "\nError, Enter (1 lower 2 higher 3 quit)\n";
                }
                //reset my bounds
                firstguess = (lowerbound + upperbound)/2;

            }while(quit != 3);

        return 0;
}
