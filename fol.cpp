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

map<char,string> tablehelp(map<char,vector<string>> prod,char NT,map<char,vector<char>> follow){
    map<char,string> ans;
    for(int i = 0; i < prod[NT].size(); i++){
        if(!isupper(prod[NT][i][0])){
            if(prod[NT][i][0] == '#'){
                for(char l : follow[NT])
                    ans[l] = prod[NT][i];
            }
            else
                ans[prod[NT][i][0]] = prod[NT][i];
        }
            
        else{
            vector<char> temp = firsthelp(prod,prod[NT][i][0]);
            for(char p : temp)
                ans[p] = prod[NT][i];
        }
    }
    return ans;
}
map<char,map<char,string>> parsing_table(map<char,vector<string>> prod,map<char,vector<char>> follow){
    map<char,map<char,string>> ptable;
    map<char,vector<string>>::iterator prodit = prod.begin();
    while (prodit != prod.end()) {
        ptable[prodit->first] = tablehelp(prod,prodit->first,follow);
        ++prodit;
    }
    return ptable;
}

int main(){
    map<char,vector<string>> prod;
    prod['S'] = {"TE"};
    prod['E'] = {"+TE","#"};
    prod['T'] = {"FK"};
    prod['K'] = {"*FK","#"};
    prod['F'] = {"a","(S)"};
    
    map<char,vector<char>> follow;
    follow['S'] = {'$',')'};
    follow['E'] = {'$',')'};
    follow['T'] = {'+','$',')'};
    follow['K'] = {'+','$',')'};
    follow['F'] = {'+','*','$',')'};

    map<char,map<char,string>> ans = parsing_table(prod,follow);
    
    map<char,map<char,string>>::iterator ity = ans.begin();
    
    while(ity != ans.end()){
        map<char,string>::iterator itz = ity->second.begin();
        while(itz != ity->second.end()){
            cout << ity->first << " - "<< itz->first << " : " << itz->second << endl;
            ++itz;
        }
        ++ity;
    }
    
    return 0;
}
