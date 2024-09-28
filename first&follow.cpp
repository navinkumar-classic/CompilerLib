#include <iostream>
#include <map>
#include <vector>
#include <cctype>
using namespace std;

vector<char> firsthelp(map<char,vector<string>> prod,char NT){
    vector<char> ans;
    for(int i = 0; i < prod[NT].size(); i++){
        if(!isupper(prod[NT][i][0]))
            ans.push_back(prod[NT][i][0]);
        else{
            vector<char> temp = firsthelp(prod,prod[NT][i][0]);
            for(char p : temp)
                ans.push_back(p);
        }
    }
    return ans;
}
map<char,vector<char>> first(map<char,vector<string>> prod){
    map<char,vector<char>> first;
    map<char,vector<string>>::iterator prodit = prod.begin();
    while (prodit != prod.end()) {
        first[prodit->first] = firsthelp(prod,prodit->first);
        ++prodit;
    }
    return first;
}

int main(){
    map<char,vector<string>> prod;
    prod['S'] = {"TE"};
    prod['E'] = {"+TE","#"};
    prod['T'] = {"FK"};
    prod['K'] = {"*FK","#"};
    prod['F'] = {"a","(S)"};

    map<char,vector<char>> ans = first(prod);
    
    map<char,vector<char>>::iterator it = ans.begin();
    while(it != ans.end()){
        cout<< it->first << " : ";
        for(char j : it->second)
            cout << j << " ";
        cout << endl;
        ++it;
    }
    
    return 0;
}
