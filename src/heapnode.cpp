/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
  par = left = right = NULL;
}

HeapNode::HeapNode(int _val) : HeapNode{} {
  this->val = _val;
}

HeapNode::~HeapNode(){
  delete left;
  delete right;
}
