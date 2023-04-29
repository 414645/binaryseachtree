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

//Working on making it a balanced tree with red black
//added color (black = 0 red = 1)
//code got really complex and just unreadable with adding so ripped it out and
//tried to make rotates and insertRebalance simple
//and put comments down there on how they work

void print(Node* current, int tab);
//print out the tree in a way that lets you see children + parents + color
void printTest(Node* current, int tab, bool color);
//testprint can show less

void add(Node* &root, Node* current, Node* previous, int thing);
//add thing to the binary tree

void remove(Node* &root, Node* current, Node* previous,int thing);
//three cases here (one is two children, one is one child, one is none)
//also I am handeling root differntlu since pas by refferece

bool search(Node* current, int thing);
//ture is found it, false is not found

//maintian red-black tree properties after problems
void insertRebalance(Node* newNode, Node* &root);
void deleteRebalance(Node* newNode, Node* &root);

//manipulating tree
void leftRotate(Node* x, Node* &root);
void rightRotate(Node* x, Node* &root);

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
    //multiple prints with varying levels of info
    if (strcmp(input, "PRINT") == 0) {
      cout << "Binary Search Tree:" << endl;
      print(root, 0);
    }
    if (strcmp(input, "PRINT1") == 0) {
      cout << "Binary Search Tree(parentless):" << endl;
      printTest(root, 0, true);
    }
    if (strcmp(input, "PRINT2") == 0) {
      cout << "Binary Search Tree(basic):" << endl;
      printTest(root, 0, false);
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
	int thing;
	cin >> thing;
	add(root, root, NULL, thing);
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
    //cout a R or B before node for color
    if (current->getColor() == 0) {
      cout << "B";
    }
    else if (current->getColor() == 1) {
      cout << "R";
    }
    //cout #
    cout << current->getNumber();
    //cout parrent
    if (current->getParent() != NULL) {
      cout << " p=" << current->getParent()->getNumber();
    }
    else {
      cout << " p=NULL";
    }
    //end line
    cout << endl;
    
    //call print on right node
    print(current->getRight(), tab + 1);
  }
}

