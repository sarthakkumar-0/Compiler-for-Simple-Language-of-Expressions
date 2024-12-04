/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    size = 0;
    root = NULL;
}

string value (SymNode* node){
    if(node == NULL){
        return "null";
    }
    return node->key;
}

int hgt(SymNode* node){
    if (node == NULL){
        return 0;
    }
    return node->height;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymNode* rotRight(SymNode* node){

    if (node == NULL || node->left == NULL) {
        return node; //already balanced
    }

    SymNode* parentNode = node->par;
    SymNode* newRoot = node->left;
    SymNode* temp =newRoot->right;

    newRoot->right = node;
    newRoot->par = parentNode;

    node->par = newRoot;
    node->left = temp;

    if(temp!=NULL){
        temp->par = node;
    }

    if(parentNode!=NULL){
        if(parentNode->left == node){
            parentNode->left = newRoot;
        }
        else if(parentNode->right== node){
            parentNode->right = newRoot;
        }
    }


    node->height = 1 + std::max(hgt(node->left),hgt(node->right));
    newRoot->height = 1 + std::max(hgt(newRoot->left),hgt(newRoot->right));

    return newRoot;

}

SymNode* rotLeft(SymNode* node){

    if (node == NULL || node->right == NULL) {
        return node; //already balanced
    }    

    SymNode* newRoot = node->right;
    SymNode* parentNode = node->par;
    SymNode* temp = newRoot->left;

    newRoot->par = parentNode;
    newRoot->left = node;

    node->par = newRoot;
    node->right = temp;

    if(temp!=NULL){
        temp->par = node;
    }

    if(parentNode!=NULL){
        if(parentNode->left == node){
            parentNode->left = newRoot;
        }
        else if(parentNode->right== node){
            parentNode->right = newRoot;
        }
    }

    node->height = 1 + std::max(hgt(node->left),hgt(node->right));
    newRoot->height = 1 + std::max(hgt(newRoot->left),hgt(newRoot->right));

    return newRoot;
}

SymNode* rotRightLeft(SymNode* node){
    node->right = rotRight(node->right);
    return rotLeft(node);
}

SymNode* rotLeftRight(SymNode* node){
    node->left = rotLeft(node->left);
    return rotRight(node);
}

int getBalance(SymNode* node){
    if (node == NULL){
        return 0;
    }
    int a = hgt(node->left) - hgt(node->right);
    return a;
}

SymNode* insertion(SymNode* root ,string k ,int & size){
    //taking for granted that key is not present
    if (root == NULL){
        SymNode* n = new SymNode (k);
        root = n ;
        size++;
        return root ;
    }
    SymNode* temp = root ;
    SymNode* parent;
    while (temp != NULL){
        parent = temp;
        if (temp->key < k){
            // temp->height++;
            temp = temp->right;
        }
        else if(temp->key > k){
            // temp->height++;
            temp = temp->left;
        }
        else{
            //this case will never come
            return root;
            break;
        }
    }

    SymNode* n = new SymNode(k);
    if (parent->key > k){
        parent->left = n;
        n->par = parent;
        size++;
    }
    else if (parent->key < k){
        parent->right = n;
        n->par = parent;
        size++;
    }

    SymNode* result;
    // the restoration part......
    while (parent != NULL){
        parent->height = 1 + max(hgt(parent->left), hgt(parent->right));
        int balance = getBalance(parent);
        if (balance > 1 && k < parent->left->key) {
            parent = rotRight(parent);
        } else if (balance < -1 && k > parent->right->key) {
            parent = rotLeft(parent);
        } else if (balance > 1 && k > parent->left->key) {
            parent = rotLeftRight(parent);
        } else if (balance < -1 && k < parent->right->key) {
            parent = rotRightLeft(parent);
        }
        result = parent;
        parent = parent->par;
        }
    return result ;    
}

// if same is inserted then just return, no change in address....
void SymbolTable::insert(string k){
    if (SymbolTable::search(k) != -2){
        // if same is inserted then just return, no change in address....
        return;
    }
    int sz = size;
    root = insertion (root , k ,sz);
    size = sz;  
}

string successor(string val , SymNode* root ){
    string s = "" ;
    SymNode* temp = root;
    while (temp->key != val){
        if (temp->key < val){
            temp = temp->right;
        }
        else if (temp->key > val){
            s = temp->key;
            temp = temp->left;
        }
    }
    if (temp->right == NULL){
        return s;
    }
    temp = temp->right;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp->key;
}

SymNode* restoration (SymNode* node){
    SymNode* result;
    // the restoration part......
    // while (node != NULL){
        node->height = 1 + max(hgt(node->left), hgt(node->right));
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0) {
            node = rotRight(node);
        } else if (balance < -1 && getBalance(node->right) <= 0) {
            node = rotLeft(node);
        } else if (balance > 1 && getBalance(node->left) < 0) {
            node = rotLeftRight(node);
        } else if (balance < -1 && getBalance(node->left) > 0) {
            node = rotRightLeft(node);
        }
        result = node;
        // node = node->par;
        // }


    return result ;
}


SymNode* deletion(string val , SymNode* root ){
    if (root == NULL){
        //root not found;
        return root;
    }

    if (root->key > val){
        root->left = deletion(val, root->left);
        root = restoration(root);
        return root;
    }
    else if (root->key < val){
        root->right = deletion(val ,root->right);
        root = restoration(root);
        return root;
    }

    // the important case..
    //root->key = val;
    else{
        if (root->left != NULL && root->right != NULL){
         
            root->key = successor(val , root); 
            root->right = deletion (root->key , root->right );
            root = restoration (root);
            return root;
        }
        else{
            if (root->left == NULL){
                SymNode* parent = root->par;
                SymNode * n = root;
                root = (root->right);
                if (root != NULL){
                    root->par = parent;
                }
                if (n != NULL){
                    delete n;
                }
                return root;
            }
            else{
                SymNode* n = root;
                SymNode* parent = root->par;
                root = (root->left) ;
                if (root != NULL){root->par = parent;}
                if (n != NULL){delete n;}                
                return root;
            }
        }
    }  
}

void SymbolTable::remove(string k){
    if (search(k) == -2){
        return;
    }
    root = deletion(k,root);
    size--;
    return ;
}

int SymbolTable::search(string k){
    if (root == NULL){
        return -2;
    }
    SymNode* temp = root;
    while (temp!=NULL){
        if (temp->key < k){
            temp = temp->right;
        }
        else if (temp->key > k){
            temp = temp->left;
        }
        else{
            return temp->address;
        }
    }
    return -2;
}

// if element is not present, i am inserting it first....
void SymbolTable::assign_address(string k,int idx){
    if (search(k) == -2){
        insert(k);
    }
    if (root == NULL){
        return;
    }
    SymNode* temp = root;
    while (temp!=NULL){
        if (temp->key < k){
            temp = temp->right;
        }
        else if (temp->key > k){
            temp = temp->left;
        }
        else{
            break;
        }
    }
    temp->address = idx;
}

void deletenode(SymNode* root){
    if (root == NULL){
        return ;
    }
    // delete root->val;
    deletenode (root->left);
    deletenode (root->right);

    delete root;
}

SymbolTable::~SymbolTable(){
    deletenode(root);
}
