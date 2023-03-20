#include <iostream>

#include "node.h"


using namespace std;

//by ryan veith
//binary search tree
//should be able to add, remove and print in any order
//nodes can have anything from 1 to 999
//seperate inputs with spaces (cin?)

void print(Node* current, int tab);

void add(Node* &root, Node* current, Node* previous, int thing);
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
      print(root, 0);
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
      char input;
      cout << "Would you like to add from a file (1) ";
      cout << "or the console (2)?" << endl;
      cin >> input;
      if (input == '1') {
	//file handeling
      }
      else if (input == '2') {
	cout << "Enter numbers seperated by spaces" << endl;
	//input handling
	//exept I don't want to for 3 digit numbers
	//I coudl char 1 * 100 + char 2 * 10 + char 3 but
	/*
	bool loop = true;
	while(loop) {
	  cin >> input;
	  if ((int)input > 47  && (int)input < 58) {
	    cout << input << endl;
	  }
	  else {
	    loop = false;
	  }
	}
	*/
	int thing;
	for(int a = 0; a < 5; a++) {
	  cin >> thing;
	  add(root, root, NULL, thing);
	}
      }
    }
  }
}

//a fun program I made back in hashtable simplified for a tree
void print(Node* current, int tab) {
  if (current != NULL) {
    //cout << "print: " << current->getNumber() << endl;
    //call print on left node
    print(current->getLeft(), tab + 1);
    //print myself with correct tab number
    for (int a = 0; a < tab; a++) {
      cout << "    ";
    }
    cout << current->getNumber() << endl;
    //call print on right node
    print(current->getRight(), tab + 1);
  }
}

//I don't think I will ever need to use previous but lazy
void add(Node* &root, Node* current, Node* previous, int thing) {
  //do we need to replace head?
  if(root == NULL) {
    Node* newNode = new Node(thing);
    root = newNode;
  }
  else if(current == NULL) {
    cout << "something went wrong" << endl;
  }
  ///if bigger go right
  else if (current->getNumber() > thing) {
    if (current->getRight() != NULL) {
      //go there
      add(root, current->getRight(), current, thing);
    }
    else {
      //add me there
      Node* newNode = new Node(thing);
      current->setRight(newNode);
    }
  }
  //if we are smaller go left
  else if (current->getNumber() < thing) {
    if (current->getLeft() != NULL) {
      //go there
      add(root, current->getLeft(), current, thing);
    }
    else {
      //add me there
      Node* newNode = new Node(thing);
      current->setLeft(newNode);
    }
  }
  else {
    cout << "Um..." << endl;
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
