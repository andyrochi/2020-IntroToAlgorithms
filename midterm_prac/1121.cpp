#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
bool valid(vector<int>&a, int k, ll len){
    ll point = a[0]+len;
    int used = 1;
    for(int i = 1 ; i < a.size() ; i++){
        if(a[i]>point){
            point = a[i]+len;
            used++;
        }
        if(used>k) break;
    }
    return used <= k;
}
ll bsearch(vector<int>&a,int k){
    ll l=0,r=2*2e30;
    while(l<r){
        ll mid = l+r>>1;
        if(valid(a,k,mid)) r = mid;
        else l = mid+1;
    }
    return l;
}
int main(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto& i: a) cin >> i;
    sort(a.begin(),a.end());
    cout << bsearch(a,k) << endl;
}