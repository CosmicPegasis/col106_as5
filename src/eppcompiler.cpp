/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
#define SUB_TYPE(a, b)                                                         \
  else if (root->type == b) {                                                  \
    res += a;                                                                  \
  }

void handleLeafNode(ExprTreeNode *cur, SymbolTable *sym, vector<string> &v) {
  if (cur->type == "VAL") {
    v.push_back("PUSH " + to_string(cur->num));
  } else {
    int address = sym->search(cur->id);
    v.push_back("PUSH mem[" + to_string(address) + "]");
  }
}
void handleOperatorNode(ExprTreeNode *cur, SymbolTable *sym,
                        vector<string> &v) {
  v.push_back(cur->type);
}
void solveRHS(ExprTreeNode *cur, SymbolTable *sym, vector<string> &v) {
  string res = "";
  if (!cur) {
    return;
  }
  solveRHS(cur->right, sym, v);
  solveRHS(cur->left, sym, v);
  if (!(cur->left) && !(cur->right)) { // Must be a variable of a value
    handleLeafNode(cur, sym, v);
  } else {
    handleOperatorNode(cur, sym, v);
  }
}
EPPCompiler::EPPCompiler() {}

EPPCompiler::EPPCompiler(string out_file, int mem_limit) : EPPCompiler{} {
  this->output_file = out_file;
  this->memory_size = mem_limit;
  for (int i = mem_limit - 1; i > -1; i--) {
    mem_loc.push_back(i);
  }
}
void assignLHSVariable(string &id, SymbolTable *sym, vector<int> &mem_loc) {
  if (sym->search(id) == -2) {
    // Means we don't have an address already
    int new_address = mem_loc.back();
    mem_loc.pop_back();
    sym->insert(id);
    sym->assign_address(id, new_address);
  } else if (sym->search(id) == -1) {
    int new_address = mem_loc.back();
    mem_loc.pop_back();
    sym->assign_address(id, new_address);
  } else {
    // If already has an address then don't do anything
    return;
  }
}
bool isDeletionTree(ExprTreeNode* root){
  return root->left->type == "DEL";
}
bool isAssignmentTree(ExprTreeNode* root){
  return root->left->type == "VAR";
}

void EPPCompiler::compile(vector<vector<string>> code) {
  vector<string> targ_code;
  for (vector<string> &line : code) {
    this->targ.parse(line);
    ExprTreeNode* root = this->targ.expr_trees.back();
    if(isDeletionTree(root)){
      if(this->targ.last_deleted != -1){
	mem_loc.push_back(this->targ.last_deleted);
      }
    }
    else if(isAssignmentTree(root)){
	assignLHSVariable(root->left->id, this->targ.symtable, mem_loc);
    }
    else{
      // Must be return; do nothing.
    }
    vector<string> tokenized_targ_line = generate_targ_commands();
    string targ_line = "";
    for (string &token : tokenized_targ_line) {
      targ_line += token + "\n";
    }
    targ_code.push_back(targ_line);
  }
  write_to_file(targ_code);
}
vector<string> gen_tree_targ_commands(ExprTreeNode *root, SymbolTable *symtable,
                            vector<int> &mem_loc, int last_deleted) {
  vector<string> res;
  if (isDeletionTree(root)) {
    return res;
  }
  solveRHS(root->right, symtable, res);
  if (isAssignmentTree(root)) {
    res.push_back("mem[" + to_string(symtable->search(root->left->id)) +
                  "] = POP");
  } else {
    // Must be return
    res.push_back("RET = POP");
  }
  return res;
}
vector<string> EPPCompiler::generate_targ_commands() {
  return gen_tree_targ_commands(this->targ.expr_trees.back(), this->targ.symtable,
                      this->mem_loc, this->targ.last_deleted);
}

void EPPCompiler::write_to_file(vector<string> commands) {
  ofstream fout;
  fout.open(this->output_file);
  for (string &line : commands) {
    fout << line;
  }
}

EPPCompiler::~EPPCompiler() {}
