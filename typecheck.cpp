#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

string getS(char x){
    string s(1, x);
    return s;  
}

int precedence(string type){
    if(type == "real") return 3;
    else if(type == "long") return 2;
    else if(type == "int") return 1;
    return 0;
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

void inter(vector<string> s,map<string,string> typeMap,string lhs){
    int t = 0;
    int id = 0;
    stack<string> navin;
    for(string i : s){
        if (isalnum(i[0])){
            navin.push(i);
        }
        else{
            string o2 = navin.top();navin.pop();
            string o1 = navin.top();navin.pop();
            string o3 = "t"+to_string(t);
            
            if(precedence(typeMap[o1]) >= precedence(typeMap[o2]))
                typeMap[o3] = typeMap[o1];
            else typeMap[o3] = typeMap[o2];
            
            navin.push(o3);
            t += 1;
        }
    }
    
    string correct = typeMap[navin.top()];
    string observed = typeMap[lhs];
    
    if(precedence(correct) <= precedence(observed)){
        cout << "Correct";
        return;
    }
    cout << lhs << " should be of " << correct << " type.";
}

int main(){
    cout << "Enter the number of variables: ";
    int num; cin >> num;
    map<string,string> typeMap;
    
    cout << "Enter the variable and type(with space-(int,real,long)): " << endl;
    
    for(int i = 0; i < num; i++){
        string var,type;
        cin >> var; cin >> type;
        typeMap[var] = type;
    }
    
    cout << "Enter the LHS of the expression: ";
    string a; cin >> a;
    cout << "Enter a RHS of the expression (no space): ";
    string s; cin >> s;
    vector<string> ans = postfix(s);
  
    inter(ans,typeMap,a);
   
    return 0;
}
