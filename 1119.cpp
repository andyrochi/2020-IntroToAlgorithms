#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;
#define P pair<int,int>

int main(){
    int n,s;
    cin >> n >> s;
    vector<int> a(n);
    for(int i = 0 ; i < n ; i++) cin >> a[i];
    unordered_map<int,vector<P> > sums;

    for(int i = 0 ; i < n ; i++){
        for(int j = i+1 ; j < n ; j++){
            int sum = a[i]+a[j];
            sums[sum].push_back({i,j});
        }
    }
    int i = 0,j=0,k=0,l=0;
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            int temp = s;
            temp -= a[i]+a[j];
            //cout <<"i:" << i << ",j:" << j << ",sum:"<< a[i]+a[j] << endl;
            auto dif = sums.find(temp);
            if(dif != sums.end()){
                //cout << "found:" << temp << endl;
                for(int m = 0 ; m < sums[temp].size(); m++){
                    if(sums[temp][m].first > i && sums[temp][m].first > j){
                        k = sums[temp][m].first;
                        l = sums[temp][m].second;
                        break;
                    }
                }
            }
            else{
                break;
            }
            if(l!=0)break;
        }
        if(l!=0)break;
    }

    if(l!=0){
        cout << i << " " << j << " " << k << " " << l << endl;
    }
    else{
        cout << -1 << endl;
    }
    return 0;
}