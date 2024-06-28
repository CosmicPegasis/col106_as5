/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

#define CTOKEN(a, b)                                                           \
  else if (token == a) {                                                       \
    type = b;                                                                  \
  }

// Write your code below this line
string determine_type(string token) {
  string type;
  bool is_variable = true;
  if (token == "+") {
    type = "ADD";
  }
  CTOKEN("-", "SUB")
  CTOKEN("*", "MUL")
  CTOKEN("/", "DIV")
  CTOKEN(":=", "ASSIGN")
  CTOKEN("ret", "RET"
         )
  CTOKEN("del", "DEL")
  CTOKEN("(", "LB")
  CTOKEN(")", "RB")
  else {

    for (char &c : token) {
      if (((c < 'A' || c > 'z') && c != '_')) {
        is_variable = false;
        break;
      }
    }
    if (is_variable) {
      type = "VAR";
    } else {
      type = "VAL";
    }
  }
  return type;
}
void create_subtree(vector<ExprTreeNode *> &expr_trees) {
  vector<ExprTreeNode *> assignment_arr;
  while (expr_trees.back()->type != "LB") {
    assignment_arr.push_back(expr_trees.back());
    expr_trees.pop_back();
  }
  ExprTreeNode *left_bracket = expr_trees.back();
  delete left_bracket;
  expr_trees.pop_back();
  if (assignment_arr.size() == 3) {
    ExprTreeNode *right = assignment_arr[0];
    ExprTreeNode *op = assignment_arr[1];
    ExprTreeNode *left = assignment_arr[2];
    op->right = right;
    op->left = left;
    expr_trees.push_back(op);
  }
}

ExprTreeNode *parse_token(string token) {
  string type = determine_type(token);
  ExprTreeNode *node = new ExprTreeNode(type, 0);
  if (type == "VAR") {
    node->id = token;
  } else if (type == "VAL") {
    node->num = stoi(token);
  }
  return node;
}

Parser::Parser() { this->symtable = new SymbolTable(); }
int syncSymtable(ExprTreeNode *root, SymbolTable *sym) {
  if (root->left->type == "DEL") {
    int address = sym->search(root->right->id);
    if (address >= -1) {
      sym->remove(root->right->id);
      return address;
    }
  } else if (root->left->type == "VAR") {
    if (sym->search(root->left->id) == -2) {
      sym->insert(root->left->id);
    }
  }
  return -1;
}

void Parser::parse(vector<string> expression) {
  vector<ExprTreeNode *> stk;
  for (string &s : expression) {
    ExprTreeNode *node = parse_token(s);
    if (node->type == "RB") {
      create_subtree(stk);
      delete node;
    } else {
      stk.push_back(node);
    }
  }
  // Stack is guaranteed to have three elements in the end
  stk[1]->right = stk[2];
  stk[1]->left = stk[0];
  this->expr_trees.push_back(stk[1]);
  this->last_deleted = syncSymtable(this->expr_trees.back(), this->symtable);
}

Parser::~Parser() {
  delete this->symtable;
  for (ExprTreeNode *node : expr_trees) {
    delete node;
  }
}
