/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key = "";
    height = 0;
    address = -1;  //i think not necessary...
    par = nullptr;
    left = nullptr;
    right = nullptr;
}

SymNode::SymNode(string k){
    key = k;
    height = 1;
    address = -1;
    par = nullptr;
    left = nullptr;
    right = nullptr;
}

SymNode::~SymNode(){
    if (!par){
        delete par;
    }
    if (!left){
        delete left;
    }
    if (!right){
        delete right;
    }
}

SymNode* LeftLeftRotation(){return nullptr;}
SymNode* RightRightRotation(){return nullptr;}
SymNode* LeftRightRotation(){return nullptr;} // case 3
SymNode* RightLeftRotation(){return nullptr;} // case 4
