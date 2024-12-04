/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    // targ is not dynamically defined
    // what is memory size ?
    output_file = ""; // what is this ?
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file = out_file;
    memory_size = mem_limit;
    for (int i = 0; i < memory_size; i++)
    {
        least_mem_loc.push_heap(memory_size - i - 1);
    }
}

void targ_helper (ExprTreeNode* node ,vector<string> & result  , Parser targ){
    if (node->right == NULL || node->left == NULL){
        if (node->type == "VAL"){
            int a = node->num;
            string temp = "PUSH " + to_string (a);
            result.push_back(temp);
            return;
        }
        if (node->type == "VAR"){
            int address = targ.symtable->search(node->id);
            string temp = "PUSH mem[" + to_string (address) + "]";
            result.push_back(temp);
            return;
        }
    }
    targ_helper(node->right , result, targ);
    targ_helper(node->left , result , targ);
    result.push_back(node->type);
}

vector<string> EPPCompiler:: generate_targ_commands(){
    if (targ.expr_trees.size() == 0){
        vector <string> a;
        return a;
    }
    ExprTreeNode* curr = targ.expr_trees.back();
    vector <string> result;
    if (curr->left->type == "DEL"){
        int address = targ.last_deleted ;
        string s = "DEL = mem[" + to_string(address) + "]" ;
        result.push_back(s);
        return result ;
    }
    else if (curr->left->type == "RET"){
        string s = "RET = POP";
        targ_helper (curr->right , result , targ);
        result.push_back(s);
        return result;
    }
    else if (curr->left->type == "VAR"){
        // int address = mem_loc.back();
        // int address = least_mem_loc.get_min();
        int address = targ.symtable->search(curr->left->id);
        string s = "mem[" + to_string(address) + "] = POP";
        targ_helper (curr->right , result , targ);
        result.push_back(s);
        return result;
    }
    else {
        vector <string> a;
        return a;
    }
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream myfile(output_file , ios::app);
    int size = commands.size();
    for(int i = 0 ; i < size ; i++ ){
        myfile << commands[i] << endl;
    }
    myfile.close();
}

void EPPCompiler::compile(vector<vector<string>> code){
    // Parses each input tokenized expression, assigns a memory mapping if the expression is a variable assignment or frees up the memory address if it’s a delete
    // statement and finally compiles the code i.e generates and writes all the targ commands to the output file.

    int sz = code.size();
    
    for (int i = 0 ; i < sz ; i++){
        targ.parse(code[i]);
        ExprTreeNode* temp = targ.expr_trees.back();
        if (temp->left->type == "VAR"){
            targ.symtable->assign_address(temp->left->id , least_mem_loc.get_min());
            vector <string> a = generate_targ_commands();
            
            // mem_loc.pop_back();
            least_mem_loc.pop();

            write_to_file(a);
        }
        else if (temp->left->type == "DEL"){
            int a = targ.last_deleted;
            // mem_loc.push_back(a);
            least_mem_loc.push_heap(a);
            vector <string> c = generate_targ_commands();
            write_to_file(c);
        }
        else if (temp->left->type == "RET"){
            vector <string> res = generate_targ_commands();
            write_to_file(res);
        }
    }
}

EPPCompiler::~EPPCompiler(){
    for (int i = 0 ; i < targ.expr_trees.size() ; i++){
        delete targ.expr_trees[i];
    }
    delete targ.symtable;
}

// int main (){

//     EPPCompiler* comp = new EPPCompiler ("out1.txt" , 8);
    
//     vector <string> code1 {"pow1", ":=",  "13"};
//     vector <string> code2 {"pow2" ,":=" , "(" ,"2" ,"*" , "4" ,")" };
//     vector <string> code3 {"pow3" , ":=","(", "(" ,"3" ,"*" , "42" ,")" ,"/" ,"(" , "pow2" ,"*" , "pow2" , ")" , ")"};
//     vector <string> code4 {"pow4" , ":=","(", "(" ,"4" ,"*" , "42" ,")" ,"/" ,"(" , "pow3" ,"*" , "pow3" , ")" , ")"};
//     vector <string> code5 {"pow5" , ":=","(", "(" ,"5" ,"*" , "42" ,")" ,"/" ,"(" , "pow4" ,"*" , "pow4" , ")" , ")"};
//     vector <string> code6 {"del" ,":=" , "pow3"};
//     vector <string> code7 {"ret" ,":=" , "(" , "pow3","*" ",(" ,"pow2" , "+","78",")",")"};
//     vector <string> code8 {"pow2" ,":=" , "45"};
//     vector <string> code9 {"pow4" ,":=" , "(" , "pow2", "+" ,"56", ")"};

//     vector <vector <string>> testcase;
//     testcase.push_back(code1);
//     testcase.push_back(code2);
//     testcase.push_back(code3);
//     testcase.push_back(code4);
//     testcase.push_back(code5);
//     testcase.push_back(code6);
//     testcase.push_back(code7);
//     testcase.push_back(code8);
//     testcase.push_back(code9);
    
//     comp->compile(testcase);
//     return 0;
// }
