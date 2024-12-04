/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// #include <iostream>

//Write your code below this line

MinHeap::MinHeap(){
    size = 0;
    root = NULL; 
}

//sz = size+1
string path(int sz){

    string p = "";
    while (sz != 1){
        if (sz % 2 == 1){
            p += 'r';
        }
        else{
            p += 'l';
        }
        sz = sz /2;
    }
    string res  = "";
    for (int i = (p.size()-1) ; i >= 0 ; i--){
        res += p[i];
    }
    return res;
}

// returns root of the heap
HeapNode* heapifyup (HeapNode* curr) {
    HeapNode* result = curr;
    // replaced curr with curr->par;
    while (curr->par != NULL && curr->par->val > curr->val ){
        HeapNode* parent = curr->par;
        HeapNode* parent_left = curr->par->left;
        HeapNode* parent_right = curr->par->right;

        if (curr->left != NULL){
            curr->left->par = curr->par;//8
        }
        if (curr->right != NULL){
            curr->right->par = curr->par;//9
        }



        curr->par = parent->par;//1
        if (parent->par != NULL){ //2
            if (parent->par->left->val == parent->val){
                parent->par->left = curr;
            }
            else{
                parent->par->right = curr;
            }
        }
        parent->par = curr; //3
        parent->left = curr->left;//6
        parent->right = curr->right;//7

        if (parent_right != NULL){
            if (parent_right->val == curr->val){
                curr->left = parent_left;//4
                parent_left->par = curr;

                curr->right = parent;//5
            }
            else{
                curr->right = parent_right;//4
                parent_right->par = curr;

                curr->left = parent;//5
            }
        }
        else{
            // curr->right = parent->right;//4
            curr->left = parent;//5
        }

        result = curr;
    }
    while (result->par != NULL){
        result = result->par;
    }
    return result;
}

// HeapNode* MinHeap::get_root(){
//     return root;
// }

void MinHeap::push_heap(int num){
    if (size == 0){
        HeapNode* n = new HeapNode(num);
        root = n;
        size ++;
        return;
    }
    string p = path (size + 1);
    HeapNode* temp = root;
    HeapNode* prev;
    for (int i = 0 ; i < p.size() ; i++){
        prev = temp;
        if (p[i] == 'l'){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    temp = new HeapNode (num);
    temp->par = prev;
    if (p[p.size()-1] == 'l'){
        prev->left = temp;
    }else{
        prev->right = temp;
    }
    size ++;
    root = heapifyup(temp);
}

string value (HeapNode* a){
    if (a == NULL){
        return "null";
    }
    return std::to_string(a->val);
}

// void inorder (HeapNode* root){
//     if (root == NULL){
//         return;
//     }
//     inorder (root->left);
//     cout << "NodeValue: " << value (root) << ", RightChild: "<< value(root->right) <<", LeftChild: "<<value (root->left) << ", Parent: " << value (root->par) << endl;
//     inorder (root->right);
// }

int MinHeap::get_min(){
    return root->val;
}

//return the modified root
HeapNode* heapifydown (HeapNode* root ){
    if (root == NULL){
        return NULL;
    }

    HeapNode* temp = root;

    if (root->left != NULL && root->left->val < temp->val){
        temp = root->left;
    }
    if (root->right != NULL && root->right->val < temp->val){
        temp = root->right;
    }
    if (temp != root){
        int a = temp->val;
        temp->val = root->val;
        root->val = a;
        temp = heapifydown(temp );
    }
    return temp;
}

void MinHeap::pop(){
    if (size == 0){
        return;
    }
    if (size == 1){
        HeapNode* temp = root ;
        root = NULL;
        delete temp ;
        size--;
        return;
    }

    string pathe = path(size);

    HeapNode* temp = root;
    for (int i = 0 ; i < pathe.size() ; i++){
        if (pathe[i] == 'l'){
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    int a = temp->val;
    root->val = a;
    if (temp->par != NULL){
        if (temp->par->left == temp){
            temp->par->left = NULL;
            temp->par = NULL;
        }else{
            temp->par->right = NULL;
            temp->par = NULL;
        }
    }
    HeapNode* result = heapifydown(root);
    while (result->par != NULL){
        result = result->par;
    }
    size--;
    root = result;
    delete temp;
}

MinHeap::~MinHeap(){
    delete root;
}

// int main (){
//     MinHeap m;
//     m.push_heap(8);
//     m.push_heap(7);
//     m.push_heap(6);
//     m.push_heap(5);
//     m.push_heap(4);
//     m.push_heap(3);
//     m.push_heap(2);
//     m.push_heap(1);
//     m.push_heap(0);
//     inorder (m.get_root());
//     cout << "=========deleting started========="<<endl;
//     m.pop();
//     m.pop();
//     m.pop();
//     m.pop();
//     inorder (m.get_root());
//     cout << "=========deleted========="<< endl;
//     cout << "terminated sucessfully........... " <<endl;
//     // m.push_heap(7);
//     // cout << "======= "<<endl;
//     // inorder (m.get_root());
//     return 0; 
// }