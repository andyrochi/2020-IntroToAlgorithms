#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define mod 1000000007
vector<ll> solve(vector<ll> x, int n) {
    // TODO
    x[0] %= mod;
    x[1] %= mod;
    if(n==0) return {1,0};
    if(n==1){
        return x;
    }
    vector<ll> half = solve(x,n/2);
    ll a = (half[0]*half[0])%mod - (half[1]*half[1])%mod;
    a = (a<0)?(a+mod):a;
    vector<ll> whole = {a,2*((half[0]*half[1])%mod)%mod};
    if(n%2){
        ll ans = (whole[0]*x[0])%mod - (whole[1]*x[1])%mod;
        ans = (ans+mod)%mod;
        return {ans, ((whole[0]*x[1])%mod+(whole[1]*x[0])%mod)%mod};
    }
    else{
        return whole;
    }
    
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        ll a, b, n;
        cin >> a >> b >> n;  // (a + bi)^n
        vector<ll> ans = solve({a, b}, n);
        cout << ((ans[0]<0)?(ans[0]+mod):ans[0]) << ' ' << ans[1] << '\n';
    }
    return 0;
}