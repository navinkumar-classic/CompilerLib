#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<string> adv_tokenizer(string s, char del){
    vector<string> ans;
    stringstream ss(s);
    string word;
    while (!ss.eof()) {
        getline(ss, word, del);
        ans.push_back(word);
    }
    
    return ans;
}

string getS(char x){
    string s(1, x);
    return s;  
}

int isop(char x){
    switch(x){
        case '(':
            return 3;
        case ')':
            return 3;
        case '/':
            return 2;
        case '*':
            return 2;
        case '-':
            return 1;
        case '+':
            return 1;
        default:
            return 0;
    }
}

vector<string> postfix(string s){
    vector<string> ans;
    stack<char> stk;
   
    for(char i : s){
        if (isop(i) == 0)
            ans.push_back(getS(i));
        else{
            if(i == '('){
                stk.push(i);
            }
            else if(i == ')'){
                while(stk.size() > 0 && stk.top() != '('){
                    ans.push_back(getS(stk.top()));
                    stk.pop();
                }
                if(stk.size() == 0){
                    return {"error in input"};
                }
                stk.pop();
            }
            else if(stk.size() == 0)
                stk.push(i);
            else{
                while(stk.size() > 0 && isop(stk.top()) >= isop(i) && stk.top() != '('){
                    ans.push_back(getS(stk.top()));
                    stk.pop();
                }
                stk.push(i);
            }
           
        }
    }
   
    while(stk.size() > 0){
        ans.push_back(getS(stk.top()));
        stk.pop();
    }
   
   
    return ans;
}

vector<vector<string>> inter(vector<string> s,string lhs){
    vector<vector<string>> ans;
    
    int t = 0;
    int id = 0;
    stack<string> navin;
    cout << "Intermediate Code: " << endl;
    for(string i : s){
        if (isalnum(i[0])){
            navin.push(i);
        }
        else{
            vector<string> temp;
            string o2 = navin.top();navin.pop();
            string o1 = navin.top();navin.pop();
            cout << "t" << t << " = " << o1 << i << o2 << endl;
            string n = "t"+to_string(t);
            navin.push(n);
            
            temp = {i,o1,o2,n};
            ans.push_back(temp);
            t += 1;
        }
    }
    cout << lhs << " = " << "t" << t-1 << endl;
    string n = "t"+to_string(t-1);
    vector<string> tmp= {"=",n,"",lhs};
    ans.push_back(tmp);
    
    return ans;
}

string provideInst(string op){
    if(op == "+") return "ADD ";
    else if(op == "-") return "SUB ";
    else if(op == "*") return "MUL ";
    else if(op == "/") return "DIV ";
    
    return "";
}

void machine_code(vector<vector<string>> quad){
    
    cout << "Machine Code: " << endl;
    
    for(int i = 0; i < quad.size(); i++){
        
        if(quad[i][0] != "="){
            cout << "MOV " << quad[i][1] << "," << "R0" << endl;
            cout << provideInst(quad[i][0]) << quad[i][2] << "," << "R0" << endl;
            cout << "MOV " << "R0" << "," << quad[i][3] << endl;
        }
        else{
            cout << "MOV " << quad[i][1] << "," << quad[i][3] << endl;
        }
    }
    
}

int main(){
    cout << "Enter the expression(no space): ";
    string expression; cin >> expression;
    vector<string> expr = adv_tokenizer(expression,'=');
    
    vector<string> post = postfix(expr[1]);
    vector<vector<string>> quad = inter(post,expr[0]);
    cout << endl;
    machine_code(quad);

    return 0;
}
