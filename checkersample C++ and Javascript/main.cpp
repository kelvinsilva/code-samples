//Kelvin Silva
//kelvinsilva747@gmail.com

#define WIN32_LEAN_AND_MEAN
//strip unneeded win32 things

#include <windows.h>
//windowsx.h for the get combobox text
#include <windowsx.h>
//string for easy string formatting and fstream for .txt ouput of html
#include <string>
#include <fstream>
//for atoi
#include <cstdlib>
using std::string;
using std::ofstream;
#include "resource.h"


//We will create a handle and assign it in the main function
HINSTANCE hInst;

//generate the text for html according to what is inputted in the gui
void GenerateText(string, string, int, int, int, int);
//dialog box switch statement so that the program determines what button you pressed
BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);





int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;
    //this is a dialog based program so not much here.



    // The user interface is a modal dialog box
    return DialogBox(hInstance, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DialogProc);
}

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_INITDIALOG:{
                //Two dimensions that i set for the user to choose
                string dimension1 = "4 4";
                string dimension2 = "3 3";

                //SendMessage sends a handle to the Combo box in the GUI, the message is CB_ADDSTRING, and we cast the string to send it as message
                SendMessage(GetDlgItem(hwndDlg, IDC_COMBO1), CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)dimension1.c_str()));
                SendMessage(GetDlgItem(hwndDlg, IDC_COMBO1), CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)dimension2.c_str()));
        }
            /*
             * TODO: Add code to initialize the dialog.
             */
            return TRUE;


        case WM_CLOSE:
        //if x button is pressed, end dialog
            EndDialog(hwndDlg, 0);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {

                 case IDC_RADIO1:{
                    //first radio button choice, not really anything is done here, decision is made when generate is pressed
                 }
                 break;

                 case IDC_RADIO2:{
                    //

                 }break;

                case IDC_BTN_GEN:
                    //when generate button is pressed, make the following string choices according to radio button press
                    string colorchoice1;
                    string colorchoice2;
                    if (BST_CHECKED == IsDlgButtonChecked(hwndDlg, IDC_RADIO1)){

                        colorchoice1 = "#FF0000";
                        colorchoice2 = "#00FF00";

                    }else if (BST_CHECKED == IsDlgButtonChecked(hwndDlg, IDC_RADIO2)){

                        colorchoice1 = "#FFFF00";
                        colorchoice2 = "#0000FF";

                    }
                    //get lengths for each char* buffer so we know how much memory to allocate
                    int len = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_WIDTH));
                    int len2 = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_HEIGHT));
                    char* bufheight = (char*)GlobalAlloc(GPTR, len+1);
                    char* bufwidth = (char*)GlobalAlloc(GPTR, len+1);
                    char* bufstrcmb = (char*)GlobalAlloc(GPTR, 4);

                //Get combobox text and 2 textboxes text, bufferheight, bufferwidth, bufferstrcombo
                    ComboBox_GetText(GetDlgItem(hwndDlg, IDC_COMBO1), bufstrcmb, 4);
                    GetDlgItemText(hwndDlg, IDC_HEIGHT, bufheight, len + 1);
                    GetDlgItemText(hwndDlg, IDC_WIDTH, bufwidth, len2 + 1);

                //convertchar numbers
                //use atoi to convert char* buffermemory to an int
                    int height = atoi(bufheight);
                    int width = atoi(bufwidth);

                    //to make things easier on myself i decided to convert all my c style strings into c++ string objects
                    string buffstring(bufstrcmb);

                    //some string manipulation to split the 4 4 or 3 3 in half to get the length and width parameters of the checker board
                    string xz = buffstring.substr(0,1);
                    int xsiz = atoi(xz.c_str());
                    //converting each substringed string into an int
                    string y = buffstring.substr(2,3);
                    int ysiz = atoi(y.c_str());

                    //in final we have the following variables to pass to the textgenerator:
                    /*
                    int xsiz
                    iny ysiz
                    int height
                    int width
                    string colorchoice1
                    string colorchoice2
                    */


                //free dynamic memory
                    GlobalFree((HANDLE)bufheight);
                    GlobalFree((HANDLE)bufwidth);
                    GlobalFree((HANDLE)bufstrcmb);

                    //passing the two color choices for alternating checkers, height and width is the dimension of each checker square
                    //xsiz and y siz is the dimension of the board in whole
                    GenerateText(colorchoice1, colorchoice2, height, width, xsiz, ysiz);

                return TRUE;
            }
    }

    return FALSE;
}

