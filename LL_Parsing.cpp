#include <iostream>
#include <map>
#include <stack>
#include <cctype>
using namespace std;

void parsing(map<char,map<char,string>> ptable,string input){
    stack<char> stk; stk.push('S');
    int point = 0;
    while(point < input.length()){ //&& input[point] != '$'
        if(stk.size() == 0)
            break;
        else if(stk.top() == '#')
            stk.pop();
        else if(islower(stk.top())){
            if(stk.top() == input[point]){
                point++;stk.pop();
            }
            else
                break;
        }
        else{
            if(ptable.find(stk.top()) != ptable.end()){
                if(ptable[stk.top()].find(input[point]) != ptable[stk.top()].end()){
                    string temp = ptable[stk.top()][input[point]];stk.pop();
                    for(int i = temp.length() - 1; i >= 0; i--){
                        stk.push(temp[i]);
                    }
                }
                else
                    break;
            }
            else
                break;
        }
    }
    if(input[point] == '$')
        cout << "Parsing Successful";
    else
        cout << "Parsing Unsuccessful";
    return;
}

int main(){
    map<char,map<char,string>> pta;
    pta['S']['a'] = "aB";
    pta['B']['b'] = "bC";
    pta['C']['c'] = "cS";
    pta['S']['$'] = "#";
    pta['B']['$'] = "#";
    pta['C']['$'] = "#";
    parsing(pta,"abcabcad$");

    return 0;
}
