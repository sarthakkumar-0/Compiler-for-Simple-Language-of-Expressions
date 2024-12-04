/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
#include <iostream>

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}

// num_type = 1 for operations
// num_type = 2 for numbers
// num_type = 3 for variables
// num_type = 4 for delete
// num_type = 5 for return
string get_type (string input , int & num_type){
    char first = input[0];
    switch (first)
    {
    case '+':
        num_type = 1;
        return "ADD";
        break;
    case '-':
        num_type = 1;
        return "SUB";
        break;
    case '*':
        num_type = 1;
        return "MUL";
        break;
    case '/':
        num_type = 1;
        return "DIV";
        break;
    case '%':
        num_type = 1;
        return "MOD";

    }
    if (first >= 48 && first <= 57){
        num_type = 2;
        return "VAL";
    }
    else{
        if (input == "del"){
            num_type = 4;
            return "DEL";
        }
        else if (input == "ret"){
            num_type = 5;
            return "RET";
        }
        else{
            num_type = 3;
            return "VAR";
        }
    }
}

void Parser::parse(vector<string> expression){
    int sz = expression.size();
    int check = 0;
    vector <ExprTreeNode*> this_code;

    //root node starts with ":="
    ExprTreeNode* rt = new ExprTreeNode("START", -1);
    rt->id = ":=";
    this_code.push_back(rt);

    //the lhs variable/return/delete
    ExprTreeNode* lhs ;
    int i = 0;
    string lh_type = get_type(expression[0], i);
    lhs = new ExprTreeNode (lh_type , -1);
    if (lh_type == "VAR"){
        lhs->id = expression[0];
    }
    this_code[0]->left = lhs;

    for (int i = 2 ; i < sz ; i++){
        if (expression[i] == "("){
            check ++;
            // cout<<"case1"<<endl;
            continue;
        }

        if (expression[i] == ")"){
            check--;
            ExprTreeNode* temp1 = this_code[this_code.size()-1];
            this_code.pop_back();
            ExprTreeNode* temp2 = this_code[this_code.size()-1];
            this_code.pop_back();

            temp2->right = temp1;
            this_code.push_back(temp2);
            // cout<<"case2"<<endl;
            continue;
        }

        int typ = 0;
        string str_type = get_type(expression[i] , typ);
        if (typ == 1){
            //making new node
            ExprTreeNode* temp = new ExprTreeNode (str_type , -1);
            //accessing the prevnode
            ExprTreeNode* temp2 = this_code[this_code.size()-1];
            this_code.pop_back();
            temp->left = temp2;
            this_code.push_back(temp);
        }
        else if (typ == 2){
            int t = stoi(expression[i]);
            ExprTreeNode* temp = new ExprTreeNode(str_type , t);
            this_code.push_back(temp);
        }
        else if (typ == 3){
            ExprTreeNode* temp = new ExprTreeNode (str_type , -1);
            temp->id = expression[i];
            this_code.push_back(temp);
        }
    }
    ExprTreeNode* temp2 = this_code[1];
    this_code.pop_back();
    ExprTreeNode* temp = this_code[0];
    temp->right = temp2;
    expr_trees.push_back(this_code[this_code.size()-1]);
    // cout << "size of expr_trees : "<<expr_trees.size()<<endl;
    string s = this_code[this_code.size()-1]->left->type;
    if (s == "VAR"){
        string ins_var = this_code[this_code.size()-1]->left->id;
        symtable->insert(ins_var);
    }
    else if (s == "DEL"){
        string del_var = this_code[this_code.size()-1]->right->id;
        last_deleted = symtable->search(del_var);
        symtable->remove(del_var);
    }    
}

Parser::~Parser(){
    // int s = expr_trees.size();
    // for (int i =0 ;i < s ;i++){
    //     delete expr_trees[i];
    // }
    // // not sure about this...
    // delete symtable;
}

