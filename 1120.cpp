#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
using namespace std;

int main(){
    int n;
    cin >> n;
    string s;
    vector<int> length(n),palPos(n),appPos(n);
    unordered_map<char,int> prevPos; 
    cin >> s;
    
    for(int i = 0 ; i < n ; i++){
        int palPosC = -1;
        int searchStart = n;
        if(prevPos.find(s[i])!=prevPos.end()){
            searchStart = prevPos[s[i]];
        }
        //problems to deal with, same character will choose same palPos 
        for(int j = searchStart-1; j > i+1 ; j--){
            if(s[i]==s[j]){
                palPos[i] = j;
                palPosC = j;
                prevPos[s[i]] = j;
                break;
            }
        }
        if(palPosC==-1){
            palPos[i] = palPosC;
            appPos[i] = -1;
            continue;
        }
        int maxLength=0,maxIndex=-1;
        //find best position to append to
        for(int k = 0; k < i-1; k++){
            //if appendable
            if(palPos[k]!=-1){
                //check right part
                if(palPos[k]-palPosC>1){//can append
                    if(length[k]>maxLength){
                        maxLength = length[k];
                        maxIndex = k;
                    }
                    
                }
            }
        }
        //append pos not found, I'm the beginning
        if(maxIndex==-1){
            length[i] = 1;
            appPos[i] = -1;
        }
        //append position found
        else{
            length[i] = maxLength+1;
            appPos[i] = maxIndex;
        }
    }

    int outputIndex = 0, max = 0;
    for(int i = 0 ; i < n ; i++) cout << setw(4) << i << " ";
    cout << "\n";
    for(int i = 0 ; i < n ; i++) cout << setw(4) << s[i] << " ";
    cout << "\n";
    for(int i = 0 ; i < n ; i++) cout << setw(4) << palPos[i] << " ";
    cout << "\n";
    for(int i = 0 ; i < n ; i++) cout << setw(4) << appPos[i] << " ";
    cout << "\n";
    for(int i = 0 ; i < n ; i++) cout << setw(4) << length[i] << " ";
    cout << "\n";

    for(int i = 0 ; i < n ; i++){
        //cout << length[i] << " ";
        if(length[i]>max){
            max = length[i];
            outputIndex = i;
        }
    }
    //cout << endl;
    if(max == 0) cout << 1 << endl;
    else{
    if(palPos[outputIndex]-outputIndex > 3)
        cout << max*2 + 1 << endl;
    else
        cout << max*2 << endl;
    }
    //cout << endl << max*2 << endl;
    
}