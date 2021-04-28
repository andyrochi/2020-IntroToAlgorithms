#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

int valid(vector<int>& p, int k, ll test){
    int i = 0;
    k--;
    ll val = p[0] + test;
    while(i < p.size()){
        if(p[i]<=val){
            i++;
            continue;
        }
        val= p[i] + test;
        i++;
        k--;
        if(k<0) break;
    }
    return k;
}

ll bsearch(vector<int>& p, int k){
    ll l = 0;
    ll r = 2*2E30;
    while(l<r){
        ll mid = (l+r)/2;
        if(valid(p,k,mid)>=0) r = mid;
        else l = mid+1;
    }
    return l;
}
int main(){
    int n,k;
    cin >> n >> k;
    vector<int> p(n);
    for(int i = 0 ; i < n ; i++) cin>>p[i];
    sort(p.begin(),p.end());
    cout << bsearch(p,k) << endl;

}