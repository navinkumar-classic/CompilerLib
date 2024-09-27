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

void inter(vector<string> s){
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
            cout << "t" << t << " = " << o1 << i << o2 << endl;
            string n = "t"+to_string(t);
            navin.push(n);
            t += 1;
        }
    }
}
int main(){
    cout << "Enter a String(no space): ";
    string s;
    cin >> s;
    vector<string> ans = postfix(s);
    int u = 1;
    map<string,string> kl;
   
    for(int i = 0; i < ans.size(); i++){
        if(isalpha(ans[i][0])){
            if(kl.find(ans[i]) == kl.end()){
                string og = ans[i];
                ans[i] = "id" + to_string(u++);
                kl[og] = ans[i];
            }
            else{
                ans[i] = kl[ans[i]];
            }
        }
    }
   
    cout << endl << "Identifier: " << endl;
   
    map<string, string>::iterator iter;
    for (iter = kl.begin(); iter != kl.end(); ++iter) {
        cout << iter->first << " - " << iter->second << endl;
    }
    
    cout << endl << "The Postfix Expession: " << endl;
    
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
   
    cout << endl <<endl << "The Intermediate Code: " << endl;
    inter(ans);
   
    return 0;
}
