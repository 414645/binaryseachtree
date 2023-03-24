#include <iostream>

#include <cstring>
#include <fstream>

#include "node.h"


using namespace std;

//by ryan veith
//binary search tree
//should be able to add, remove and print in any order
//nodes can have anything from 1 to 999
//seperate inputs with spaces for add by file

void print(Node* current, int tab);
//print out the tree in a way that lets you see children

void add(Node* &root, Node* current, Node* previous, int thing);
//add thing to the binary tree

void remove(Node* &root, Node* current, Node* previous,int thing);
//three cases here (one is two children, one is one child, one is none)
//also I am handeling root differntlu since pas by refferece

bool search(Node* current, int thing);
//ture is found it, false is not found

int main() {
  //cout << "hello world" << endl;
  cout << "Type HELP for a list of commands" << endl;
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
      cout << "Binary Search Tree:" << endl;
      print(root, 0);
    }
    if (strcmp(input, "REMOVE") == 0) {
      int thing;
      cout << "what number would you like to remove?" << endl;
      cin >> thing;
      remove(root, root,  NULL, thing);
    }
    if (strcmp(input, "SEARCH") == 0) {
      int thing;
      cout << "what number would you like to searfch for?" << endl;
      cin >> thing;
      if (search(root, thing) == true) {
	cout << thing << " is in the tree" << endl;
      }
      else {
	cout << thing << " is not in the tree" << endl;
      }
    }
    if (strcmp(input, "ADD") == 0) {
      //file vs console
      char input;
      cout << "Would you like to add from a file (1) ";
      cout << "or the console (2)?" << endl;
      cin >> input;
      if (input == '1') {
	//file handeling
	cout << "What is the name of the file?" << endl;
        char word[80];
	cin >> word;
	//open file and go though it
	ifstream myFile (word);
	if (myFile.is_open()) {
	  //while so keep going until hit end
	  bool notQuit = true;
	  while (notQuit) {
	    //cin number
	    int t = -1;
	    myFile >> t;
	    //cout << "t: " << t << endl;
	    //file will stop overriding once it hits the end
	    if (t >= 0) {
	      //add it
	      add(root, root, NULL, t);
	    }
	    else {
	      notQuit = false;;
	    }
	  }
	}
	else {
	  cout << "something went worng, ";
	  cout << "please check your spelling of the file name" << endl;
	}
	myFile.close();
	cout << "done" << endl;;
      }
      else if (input == '2') {
	cout << "Enter numbers seperated by spaces" << endl;
	//input handling
	//exept I don't want to for 3 digit numbers
	//do singe input at a time for now
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
	//for(int a = 0; a < 5; a++) {
	  cin >> thing;
	  add(root, root, NULL, thing);
	  //}
      }
    }
  }
}

//a fun program I made back in hashtable simplified for a binary tree
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

//I don't think I will ever need to use previous
//but easy to have for if needed
void add(Node* &root, Node* current, Node* previous, int thing) {
  //first check if it is a legal int to add
  //(does it appear in the tree aready)
  if (search(root, thing) == true) {
    cout << thing << " is aready in the tree" << endl;
    cout << "You may not add duplicate numbers to the tree" << endl;
    return;
  }

  //Do the add fuction
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
    //duplicats are not allowed
    cout << "Um..." << endl;
  }
}
void remove(Node* &root, Node* current, Node* previous, int thing) {
  if (previous != NULL) {
    //I just want to know if this was left or right node of previous
    //this is not very useful but...
    bool right = true;
    if (previous->getNumber() > thing) {
      right = true;
    }
    else {
      right = false;
    }
  }
      
  //three cases here (one is root)
  //kindof, I am also treating head = null as seperate since by reference
  if(current == NULL) {
    cout << "Nothing to remove " << endl;
  }
  else if(root->getNumber() == thing) {
    //remove current, current = root

    //if this is the only thing in the tree
    if(current->getRight() == NULL && current->getLeft() == NULL) {
      //just delete this one
      root = NULL;
      delete current;
    }

    //if there is one node
    //it becomes root
    else if(current->getRight() != NULL && current->getLeft() == NULL) {
      root = current->getRight();
      delete current;
    }
    //if there is one node (otherside)
    else if(current->getLeft() != NULL  && current->getRight() == NULL) {
      root = current->getLeft();
      delete current;
    }
    
    else if(current->getLeft() != NULL  && current->getRight() != NULL) {
      //two chidren
      //go right once, then left untill getLeft() = NULL
      //delete that one
      //then replace me with them
      Node* temp = current->getRight();
      while (temp->getLeft() != NULL) {
	temp = temp->getLeft();
      }
      int replace = temp->getNumber();
      remove(root, root, NULL, replace);
      current->setNumber(replace);
      
    }
  }
  else if (current->getNumber() == thing) {
    //remove current thing somehow

    //if this is the end (leaf)
    if(current->getRight() == NULL && current->getLeft() == NULL) {
      //just delete this one
      if (previous->getNumber() > thing) {
	//right
	previous->setRight(NULL);
      }
      else {
	//left
	previous->setLeft(NULL);
      }
      delete current;
    }

    //if there is one node
    //we move the that one up
    //it will work because of how they were added
    else if(current->getRight() != NULL && current->getLeft() == NULL) {
      if (previous->getNumber() > thing) {
	//right
	previous->setRight(current->getRight());
      }
      else {
	//left
	previous->setLeft(current->getRight());
      }
    }
    //if there is one node (otherside)
    else if(current->getLeft() != NULL  && current->getRight() == NULL) {
      if (previous->getNumber() > thing) {
	//right
	previous->setRight(current->getLeft());
      }
      else {
	//left
	previous->setLeft(current->getLeft());
      }
    }

    else if(current->getLeft() != NULL  && current->getRight() != NULL) {
      //two chidren
      //go right once, then left untill getLeft() = NULL
      //delete that one
      //then replace me with them
      Node* temp = current->getRight();
      while (temp->getLeft() != NULL) {
	temp = temp->getLeft();
      }
      int replace = temp->getNumber();
      remove(root, root, NULL, replace);
      //cout << "done" << endl;
      current->setNumber(replace);
      
    }
    else {
      cout << "We can't remove that" << endl;
    }
    
  }
  //this is not the thing to delete so go find that thing
  else if (current->getNumber() > thing) {
    //cout << "right" << endl;
    remove(root, current->getRight(), current, thing);
  }
  else {
    //cout << "left" << endl;
    remove(root, current->getLeft(), current, thing);
  }
  
}
bool search(Node* current, int thing) {
  //possibly retruns
  if (current == NULL) {
    return false;
  }
  else if(current->getNumber() == thing) {
    return true;
  }
  else {
    bool a = search(current->getRight(), thing);
    bool b = search(current->getLeft(), thing);
    if (a == true || b == true) {
      return true;
    }
    else {
      return false;
    }
  }
}
