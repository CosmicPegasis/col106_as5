/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
  height = -1;
  par = left = right = NULL;
}

SymNode::SymNode(string k) : SymNode{} {
  key = k;
}

SymNode* SymNode::LeftLeftRotation(){
  return NULL;
}

SymNode* SymNode::RightRightRotation(){
  return NULL;
}

SymNode* SymNode::LeftRightRotation(){
  return NULL;
}

SymNode* SymNode::RightLeftRotation(){
  return NULL;
}

SymNode::~SymNode(){
  delete left;
  delete right;
}
