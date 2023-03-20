#include <iostream>

#include "node.h"


using namespace std;

//by ryan veith
//binary search tree
//should be able to add, remove and print in any order
//nodes can have anything from 1 to 999
//seperate inputs with spaces (cin?)

void print(Node* root);

void add(Node* root, int thing);
//add int to thing

void remove(Node* root, Node* previous,int thing);
//three cases here (one is root)

bool search(Node* root, int thing);
//possibly retruns

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
      print(root);
    }
    if (strcmp(input, "REMOVE") == 0) {
      cout << "rm" << endl;
      int thing;
      cout << "what number would you like to remove?" << endl;
      cin >> thing;
      remove(root, NULL, thing);
    }
    if (strcmp(input, "SEARCH") == 0) {
      cout << "s" << endl;
      int thing;
      cout << "what number would you like to searfch for?" << endl;
      cin >> thing;
      if (search(root, thing) == true) {
	cout << "found it" << endl;
      }
    }
    if (strcmp(input, "ADD") == 0) {
      cout << "add" << endl;
      //file vs console
      int thing = 1;
      add(root, thing);
    }
  }
}

void print(Node* root) {

}

void add(Node* root, int thing) {
  //add int to thing
  if(root == NULL) {
    Node* newNode = new Node(thing);
    root = newNode;
  }
  else if (root->getNumber() > thing) {
    add(root->getRight(), thing);
  }
  else {
    add(root->getLeft(), thing);
  }
}
void remove(Node* root, Node* previous, int thing) {
  //three cases here (one is root)
  if(root == NULL) {
    cout << "failure " << endl;
  }
  else if (root->getNumber() == thing) {
    cout << thing << endl;
    //remove current thing
    //if ...
    
    
  }
  else if (root->getNumber() > thing) {
    //remove(root->getRight());
  }
  else {
    //remove(root->getLeft());
  }
  
}
bool search(Node* root, int thing) {
  //possibly retruns

  return false;
}
