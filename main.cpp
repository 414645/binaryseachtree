#include <iostream>

#include "node.h"


using namespace std;

//by ryan veith
//binary search tree
//should be able to add, remove and print in any order
//nodes can have anything from 1 to 999
//seperate inputs with spaces (cin?)

void print(Node* root);
void add(Node* &root, int thing); //add int to thing
void remove(Node* &root, int thing); //three cases here (one is root)
bool search(Node* root, int thing); //possibly retruns

int main() {
  cout << "hello world" << endl;
  bool quit = false;
  char input[80];
  Node* root = NULL;
  //main loop of program for user input
  while(quit == false) {
    //ask user input
    cin.getline(input, 80);
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
    if (strcmp(input, "HELP") == 0) {
      cout << "Commands are:" << endl;
      cout << "PRINT" << endl;
      cout << "ADD" << endl;
      cout << "REMOVE" << endl;
      cout << "SEARCH" << endl;
      cout << "QUIT" << endl;
    }
    if (strcmp(input, "PRINT") == 0) {
      cout << "PRINT" << endl;
    }
    if (strcmp(input, "REMOVE") == 0) {
      cout << "rm" << endl;
    }
    if (strcmp(input, "SEARCH") == 0) {
      cout << "s" << endl;
    }
    if (strcmp(input, "ADD") == 0) {
      cout << "add" << endl;
    }
  }
}

void print(Node* root) {

}

void add(Node* &root, int thing) {
  //add int to thing
  if(root == NULL) {
    Node* newNode = new Node(thing);
  }
  
  
}
void remove(Node* &root, int thing) {
  //three cases here (one is root)
  
  
}
bool search(Node* root, int thing) {
  //possibly retruns

  return false;
}