void GenerateText(string color1, string color2,  int heightsq, int widthsq, int W, int H){

    ofstream checkerfile;
    checkerfile.open("checkerfile.txt");

    //Declare document type and append html and body headers

    checkerfile << "<!DOCTYPE html>\n<html>\n\t<body>";
    //initial script for the names and start button
    checkerfile <<"\n\t\t<script>";
    checkerfile << "\n\n\n\t\t\tfunction startbtn(){";
    checkerfile << "\n\t\t\t\tvar pinput = document.getElementById(\"player1\").value;";
    checkerfile << "\n\t\t\t\tvar pinput2 = document.getElementById(\"player2\").value;";
    checkerfile << "\n\t\t\t\tvar color1 = \"<font color = \\\"" << color1 << "\\\">\" + pinput + \"</font>\";";
    checkerfile << "\n\t\t\t\tvar color2 = \"<font color = \\\"" << color2 << "\\\">\" + pinput2 + \"</font>\";";
    //when startbutton is clicked, change innerHTML to the 2 players names combination
    checkerfile << "\n\t\t\t\tdocument.getElementById(\"p1\").innerHTML = color1 + \"---\" + color2;";
    checkerfile << "\n\t\t\t}";
    checkerfile << "\n\t\t</script>";
    //Write the players name on the html page along with submit data form
    checkerfile << "\n\t\t<div align = \"middle\">\n\t\t\t";
    checkerfile << "<form>\n\t\t\tPlayer 1:<input type =\"text\" id = \"player1\">";
    checkerfile << "\n\t\t\tPlayer 2: <input type = \"text\" id = \"player2\">";
    checkerfile << "\n\t\t\t\t<input type = \"button\" onclick = \"startbtn()\" value = \"START\"/>";
    checkerfile << "\n\t\t\t</form>\n\t\t\t<p id = \"p1\">PLAYER1 --- PLAYER2</p>";
    checkerfile << "\n\t\t</div>";

    //start checkerboard script, note that the player names and start button are on a different divider than the checkerboard script
    checkerfile << "\n\n\n\t\t<div align = \"middle\">";
    checkerfile << "\n\n\t\t<br>";
    checkerfile << "\n\n\t\t<script>\n\t\t\t";




//my first function here is settoggle() once the amount of grids has been created, I gather the index of each grid and assign a value of 0
//i then assign each grid the value 1 or 0 respectively.
//for example, 1 fact that is known, is that all the checkerboards are empty at runtime, this means that all indexes can be set to 0 without question
//Any grid that is clicked calls the settoggle function, since the user clicks a grid for the first time, we are putting in a checker and setting
//this grid's index to 1, the next click on the same checker will call the same settoggle function, but notice the if statement checking if it has already been pressed once
//it alternates between these two thought processes
    checkerfile << "\n\n\n\t\t\tfunction settoggle(id){\n\n\t\t\t\tif(checkertoggle[id.substring(7)] == 0){\n";
    checkerfile << "\t\t\t\t\tcheckerplace(id);\n\n\t\t\t\tcheckertoggle[id.substring(7)] = 1;\n\t\t\t}else{\n";
    checkerfile << "\t\t\t\t\t\tcheckerdelete(id);\n\n\t\t\t\t\tcheckertoggle[id.substring(7)] = 0;\n\t\t\t\t}\n\t\t\t}";
//\t is to make a tab in output stream, \n a newline, and \\\" is the equivalent of writing \" to the output, \" is a quotation
//fill a circle with radius half of the square checker grid size, that way the circle can scale with the checker grid size.
//a black circle is a checker
    checkerfile << "\n\n\n\t\t\tfunction checkerplace(id){\n\t\t\t\t";
    checkerfile << "var canv = document.getElementById(id);";
    checkerfile << "\n\t\t var ctx = canv.getContext(\"2d\");";
    checkerfile << "\n\t\t\t\tctx.fillStyle = \"#000000\";";
    checkerfile << "\n\t\t\t\tctx.beginPath();\n\t\t\t\tctx.arc(" << heightsq/2 << ", " << widthsq/2 << ", " << heightsq/3 << ", 0, Math.PI*2); \n\t\t\t\tctx.fill();\n\t\t\t}";

//When creating the grid, each checker grid canvas is either an even or odd, i choose 1 color to start out as evens and another as odds,
//this is how i know what each color is since it is only alternating by 2
    checkerfile << "\n\n\n\n\t\t\tfunction checkerdelete(id){\n\t\t\t\t";
    checkerfile << "var canv = document.getElementById(id);";
    checkerfile << "\n\t\t var ctx = canv.getContext(\"2d\");";
    checkerfile << "\n\n\t\t\t\tif (id.substring(7) % 2 == 0){\n\t\t\t\t\t";
    checkerfile << "ctx.fillStyle = \"" << color1 << "\";\n\n\t\t\t\t\t";
    checkerfile << "}else ctx.fillStyle = \"" << color2 << "\";\n\t\t\t\t\tctx.fillRect(0, 0, " << widthsq << ", " << heightsq << " );\n\t\t\t}";

//use a loop to write multiple canvases as chosen by the user in the keygen
//at every 4th square, do a break and start a new row
//to make naming and calling of each element easier, decided to name the canvas: canvas_INT
//that way a loop can easily cycle through the name without any substring or any other sort of trick
    checkerfile << "\n\n\t\t\tvar count = 0;";
    checkerfile << "\n\n\t\t\tdocument.write(\"<br>\");";
    checkerfile << "\n\n\t\t\twhile(count<16){";
    checkerfile << "\n\t\t\t\t\tdocument.write(\"<canvas id = \\\"canvas_\" + count + \"\\\" width = \\\""<< widthsq << "\\\" height = \\\" " << heightsq << "\\\"></canvas>\");";
    checkerfile << "count++;";
    checkerfile << "\n\t\t\t\tif (count % "<< W << "  == 0){\n";
    checkerfile << "document.write(\"<br>\");";
    checkerfile << "\n\n\t\t\t}}";
//fill in each canvas with alternating colors to the height and width specification of user
    checkerfile << "\n\n\n\t\t\tvar count = 0;\n\t\t\twhile(count < " << W*H <<"){\n\n\t\t\tvar name = \"canvas_\" + count;";
    checkerfile << "\n\t\t\t\tvar canv = document.getElementById(name);\n\t\t\t\t\tvar ctx = canv.getContext(\"2d\");";
    checkerfile << "\n\t\t\t\tif (count % 2 == 0){\n";
    checkerfile << "\n\t\t\t\tctx.fillStyle = \"" << color1 << "\";\n\n\t\t\t\t}";
    checkerfile << "else{\n\t\t\t\tctx.fillStyle = \"" << color2 << "\";\n\t\t\t\t}";
    checkerfile << "\n\t\t\t\tctx.fillRect(0,0,"<< heightsq << " ," << widthsq << ");\n\t\t\t\tcount++;\n\t\t\t\t}";

//compile an array of checkers for settoggle function, equivalent to something like the following:
//make an array of integers the same number or canvases made
    checkerfile << "\n\n\t\t\tvar checkertoggle = new Array(count);";
    checkerfile << "\n\t\t\tfor (var counter = 0; counter < count; counter++){\n";
    checkerfile << "\t\t\t\tcheckertoggle[counter] = 0;\n\t\t\t}";

//generate each onclick anonymous function, canvas_ count++
    for(int i = 0; i < (W * H); i++){

        checkerfile << "\n\n\t\t\tcanvas_" << i << ".onclick = function(){\n";
        checkerfile << "\n\t\t\t\tsettoggle(this.id);\n\t\t\t}";

    }
//close our output stream and complete each header
    checkerfile << "\n\t\t</script>\n\t</div>\n</body>\n</html>";
    checkerfile.close();

}
