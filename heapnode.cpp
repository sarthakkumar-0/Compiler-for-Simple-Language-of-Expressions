/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

class HeapNode{
public:
    int val;
    HeapNode* par = NULL;
    HeapNode* left = NULL;
    HeapNode* right = NULL;

    HeapNode(){
    }

    HeapNode(int _val){
        val = _val;
    }
    ~HeapNode(){
        if (par != NULL){
            delete par;
        }
        if (left != NULL){
            delete left;
        }
        if (right != NULL){
            delete right;
        }
    }

};