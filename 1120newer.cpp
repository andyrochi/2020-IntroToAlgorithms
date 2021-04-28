#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> lds1,lds2,cur; //lds1 is -2 lds2 is -1
    int flag = -1;
    int ans = 0;
    for(int i = 0 ; i < n ; i++ ){
        vector<int> temp;
        //find matches
        for(int j = n-1 ; j > i+1 ; j--)
            if(s[i]==s[j]) temp.push_back(j);
        
        //if first
        if(i==0){
            if(!temp.empty()){ 
                lds1.push_back(temp[0]);
                flag = i;
            }
        }
        //if second
        else if(i==1){
            lds2 = lds1;
            if(!temp.empty()){
                
                if(lds2.empty())
                    lds2.push_back(temp[0]);
                else{
                    if(temp[0]>lds2[0]) lds2[0] = temp[0];
                }
                flag = i;
            }
        }
        //others
        else{
            cur = lds2;
            bool modify = false;
            //found something
            if(!temp.empty()){

                if(!lds1.empty()){
                    int ldIndex = lds1.size()-1;
                    int addIndex = -1;
                    int replaceIndex = -1;
                    for(int k = 0 ; k < temp.size() ; k++){
                        //check if can append
                        //if match can be appended to the last of lds1 ->append
                        if(lds1[ldIndex]-temp[k]>1){
                            if(temp[k]>addIndex) addIndex = temp[k];
                        }
                        //if match cannot be appended -> check if can replace
                        else{
                            if(lds1.size()>1){
                                if(temp[k]>lds1[ldIndex]&& lds1[ldIndex-1]-temp[k]>1){
                                    if(temp[k]>replaceIndex) replaceIndex = temp[k];
                                }
                            }
                            else{
                                if(temp[k]>lds1[ldIndex]){
                                    if(temp[k]>replaceIndex) replaceIndex = temp[k];
                                }
                            }
                        }
                        if(addIndex != -1){
                            lds1.push_back(addIndex);
                            modify = true;
                            flag = i;
                            
                        }
                        else if(replaceIndex!=-1){ 
                            lds1[ldIndex] = replaceIndex;
                            modify = true;
                            flag = i;
                        }//
                    }
                }
                else{
                    lds1.push_back(temp[0]);
                    modify =true;
                    flag = i;
                }
                if(modify){
                    cur = lds1;
                }
            }
            lds1 = lds2;
            lds2 = cur;
            cur.clear();
        }
    }
    if(lds2.size()==0) cout << 1 << endl;
    else{
        if(lds2[lds2.size()-1]-flag > 3) cout << lds2.size()*2+1 << endl;
        else cout << lds2.size()*2 << endl;
    }
    
}