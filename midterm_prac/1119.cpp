#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define p pair<int,int>
#define mp make_pair
int main(){
    int n,s;
    cin >> n >> s;
    vector<int> a(n);
    for(auto &i: a) cin >> i;
    unordered_map<int,vector<p> > search;
    for(int i = 0 ; i < n ; i++ )
        for(int j = i+1 ; j < n ; j++){
            int tempSum = a[i] + a[j];
            search[tempSum].push_back(mp(i,j));
        }
    
    int fir=0,sec=0,thi=0,fou=0;
    for(int i = 0 ; i < n ; i++){
        fir = i;
        for(int j = i+1 ; j < n ; j++){
            sec = j;
            int left = s - (a[i]+a[j]);
            if(search.find(left)!=search.end()){
                for(int k = 0 ; k < search[left].size(); k++ ){
                    if(search[left][k].first>sec){
                        thi = search[left][k].first;
                        fou = search[left][k].second;
                        break;
                    }
                }
            }
            if(fou!=0) break;
        }
        if(fou!=0) break;
    }
    if(fou==0) cout << -1 << endl;
    else cout << fir << " " << sec << " " << thi << " " << fou << endl;
    return 0;
}