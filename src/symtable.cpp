/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymNode *create_symnode(string k, SymNode *par, SymNode *left, SymNode *right) {
  SymNode *res = new SymNode(k);
  res->left = left;
  res->right = right;
  res->par = par;
  return res;
}
SymNode *create_symnode(string k, SymNode *left, SymNode *right) {
  SymNode *res = new SymNode(k);
  res->left = left;
  res->right = right;
  return res;
}
SymNode *create_symnode(string k) {
  SymNode *res = new SymNode(k);
  res->par = NULL;
  return res;
}

void safe_delete(SymNode *to_be_deleted) {
  to_be_deleted->left = NULL;
  to_be_deleted->right = NULL;
  delete to_be_deleted;
}

// Write your code below this line
SymNode *avlSearch(SymNode *root, string k) {
  if (!root) {
    return NULL;
  }
  if (root->key < k) {
    if (root->right) {
      return avlSearch(root->right, k);
    } else {
      return NULL;
    }
  } else if (root->key > k) {
    if (root->left) {
      return avlSearch(root->left, k);
    } else {
      return NULL;
    }
  } else {
    return root;
  }
};
int avlGetBalance(SymNode *cur) {
  int left_height = -1;
  int right_height = -1;
  // if(!cur){
  //   return 0;
  // }
  if (cur->left) {
    left_height = cur->left->height;
  }
  if (cur->right) {
    right_height = cur->right->height;
  }
  return left_height - right_height;
}

void avlUpdateHeight(SymNode *cur, int leftHeight, int rightHeight) {
  if (!cur) {
    // std::cout << "[AVL_Update_Height] Node is null\n";
  }
  cur->height = (leftHeight >= rightHeight ? leftHeight : rightHeight) + 1;
}
// void avlUpdateBalance(SymNode *cur, int leftHeight, int rightHeight) {
//     if (!cur) {
//       // // std::cout << "[AVL_Update_Balance] Node is null\n";
//     }
//     avlGetBalance(cur);
// }
void avlUpdateNode(SymNode *cur) {
  if (!cur) {
    return;
  }
  int leftHeight = -1, rightHeight = -1;
  if (cur->left) {
    leftHeight = cur->left->height;
  }
  if (cur->right) {
    rightHeight = cur->right->height;
  }
  avlUpdateHeight(cur, leftHeight, rightHeight);
  // avlUpdateBalance(cur, leftHeight, rightHeight);
}
void avlUpdateBranch(SymNode *cur) {
  if (!cur) {
    return;
  } else {
    avlUpdateNode(cur);
    avlUpdateBranch(cur->par);
  }
}
void avlMakeRightChild(SymNode *cur, SymNode *victim) {
  if (!cur) {
    //   // std::cout << "[avlMakeChild] Node requested to have a child is null\n";
  }
  if (victim) {
    victim->par = cur;
  }
  cur->right = victim;
}
void avlMakeLeftChild(SymNode *cur, SymNode *victim) {
  if (!cur) {
    //   // std::cout << "[avlMakeChild] Node requested to have a child is null\n";
  }
  if (victim) {
    victim->par = cur;
  }
  cur->left = victim;
}
void avlConnectWithGrandparent(SymNode *cur, SymNode *child) {
  if (!cur) {
    //  // std::cout << "[avlConnectWithGramma] Parent of null node requested";
  }
  if (cur->par) {
    if (cur->par->left == cur) {
      avlMakeLeftChild(cur->par, child);
    } else {
      avlMakeRightChild(cur->par, child);
    }
  } else {
    child->par = NULL;
  }
}
void avlBalanceRR(SymNode *cur) {
  if (!cur) {
    //   // std::cout << "[avlBalance] Node to be balanced is null \n";
  }
  avlConnectWithGrandparent(cur, cur->right);
  SymNode *newBase = cur->right;
  avlMakeRightChild(cur, cur->right->left);
  avlMakeLeftChild(newBase, cur);
  avlUpdateBranch(cur);
}
void avlBalanceLL(SymNode *cur) {
  if (!cur) {
    //  // std::cout << "[avlBalance] Node to be balanced is null \n";
  }
  avlConnectWithGrandparent(cur, cur->left);
  SymNode *newBase = cur->left;
  avlMakeLeftChild(cur, cur->left->right);
  avlMakeRightChild(newBase, cur);
  avlUpdateBranch(cur);
}