// int main (){
//     Parser* par = new Parser();
//     vector <string> code1 {"pow1", ":=",  "13"};
//     vector <string> code2 {"pow2" ,":=" ,"(", "(" ,"2" ,"*" , "42" ,")" ,"/" ,"(" , "1" ,"*" , "1" , ")" , ")"};
//     vector <string> code3 {"pow3" , ":=","(", "(" ,"3" ,"*" , "42" ,")" ,"/" ,"(" , "pow2" ,"*" , "pow2" , ")" , ")"};
//     vector <string> code4 {"pow4" , ":=","(", "(" ,"4" ,"*" , "42" ,")" ,"/" ,"(" , "pow3" ,"*" , "pow3" , ")" , ")"};
//     vector <string> code5 {"pow5" , ":=","(", "(" ,"5" ,"*" , "42" ,")" ,"/" ,"(" , "pow4" ,"*" , "pow4" , ")" , ")"};
//     vector <string> code6 {"del" ,":=" , "pow3"};
//     vector <string> code7 {"ret" ,":=" , "(" , "pow3","*" ",(" ,"pow2" , "+","78",")",")"};
//     vector <string> code8 {"v", ":=", "(", "(", "3", "*", "2", ")", "+", "(", "10", "*", "11", ")", ")"};

//     vector <vector <string>> testcase;
//     testcase.push_back(code1);
//     testcase.push_back(code8);
//     testcase.push_back(code2);
//     testcase.push_back(code3);
//     testcase.push_back(code4);
//     // testcase.push_back(code5);
//     testcase.push_back(code7);
//     // testcase.push_back(code6);
    
//     for (int i =0 ; i<testcase.size() ;i++){
//         par->parse(testcase[i]);
//         // cout<<"printing symbol table::"<<endl;
//         // inorder_sym(evalu->symtable->get_root());
//         // cout << endl;
//         inorderP (par->expr_trees.back());
//         cout<< endl;
//     }
//     cout<< endl;
//     cout << "size of the symtable : " << par->symtable->get_size() <<endl;
//     // for (int i = 0; i< testcase.size(); i++){
        
//     //     cout << endl;
//     // }
//     // cout << endl;
//     cout<<"printing symbol table::"<<endl;
//     inorder1( par->symtable->get_root());
//     cout << endl;
//     cout << "deleting parser........"<<endl;
//     delete par;
//     cout << "deleted successfully"<<endl;

//     return 0;
// }

// int main(){
// // Statement 1: v := ((3 * 2) + (10 * 11))
// vector<string> token1 = {"v", ":=", "(", "(", "3", "", "2", ")", "+", "(", "10", "", "11", ")", ")"};
// // Statement 2: a := (((3 * v) + 9) / 11)
// vector<string> token2 = {"a", ":=", "(", "(", "(", "3", "*", "v", ")", "+", "9", ")", "/", "11", ")"};
// // Statement 3: b := a
// vector<string> token3 = {"b", ":=", "a"};
// // Statement 4: del := b
// vector<string> token4 = {"del", ":=", "b"};
// // Statement 5: c := ((3 * a) - (2 * v))
// vector<string> token5 = {"c", ":=", "(", "(", "3", "", "a", ")", "-", "(", "2", "", "v", ")", ")"};


// vector<vector<string>>l{token1,token2,token3,token4};

// Parser* p= new Parser();
// for(int i=0;i<l.size();i++){
//     p->parse(l[i]);
//     cout <<"parsing for expression "<<i+1 << " done!" << endl;
//     inorderP(p->expr_trees.back());
//     // cout << endl <<"printing symbol table " << endl;
//     // print2(p->symtable);
// }
//     // for(int i=0;i<p->expr_trees.size();i++){
//     //     inorderP(p->expr_trees[i]);
//     //     cout << endl;
//     // }

//     return 0;
// }

