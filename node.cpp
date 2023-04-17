#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
  cout << "blank node created" << endl;
  rightNode = NULL;
  leftNode = NULL;
  number = -1;
  parent = NULL;
  color = -1;
  
}
Node::Node(int newNumber) {
  rightNode = NULL;
  leftNode = NULL;
  number = newNumber;
  //default parent to NULL and color to black
  parent = NULL;
  color = 0;
}

Node::~Node() {
  //cout << "node destroyed" << endl;
}
Node* Node::getRight() {
  return rightNode;
}
Node* Node::getLeft() {
  return leftNode;
}
void Node::setRight(Node* newRight) {
  rightNode = newRight;
}
void Node::setLeft(Node* newLeft) {
  leftNode = newLeft;
}
/*
char Node::getThing() {
  return thing;
}
Node* Node::getNode() {
  return myNode;
}*/
int Node::getNumber() {
  return number;
}
void Node::setNumber(int newNumber) {
  number = newNumber;
}


Node* Node::getParent() {
  return parent;
}
void Node::setParent(Node* newparent) {
  parent = newparent;
}
int Node::getColor() {
  return color;
}
void Node::setColor(int newcolor) {
  color = newcolor;
}


