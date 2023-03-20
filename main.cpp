#include <iostream>

#include "node.h"


using namespace std;

//by ryan veith
//binary search tree
//should be able to add, remove and print in any order
//nodes can have anything from 1 to 999
//seperate inputs with spaces (cin?)

//void print();
//void addConsole(); //console
//void addFile(); //file
//void remove(); //three cases here (one is root)
//posibly a balance funcion?

int main() {
  cout << "hello world" << endl;
  bool quit = false;
  char input[80];
  //main loop of program for user input
  while(quit == false) {
    //ask user input
    cin.getline(input, 80);
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
    if (strcmp(input, "HELP") == 0) {
      cout << "helptext" << endl;
    }
    if (strcmp(input, "PRINT") == 0) {
      cout << "PRINT" << endl;
    }
    if (strcmp(input, "REMOVE") == 0) {
      cout << "rm" << endl;
    }
    if (strcmp(input, "ADD") == 0) {
      cout << "add" << endl;
    }
  }
}
