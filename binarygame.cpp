#include <iostream>
#include <cstdlib>
#include <ctime> //you need this to declare time
#include <limits>



int main(){

        using std::cout;
        using std::cin;
        using std::numeric_limits;

        srand ((unsigned)time(0));

            int lowerbound = 0, upperbound = 100;
            int firstguess = (lowerbound + upperbound)/2;


            int quit = 0;

            do{

                cout << "Is your number higher or lower than " << firstguess << "? (1 lower 2 higher 3 quit):\n";

                if (cin >> quit){
                    
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

                    cin.clear();
                    cin.ignore(numeric_limits<int>::max(), '\n');

                    cout << "\nError, Enter (1 lower 2 higher 3 quit)\n";
                }

                firstguess = (lowerbound + upperbound)/2;

            }while(quit != 3);

        return 0;
}