// int main (){
//      Parser* par = new Parser();
//     vector <string> code1 {"pow1", ":=",  "13"};
//     vector <string> code2 {"pow2" ,":=" ,"(", "(" ,"2" ,"*" , "42" ,")" ,"/" ,"(" , "1" ,"*" , "1" , ")" , ")"};
//     vector <string> code3 {"pow3" , ":=","(", "(" ,"3" ,"*" , "42" ,")" ,"/" ,"(" , "pow2" ,"*" , "pow2" , ")" , ")"};
//     vector <string> code4 {"pow4" , ":=","(", "(" ,"4" ,"*" , "42" ,")" ,"/" ,"(" , "pow3" ,"*" , "pow3" , ")" , ")"};
//     vector <string> code5 {"pow5" , ":=","(", "(" ,"5" ,"*" , "42" ,")" ,"/" ,"(" , "pow4" ,"*" , "pow4" , ")" , ")"};
//     vector <string> code6 {"del" ,":=" , "pow3"};
//     vector <string> code7 {"ret" ,":=" , "(" , "pow3","*" ",(" ,"pow2" , "+","78",")",")"};
//     vector <string> code8 {"v", ":=", "(", "(", "3", "*", "2", ")", "+", "(", "10", "*", "11", ")", ")"};

//     vector <vector <string>> testcase;
//     testcase.push_back(code1);
//     testcase.push_back(code8);
//     testcase.push_back(code2);
//     testcase.push_back(code3);
//     testcase.push_back(code4);
//     testcase.push_back(code5);
//     testcase.push_back(code7);
//     testcase.push_back(code6);
    
//     for (int i =0 ; i<testcase.size() ;i++){
//         cout << "size before parsing : " << par->expr_trees.size()<<endl;
//         par->parse(testcase[i]);
//         cout << "size after parsing : " << par->expr_trees.size()<<endl;
//         // cout<<"printing symbol table::"<<endl;
//         // inorder_sym(evalu->symtable->get_root());
//         // cout << endl;
//         inorderP (par->expr_trees.back());
//         cout<< endl;
//     }
//     cout<<"printing symbol table::"<<endl;
//     inorder1( par->symtable->get_root());
//     cout << endl;
//     cout << "deleting parser........"<<endl;
//     delete par;
//     cout << "deleted successfully"<<endl;
    

//     return 0;
// }

void inorderP(ExprTreeNode* Node){
    if(Node== NULL){
        return;
    }
    cout << "(";
    // inorderP(Node->type);
    string op;
    // cout << "type: " << Node->type<<endl;
    if(Node->type == "ADD"){op = "+";}
    if(Node->type == "SUB"){op = "-";}
    if(Node->type == "MUL"){op ="*";}
    if(Node->type == "DIV"){op = "/";}
    if(Node->type == "VAL"){ cout <<Node->num;}
    if(Node->type == "VAR"){op = Node->id;}
    if(Node->type == "DEL"){op = "del";}
    if(Node->type == "RET"){op = "ret";}
    if(Node->type =="START"){op = ":=";}
    cout << op <<"";
    inorderP(Node->right);
    cout << ")";
}

int main(){
    Parser * par = new Parser ();
    vector <string> code1 {"x" , ":=" , "3"};
    vector <string> code2 {"y" , ":=", "2"};
    vector <string> code3 {"z" , ":=", "(" , "x" , "-" , "y" , ")"};
    vector <string> code4 {"ret" , ":=" , "z"};

    vector < vector<string> > testcases;
    testcases.push_back(code1);
    testcases.push_back(code2);
    testcases.push_back(code3);
    testcases.push_back(code4);

    for (int i =0 ; i<testcases.size() ;i++){
        par->parse(testcases[i]);
        // cout<<"printing symbol table::"<<endl;
        // inorder_sym(evalu->symtable->get_root());
        cout << endl;
        inorderP (par->expr_trees.back());
        cout<< endl;
    }
    cout<< endl;
    cout << "size of the symtable : " << par->symtable->get_size() <<endl;
    // for (int i = 0; i< testcase.size(); i++){
        
    //     cout << endl;
    // }
    // cout << endl;
    // cout<<"printing symbol table::"<<endl;
    // inorder1( par->symtable->get_root());
    // cout << endl;
    cout << "deleting parser........"<<endl;
    delete par;
    cout << "deleted successfully"<<endl;

    return 0;
}