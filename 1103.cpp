#include <iostream>
#include <string>
#include <vector>
#include <map>
#define KEY 1
#define VALUE 2
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        string key;
        string value;
        key.clear();
        value.clear();
        char c;
        map<string,string> dict;
        int mode = KEY;
        getchar();
        while((c=getchar())!='\n'){
            if(c == '{'){
                mode = KEY;
                //cout << c << endl;
                continue;
            }
            if(c == '}'){
                mode = KEY;
                dict[key] = value;
                //cout << key << ":" << value << "\n";
                key.clear();
                value.clear();
                continue;
            }
            if(c == ':'){
                mode = VALUE;
                continue;
            }
            if(c == ','){
                mode = KEY;
                dict[key] = value;
                //cout << key << ":" << value << "\n";
                key.clear();
                value.clear();
                continue;
            }
            if(mode == KEY){
                key.push_back(c);
            }
            else{
                value.push_back(c);
            }
        }

        for( auto const& pair: dict){
            cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
        
        vector<string> newkey, removedkey, changed;

        while((c=getchar())!='\n'){
            if(c == '{'){
                mode = KEY;
                
                continue;
            }
            if(c == '}'){
                mode = KEY;
                dict[key] = value;
                //cout << key << ":" << value << "\n";
                if(dict.find(key)!=dict.end()){
                    if(dict[key] == value){
                        dict.erase(key);
                    }
                    else{
                        changed.push_back(key);
                    }
                }
                else{
                    newkey.push_back(key);
                }
            
                key.clear();
                value.clear();
                continue;
            }
            if(c == ':'){
                mode = VALUE;
                continue;
            }
            if(c == ','){
                mode = KEY;
                dict[key] = value;
                //search
                if(dict.find(key)!=dict.end()){
                    if(dict[key] == value){
                        dict.erase(key);
                    }
                    else{
                        changed.push_back(key);
                    }
                }
                else{
                    newkey.push_back(key);
                }
                key.clear();
                value.clear();
                continue;
            }
            if(mode == KEY){
                key.push_back(c);
            }
            else{
                value.push_back(c);
            }
        }

        if(dict.empty()){
            cout << "No changes" << endl;
        }
        else{
            sort(newkey.begin(),newkey.end());
            sort(removedkey.begin(),removedkey.end());
            sort(changed.begin(),changed.end());
            cout << "+";
            for(int i = 0 ; i < newkey.size() ; i++){
                cout << newkey[i];
                if(i != newkey.size()-1) cout << ",";
                else cout << "\n";
            }
            for(auto const& pair: dict){
                cout <<
            }
            
        }

        cout << endl;
    }
    
    return 0;
}