void avlBalanceRL(SymNode *cur) {
  if (!cur) {
    //  // std::cout << "[avlBalance] Node to be balanced is null \n";
  }
  avlBalanceLL(cur->right);
  avlBalanceRR(cur);
}
void avlBalanceLR(SymNode *cur) {
  if (!cur) {
    // // std::cout << "[avlBalance] Node to be balanced is null \n";
  }
  avlBalanceRR(cur->left);
  avlBalanceLL(cur);
}
bool avlLLImbalance(SymNode *cur) {
  if (avlGetBalance(cur) > 1) {
    if (!(cur->left)) {
      //   // std::cout << "[avlLLImbalance] Balance > 1 but no left child";
      return false;
    }
    if (avlGetBalance(cur->left) >= 0) {
      if (avlGetBalance(cur->left) > 2) {
        //     // std::cout << "[avlLLImbalance] Child node is imbalanced";
        return false;
      }
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}
bool avlRRImbalance(SymNode *cur) {
  if (avlGetBalance(cur) < -1) {
    if (!(cur->right)) {
      //   // std::cout << "[avlLLImbalance] Balance < -1 but no right child";
      return false;
    }
    if (avlGetBalance(cur->right) <= 0) {
      if (avlGetBalance(cur->right) < -1) {
        //     // std::cout << "[avlLLImbalance] Child node is imbalanced";
        return false;
      }
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}
bool avlLRImbalance(SymNode *cur) {
  if (avlGetBalance(cur) > 1) {
    if (!(cur->left)) {
      //    // std::cout << "[avlLRImbalance] Balance > 1 but no left child";
      return false;
    }
    if (avlGetBalance(cur->left) < 0) {
      if (avlGetBalance(cur->left) < -1) {
        //    // std::cout << "[avlLLImbalance] Child node is imbalanced";
        return false;
      }
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}
bool avlRLImbalance(SymNode *cur) {
  if (avlGetBalance(cur) < -1) {
    if (!(cur->right)) {
      //    // std::cout << "[avlLLImbalance] Balance < -1 but no right child";
      return false;
    }
    if (avlGetBalance(cur->right) > 0) {
      if (avlGetBalance(cur->right) > 1) {
        //    // std::cout << "[avlLLImbalance] Child node is imbalanced";
        return false;
      }
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}
SymNode *avlBalance(SymNode *cur) {
  if (avlLLImbalance(cur)) {
    avlBalanceLL(cur);
  } else if (avlLRImbalance(cur)) {
    avlBalanceLR(cur);
  } else if (avlRRImbalance(cur)) {
    avlBalanceRR(cur);
  } else if (avlRLImbalance(cur)) {
    avlBalanceRL(cur);
  }
  //    avlUpdateBranch(cur);
  if (!(cur->par)) {
    return cur;
  }
  return avlBalance(cur->par);
}

SymNode *avlInsert(SymNode *root, string val) {
  if (root->key < val) {
    if (!(root->right)) {
      root->right = create_symnode(val, root, NULL, NULL);
      avlUpdateBranch(root->right);
      return avlBalance(root->right);
    } else {
      return avlInsert(root->right, val);
    }
  } else if (root->key > val) {
    if (!(root->left)) {
      root->left = create_symnode(val, root, NULL, NULL);
      avlUpdateBranch(root->left);
      return avlBalance(root->left);
    } else {
      return avlInsert(root->left, val);
    }
  } else {
    // std::cout << "[AVL_INSERT] Tried to insert duplicate value in BST "
    //             << root->key << "\n";
    return NULL;
  }
}
SymNode *avl_replace_node(SymNode *root, SymNode *replacer) {
  if (replacer) {
    if (replacer != root->right) {
      replacer->right = root->right;
    }
    if (replacer != root->left) {
      replacer->left = root->left;
    }
    replacer->par = root->par;
  }
  if (root->left) {
    if (replacer != root->left) {
      root->left->par = replacer;
    }
  }
  if (root->right) {
    if (replacer != root->right) {
      root->right->par = replacer;
    }
  }
  if (root->par) {
    if (root->par->right == root) {
      root->par->right = replacer;
    } else if (root->par->left == root) {
      root->par->left = replacer;
    }
  }
  safe_delete(root);
  return replacer;
}

SymNode *avl_find_successor(SymNode *root) {
  if (!(root->right)) {
    if (root->par && (root->par->key > root->key)) {
      return root->par;
    } else {
      // std::cout << "[BST_FIND_SUCCESSOR] No successor exists";
      return create_symnode(0);
    }
  }
  root = root->right;
  while (root->left) {
    root = root->left;
  }
  return root;
}
SymNode *avl_delete_leaf(SymNode *root) {
  SymNode *parent = root->par;
  avl_replace_node(root, NULL);
  return parent;
}
SymNode *avl_delete_node_without_left_child(SymNode *root) {
  return avl_replace_node(root, root->right);
}
SymNode *avl_delete_node_without_right_child(SymNode *root) {
  return avl_replace_node(root, root->left);
}
SymNode *avl_delete_node_with_both_children(SymNode *root) {
  SymNode *succ = avl_find_successor(root);
  root->key = succ->key;
  root->address = succ->address;
  if (succ->right) {
    return avl_delete_node_without_left_child(succ);
  } else {
    return avl_delete_leaf(succ);
  }
}
SymNode *avl_delete(SymNode *root, string val) {
  if (!root) {
    // std::cout << "[BST_Delete] Value not found in BST\n";
  } else if (val > root->key) {
    return avl_delete(root->right, val);
  } else if (val < root->key) {
    return avl_delete(root->left, val);
  }
  if (root->left && root->right) {
    root = avl_delete_node_with_both_children(root);
  } else if (root->left) {
    root = avl_delete_node_without_right_child(root);
  } else if (root->right) {
    root = avl_delete_node_without_left_child(root);
  } else {
    root = avl_delete_leaf(root);
  }
  avlUpdateBranch(root);
  root = avlBalance(root);
  return root;
}

SymbolTable::SymbolTable() {
  root = NULL;
  size = 0;
}

void SymbolTable::insert(string k) {
  if (size == 0) {
    root = create_symnode(k);
    avlUpdateBranch(root);
  } else {
    this->root = avlInsert(this->root, k);
  }
  size++;
}

void SymbolTable::remove(string k) {
  if (size == 1) {
    delete this->root;
    this->root = NULL;
    size--;
  } else {
    if(SymbolTable::search(k) != -2){
	this->root = avl_delete(this->root, k);
	size--;
    }
  }
}

int SymbolTable::search(string k) {
  SymNode *node = avlSearch(this->root, k);
  if (!node) {
    return -2;
  } else {
    return node->address;
  };
}

void SymbolTable::assign_address(string k, int idx) {
  SymNode *cur = avlSearch(this->root, k);
  cur->address = idx;
}

int SymbolTable::get_size() { return this->size; }

SymNode *SymbolTable::get_root() { return this->root; }

SymbolTable::~SymbolTable() { delete root; }
