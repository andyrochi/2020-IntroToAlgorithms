#include <iostream>
#include <vector>
using namespace std;
#define ll long long
#define MOD 1000000007

vector<ll> solve(vector<ll> org,int pow){
    if(pow==0) return {1,0};
    vector<ll>half = solve(org, pow/2);
    vector<ll>whole = {((half[0]%MOD)*(half[0]%MOD)%MOD-(half[1]%MOD)*(half[1]%MOD)%MOD+MOD)%MOD,(2*(((half[0]%MOD)*(half[1]%MOD))%MOD))%MOD};
    if(pow%2) return {((whole[0]%MOD)*(org[0]%MOD)%MOD-(whole[1]%MOD)*(org[1]%MOD)%MOD+MOD)%MOD,((((whole[0]%MOD)*(org[1]%MOD))%MOD)+(((whole[1]%MOD)*(org[0]%MOD))%MOD))%MOD};
    return whole;
}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);

    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int a, b, n;
        cin >> a >> b >> n;  // (a + bi)^n
        vector<ll> ans = solve({a, b}, n);
        cout << ans[0] << ' ' << ans[1] << '\n';
    }
    return 0;
}