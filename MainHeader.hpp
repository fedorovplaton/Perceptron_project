#ifndef HEADER_HPP
#define HEADER_HPP


#include "Rum.hpp"
//#include "Roz.hpp"

/* 

Type of data - "perceptron" with 2 types of contructor 
1)with the argument like as nameoffile in the same directory of program
_____________________________
Methods:
_____________________________
Save(const char* name)/ name is full name of file, just name without type (right : "name", uncorrect "name.txt")
_____________________________
Study(const char *name, int number) "name" is a name of the file with right input and output data for studying, n - is number which
shows how many examples will be use;
_____________________________
Show(_name) - program will create a file with name - "_name.tex" and then create the pdf file with the same name.
_____________________________
Set(double) - set the speed of studing;
_____________________________
NUMBERS OF STANDART FUNCTIONS:
1)1 - Exp function ( 1/(1 + e^(-x)) ) 
2)2 - Sign function (1, x > 0; 0, x = 0; -1, x < 0 ) 
3)3 - Oneorzerofunction ( 1, x >= 1; 0, x < 1 )
4)4 - Arctg ( arctg(x) )
*/

#endif