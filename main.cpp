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
void deleteRebalance(Node* k, Node* &root);

//I wanted something to call when a node was deleted from the tree to make
//what is happpening easier to understand
void deleteAlert(Node* toDelete, Node* &root);

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

      //no rebalancing needed deleted the root of the tree
    }

    //if there is one node
    //it becomes root
    else if(current->getRight() != NULL && current->getLeft() == NULL) {
      root = current->getRight();
      //root->parent is always null
      root->setParent(NULL);
      delete current;

      //the new root of the tree is black
      root->setColor(0);
    }
    //if there is one node (otherside)
    else if(current->getLeft() != NULL  && current->getRight() == NULL) {
      root = current->getLeft();
      //root->parent is always null
      root->setParent(NULL);
      delete current;

      //the new root of the tree is black
      root->setColor(0);

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

      //don't swap colors  Do NOT
      /*
      int newColor = temp->getColor();
      temp->setColor(current->getColor());
      current->setColor(newColor);
      //*/

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
    cout << "target: " << thing << ", current: " << current->getNumber() << endl;
    
    //if this is the end (leaf)
    if(current->getRight() == NULL && current->getLeft() == NULL) {
      //just delete this one

      //the new plan is to call alert before deleting so do that
      deleteAlert(current, root);
      //sucessor is currently not bieng passed (its the NULL)
      //side note. we are not doing this. search will be in alert
      //first that will then call this later

      
      if (previous->getNumber() > thing) {
	//right
	previous->setRight(NULL);
      }
      else {
	//left
	previous->setLeft(NULL);
      }

      //print(root, 0);
      //something was deleted call the alert
      //deleteAlert(current, NULL, previous, root);

      delete current;
    }

    //if there is one node
    //we move the that one up
    //it will work because of how they were added
    
    
    else if(current->getRight() != NULL && current->getLeft() == NULL) {
      //call alert first
      deleteAlert(current, root);

      Node* successor = NULL;
      if (previous->getNumber() > thing) {
	//right
	previous->setRight(current->getRight());
	//update parent
	current->getRight()->setParent(previous);

	 successor = current->getRight();
      }
      else {
	//left
	previous->setLeft(current->getRight());
	//update parent
	current->getRight()->setParent(previous);

        successor = current->getRight();
      }

      //something was deleted call the alert
      //deleteAlert(current, successor, successor->getParent(), root);
    }
    //if there is one node (otherside)
    else if(current->getLeft() != NULL  && current->getRight() == NULL) {
      //call delete alert first
      deleteAlert(current, root);

      Node* successor = NULL;
      if (previous->getNumber() > thing) {
	//right
	previous->setRight(current->getLeft());
	//update parent
	current->getLeft()->setParent(previous);

        successor = current->getLeft();
      }
      else {
	//left
	previous->setLeft(current->getLeft());
	//update parent
	current->getLeft()->setParent(previous);

        successor = current->getLeft();
      }

      //something was deleted call the alert
      //deleteAlert(current, successor, successor->getParent(), root);
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

      //swap colors exept I don;t think you do
      /*
      int newColor = temp->getColor();
      temp->setColor(current->getColor());
      current->setColor(newColor);
      //*/

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

//uncle can be null (i think atleast)
//also most of the anit seg fault is reduntant but at this point I keep readding
//impssible seg fault situations so it is in for next time
void insertRebalance(Node* newNode, Node* &root) {
  cout << "insertRebalence" << endl;
  Node* k = newNode;
  //while loop since you cant breack rule if your parent is black
  //also double checks things as k changes

  print(root, 0);
  cout << k->getParent()->getColor() << endl;
  bool loop = false;
  if (k->getParent()->getColor() == 1) {
    loop = true;
  }
  
  while (loop == true) { //red (or has case where quits if it is root)
    if (k->getParent()->getParent() != NULL) {

      /*
      Node* gp = k->getParent()->getParent();
      if (gp != NULL) {
	cout << "gp: " << gp->getNumber() << endl;
      } 
      if (gp->getRight() != NULL) {
	cout << "r: " << gp->getRight()->getNumber() << endl;
      }
      
      if (gp->getLeft() != NULL) {
	cout << "l: " << gp->getLeft()->getNumber() << endl;
      }
      //*/

      
      if (k->getParent() == k->getParent()->getParent()->getRight()) {

	//cout << "f" << endl;
	//save 'uncle' node
	//with anti seg fault measures
	Node* u = NULL;
	if (k->getParent() != NULL) {
	  if (k->getParent()->getParent() != NULL) {
	    u = k->getParent()->getParent()->getLeft();
	  }
	}
	//cout << "hello" << endl;
	//bool check = false;
	//seg fault layer
	//if(u != NULL) {
	//cout << "uncle: "<< u->getNumber() << endl;
	//print(root, 0);
	int tempcolor = 0;
	if (u != NULL) { 
	  if (u->getColor() == 1) {
	    tempcolor = 1;
	    cout << "tempcolor" << endl;
	  }
	}
	cout << "made it to if" << endl;
	
	if (tempcolor  == 1) { //red, case 3.1
	  cout << "this is happening" << endl;
	  u->setColor(0); //black
	  k->getParent()->setColor(0);
	  k->getParent()->getParent()->setColor(1); //gp -> red
	  k = k->getParent()->getParent(); //change k
	  //print(root, 0);
	  //check = true;
	  print(root, 0);
	    
	}
	
	//}
	//cout << check << endl;
	//dont do if check??
	
        else if (k == k->getParent()->getLeft()) { //case 3.31 and 3.32
	    cout << "we are doing the else if" << endl;
	    
	    k = k->getParent();
	    //!left rotate
	    cout << "!left rotate" << endl;
	    rightRotate(k, root);
	    print(root,0);
	    cout << "done" << endl;
	    //check = true;
	  }
	
	
	//cout << "hi" << endl;
	//print(root, 0);

	//cout <<k->getParent()->getRight() << "!!!" << endl;
	//cout << k->getParent()->getNumber();
	
	//tree can be balcenced earlier so need to check
	else {
	  cout << "else" << endl;
	  //if (check == false) { //parent is not red
	  k->getParent()->setColor(0); //black
	  k->getParent()->getParent()->setColor(1); //gp -> red
	  //!right rotate
	  cout << "!right rotate" << endl;
	  cout<<"rotating: "<< k->getParent()->getParent()->getNumber() << endl;
	  leftRotate(k->getParent()->getParent(), root); //gp
	  print(root,0);
	  cout << "done" << endl;
	}
	cout << "lp" << endl;
      }
      else {
	//do same things with left and right swapped 3.3.3 and 3.3.4
	cout << "mirror" << endl;
	if (k->getParent() == k->getParent()->getParent()->getLeft()) {
	  //save 'uncle' node
	  Node* u = NULL;
	  if (k->getParent() != NULL) {
	    if (k->getParent()->getParent() != NULL) {
	      u = k->getParent()->getParent()->getRight();
	    }
	  }
	  int tempcolor = 0;
	  //seg fault layer
	  if(u != NULL) {
	    if (u->getColor() == 1) {
	      tempcolor = 1;
	      cout << tempcolor << endl;
	    }
	  }

	  if (tempcolor  == 1) { //red, case 3.1
	    cout << "push blackness down" << endl;
	    u->setColor(0); //black
	    k->getParent()->setColor(0);
	    k->getParent()->getParent()->setColor(1); //gp -> red
	    k = k->getParent()->getParent(); //change k
	  }
	  else if (k == k->getParent()->getRight()) { //case 3.31 and 3.32
	    k = k->getParent();
	    //left rotate
	    cout << "left rotate" << endl;
	    //leftRotate(k, root);
	    print(root,0);
	    cout << "done" << endl;
	    }

	  //check we did not balence it aready
	  else {
	    k->getParent()->setColor(0); //black
	    k->getParent()->getParent()->setColor(1); //gp -> red
	    //right rotate
	    //print(root,0);
	    cout << "right rotate" << endl;
	    rightRotate(k->getParent()->getParent(), root); //gp
	    //print(root,0);
	    cout << "done" << endl;
	  }
	}
      }
    }
    else {
      //???
      //me having fun:
      cout << "what did you do?" << endl;
      cout << "..." <<  endl;
      cout << endl;
      cout << "you should always be able to go to parent" << endl;
      cout << "and going up twice should not hit root of tree" << endl;
      cout << "really what did you manage to break" << endl;      
      exit(1);
    }




    //a case exsts where k can be root so k.getparent.getcolor is seg fault
    //soo this exists and is a boolean it checs so that update can be in 2 ifs
    //cout << k->getNumber() << endl;
    if (k->getParent() == NULL) {
      loop = false;
    }
    else if(k->getParent()->getColor() != 1) {
      loop = false;
    }

    
  } //end of while
  root->setColor(0); //root is allways black
}

void deleteAlert(Node* toDelete, Node* &root) {
  //for updated version call this just before deleting a node, wait
  //just search for node in this "rebalnace" so the delete is now ok
  //then call delete?
  cout << "ALERT" << endl;
  cout << toDelete->getNumber() << endl;
  //exit(1);
  

  //call delete rebalancing


  //end by deleting the node
  //remove(num);
}

/*
void deleteAlert(Node* wasDeleted, Node* successor, Node* parent, Node* &root) {
  //wasDeleted->getNumber is very likely inacurate at this point in time
  //does not matter though as only goal is to rebalance tree
  //cout << wasDeleted->getNumber() << " was delted" << endl;
  int succColor = 0;
  if (successor != NULL) {
    if(successor->getColor() != 0) {
      succColor = 1;
    }
  }
  //if wasDeleted or successor is red make them black
  if (succColor == 1 || wasDeleted->getColor() == 1) {
    if (successor != NULL) {
      successor->setColor (0);
    }
  }
  else {
    //it or its next one was not red
    //fix it
    if (successor == NULL) {
      Node* temporary = new Node(-1);
      temporary->setParent(NULL);
      print(root, 0);
      deleteRebalance(temporary, root);
      delete temporary;
    }
    else {
      deleteRebalance(successor, root);
    }
  }
}
*/

void deleteRebalance(Node* k, Node* &root) {
  print (k, 0);
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
    //I think it is x.parent not x
    y->setParent(x->getParent());
  }
  else {
    //x is root so make y root
    root = y;
    y->setParent(NULL);
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
    y->setParent(x->getParent());
    //cout << y->getNumber() << ", " << y->getParent()->getNumber() << " endl" << endl;
    //cout << x->getNumber() << ", " << x->getParent()->getNumber() << " endl" << endl;
  }
  else {
    //x is root so make y root
    root = y;
    y->setParent(NULL);
  }
  //3rd thing
  //make y.left point to x
  y->setRight(x);
  x->setParent(y);
}
