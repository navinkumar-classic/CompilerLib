#include <iostream>
#include <map>
#include <vector>
#include <cctype>
#include <set>
using namespace std;

set<char> followhelp(map<char,vector<string>> prod,char NT, map<char,vector<char>> first);

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

set<char> followfirst(map<char,vector<string>> prod, map<char,vector<char>> first, string tmp, char LH,int i){
    set<char> st;
    if(!isupper(tmp[i])){
        st.insert(tmp[i]);
        return st;
    }
    else{
        if(i == tmp.length()){
            set<char> rec = followhelp(prod,LH,first);
            for(char i : rec){
                st.insert(i);
            }
        }
        else{
           for(char j: first[tmp[i]])
            st.insert(j); 
        }
        
    }
    
    return st;
}

set<char> followhelp(map<char,vector<string>> prod,char NT, map<char,vector<char>> first){
    set<char> follow;
    
    map<char,vector<string>>::iterator prodit = prod.begin();
    while (prodit != prod.end()){
        vector<string>::iterator rhs = prodit->second.begin();
        while(rhs != prodit->second.end()){
            string tmp = *rhs;
            for(int i = 0; i < tmp.length(); i++){
                if(tmp[i] == NT){
                    
                    if(i != tmp.length()-1){
                        if(!isupper(tmp[i+1]))
                            follow.insert(tmp[i+1]);
                        else{
                            set<char> rec1 = followfirst(prod,first,tmp,prodit->first,i+1);
                            for(char i : rec1){
                                follow.insert(i);
                            }
                        }
                    }
                    else{
                        if(NT != prodit->first){
                            set<char> rec = followhelp(prod,prodit->first,first);
                            for(char i : rec){
                                follow.insert(i);
                            }
                        }
                    }
                    
                }
            }
            ++rhs;
        }
        ++prodit;
    }
    
    return follow;
}

map<char,set<char>> follow(map<char,vector<string>> prod, map<char,vector<char>> first){
    map<char,set<char>> follow;
    
    map<char,vector<string>>::iterator prodit = prod.begin();
    while (prodit != prod.end()) {
        follow[prodit->first] = followhelp(prod,prodit->first,first);
        ++prodit;
    }
    
    return follow;
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
    
    cout << endl;
    map<char,set<char>> ans1 = follow(prod,ans);
    
    map<char,set<char>>::iterator its = ans1.begin();
    while(its != ans1.end()){
        cout<< its->first << " : ";
        for(char j : its->second)
            cout << j << " ";
        cout << endl;
        ++its;
    }
    
    return 0;
}