//this prints without showing parent
void printTest(Node* current, int tab, bool color) {
  if (current != NULL) {
    //cout << "print: " << current->getNumber() << endl;
    //call print on left node
    printTest(current->getLeft(), tab + 1, color);
    //print myself with correct tab number
    for (int a = 0; a < tab; a++) {
      cout << "    ";
    }
    if(color == true) {
      //cout a R or B before node for color
      if (current->getColor() == 0) {
	cout << "B";
      }
      else if (current->getColor() == 1) {
	cout << "R";
      }
    }
    //cout #
    cout << current->getNumber();
    //end line
    cout << endl;
    
    //call print on right node
    printTest(current->getRight(), tab + 1, color);
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
    //root parent = NULL by default
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

      //added a Node to the Tree!!! handle balancing
      //list parent
      newNode->setParent(current);
      //new node is red by default
      newNode->setColor(1);
      //figure out balencing
      insertRebalance(newNode, root);
      
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

      
      //added a Node to the Tree!!! handle balancing
      //same code as above!!!!!
      //list parent
      newNode->setParent(current);
      //new node is red by default
      newNode->setColor(1);
      //figure out balencing
      insertRebalance(newNode, root);
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
      //root->parent is always null
      root->setParent(NULL);
      delete current;
    }
    //if there is one node (otherside)
    else if(current->getLeft() != NULL  && current->getRight() == NULL) {
      root = current->getLeft();
      //root->parent is always null
      root->setParent(NULL);
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
      //call delete on the last one
      remove(root, root, NULL, replace);
      
      //set current to a copy of the last one
      current->setNumber(replace);
      //update parent
      current->setParent(temp->getParent());
      
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
	//update parent
	current->getRight()->setParent(previous);
      }
      else {
	//left
	previous->setLeft(current->getRight());
	//update parent
	current->getRight()->setParent(previous);
      }
    }
    //if there is one node (otherside)
    else if(current->getLeft() != NULL  && current->getRight() == NULL) {
      if (previous->getNumber() > thing) {
	//right
	previous->setRight(current->getLeft());
	//update parent
	current->getLeft()->setParent(previous);
      }
      else {
	//left
	previous->setLeft(current->getLeft());
	//update parent
	current->getLeft()->setParent(previous);
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
      remove(current, current, NULL, replace);
      //cout << "done" << endl;
      current->setNumber(replace);
      
      //update parent
      current->setParent(temp->getParent());
      
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

void insertRebalance(Node* newNode, Node* &root) {
  cout << "insertRebalence" << endl;
  Node* k = newNode;
  //case 1
  if (k->getParent() == NULL) {
    k->setColor(0);
  }
  //case 2
  if (k->getParent()->getColor() == 0) {
    //do nothing
  }
  //case 3
  if (k->getParent()->getColor() == 1) {
    Node* gp = k->getParent()->getParent();
    //set up for case 3.2 for a null uncle
    bool nullUncle = false;
    cout << "loc 1" << endl;
    if (gp->getRight() == NULL || gp->getLeft() == NULL) {
      cout << "working" << endl;
      nullUncle = true;
      
    }
    else if (gp->getRight()->getColor() == 0 ||
	     gp->getLeft()->getColor() == 0) {
      nullUncle = true;
    }
    //case 3.2
    cout << "loc 2" << endl;
    //nullUncle = true;
    cout << "loc" << endl;
    if (nullUncle == true) {
      //3.2.1
      
      cout << "hi?" << endl;
      if ( k->getParent() == gp->getRight() ) {
	cout << "true" << endl;
      }
      //cout << k->getNumber() << endl;
      //cout << k->getParent()->getNumber() << endl;
      //cout << gp->getRight()->getNumber() << endl;

	
      cout << "nullUncle" << endl;
      if (k->getParent() == gp->getRight() &&  //p is rightchild of gp
	  k->getParent()->getRight() == k) { //k is rightchild of p

	cout << "left rotation" << endl;
	print(root, 0);
	//leftRotate(gp, gp->getRight(), root);
      }
      //3.2.2
      else if (k->getParent() == gp->getRight() &&  //p is rightchild of gp
	       k->getParent()->getLeft() == k) { //k is leftchild of p
	
	cout << "right rotation" << endl;
	//rightRotate(k->getParent(), k, root);
	//do same thing as 3.2.1
	insertRebalance(k, root);
      }
      //3.2.3
      //3.2.4
      //this is just a mess
      cout << "no fautl" << endl;
      if (k->getParent() == gp->getLeft() &&  //p is lchild of gp
	  k->getParent()->getLeft() == k) { //k is ltchild of p

	cout << "! right rotation" << endl;
	print(root, 0);
	//swapped gp>right to left
	//leftRotate(gp, gp->getLeft(), root);
      }
      //3.2.2
      else if (k->getParent() == gp->getLeft() &&  //p is leftchild of gp
	       k->getParent()->getRight() == k) { //k is rchild of p
	
	cout << "! left rotation" << endl;
	//rightRotate(k->getParent(), k, root);
	//do same thing as 3.2.1
	insertRebalance(k, root);
      }
    }
    //case 3.1
    else if (gp->getRight()->getColor() == 1 &&
	     gp->getLeft()->getColor() == 1) {
      cout << "last thing" << endl;
      gp->setColor(1);
      gp->getRight()->setColor(0);
      gp->getLeft()->setColor(0);
    }
  }
}

void deleteRebalance(Node* newNode, Node* &root) {

}

//manipulating tree
void leftRotate(Node* x, Node* &root) { //& root or whatever
  //for a left rotation y is the right child of x
  Node* y = x->getRight();

  //1st thing
  //make x point to the left subtree of y
  x->setRight(y->getLeft());
  if(x->getRight() != NULL) {
    x->getRight()->setParent(x);
  }
  //2nd thing
  //make x.parent point to y instead
  if (x->getParent() != NULL) {
    //y replaces x in tree
    if (x->getParent()->getRight() == x) {
      x->getParent()->setRight(y);
    }
    else {
      x->getParent()->setLeft(y);
    }
    //double linked
    y->setParent(x);
  }
  else {
    //x is root so make y root
    root = y;
  }
  //3rd thing
  //make y.left point to x
  y->setLeft(x);
  x->setParent(y);
}

void rightRotate(Node* x, Node* &root) {
  //for a right rotation y is the left  child of x
  Node* y = x->getLeft();

  //1st thing
  //make x point to the right subtree of y
  x->setLeft(y->getRight());
  if(x->getLeft() != NULL) {
    x->getLeft()->setParent(x);
  }
  //2nd thing
  //make x.parent point to y instead
  if (x->getParent() != NULL) {
    //y replaces x in tree
    if (x->getParent()->getRight() == x) {
      x->getParent()->setRight(y);
    }
    else {
      x->getParent()->setLeft(y);
    }
    //double linked
    y->setParent(x);
  }
  else {
    //x is root so make y root
    root = y;
  }
  //3rd thing
  //make y.left point to x
  y->setRight(x);
  x->setParent(y);
}
