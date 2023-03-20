#ifndef Node_H
#define Node_H

#include <iostream>
#include <cstring>

class Node {
public:
  Node();
  //Node(char);
  //Node(Node*);
  Node(int);
  ~Node();
  
  Node* getRight();
  Node* getLeft();
  void setRight(Node*);
  void setLeft(Node*);

  //char getThing();
  //Node* getNode();
  int getNumber();
private:
  Node* rightNode;
  Node* leftNode;
  int number;
  //char thing;
  //Node* myNode;
};
#endif
