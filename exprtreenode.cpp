/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type = "NULL";
    id = "NULL2";
    num = 0;
    left = NULL;
    right = NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    type = t;
    id = "";
    if (type == "VAL"){
        num = v;
    }
    // if type is "VAR" then you can directly modify id , as it is a public variable;
    left = NULL;
    right = NULL;
}

ExprTreeNode::~ExprTreeNode(){
    if (left != NULL){
        delete left;
    }
    if (right != NULL){
        delete right;
    }
}

