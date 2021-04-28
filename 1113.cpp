#include <iostream>
#include <vector>
#include <string>
using namespace std;

int test(vector<int>& words, int value){
    int rows = 24;
    int cur = value;
    for(int i = 0 ; i < words.size() ; ){
        if(cur>=words[i]){
            cur-=words[i];
            if(cur<=1){
                if(i!=words.size()-1) rows--;
                if(rows<=0) break;
                cur=value;
            }
            else cur-=1; //blank
            i++;
        }
        else{
            rows--;
            if(rows<=0)break;
            cur = value;
        }
    }
    if(rows<=0) return -1;
    return 1;
}

int bsearch(vector<int>& words, int l, int r){
    int mid = (l+r)/2;
    while(l<r){
        mid = (l+r)/2;
        int t = test(words,mid);
        if(t<0) l = mid+1;
        else r = mid;
    }
    return l;
}

int main(){

    int n;
    cin >> n;
    vector<int> words;
    while(n--){
        string s;
        cin >> s;
        words.push_back(s.length());
    }
    int ans = bsearch(words,0,200001);
    cout << ans << endl;
    return 0;
}