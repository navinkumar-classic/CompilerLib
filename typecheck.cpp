#include <iostream>
#include <map>
#include <vector>
using namespace std;

int precedence(string type){
    if(type == "real") return 2;
    else if(type == "int") return 1;
    return 0;
}
int main(){
    
    map<char,string> type;
    cout << "Enter the number of variables: ";
    int a; cin >> a;
    
    cout << "Enter the variable followed by the type(seperated with space): " << endl;
    for(int i = 0; i < a; i++){
        char ctemp;cin >> ctemp;
        string stemp;cin >> stemp;
        type[ctemp] = stemp;
    }
    
    bool flag = true;
    cout << "Enter the number of expression: ";
    int b; cin >>b;
    cout << "Enter the 3AC expression(with no space eg a=b+c): " << endl;
    for(int i = 0; i < b; i++){
        string pro; cin >> pro;
        char lhs = pro[0],rhs1 = pro[2],rhs2 = pro[4];
        string correct;
        if(precedence(type[rhs1]) >= precedence(type[rhs2]))
            correct = type[rhs1];
        else correct = type[rhs2];
        
        if(correct != type[lhs] && precedence(correct) > precedence(type[lhs])){
            flag = false;
            cout << lhs << " should be of " << correct << " type." << endl;
        }
            
    }
    
    if(flag){ cout << "Correct"; }
    return 0;
}
