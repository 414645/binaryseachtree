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

  int getNumber();
  void setNumber(int);

  Node* getParent();
  void setParent(Node*);
  int getColor();
  void setColor(int);
private:
  Node* rightNode;
  Node* leftNode;
  int number;
  Node* parent;
  int color;
};
#endif
