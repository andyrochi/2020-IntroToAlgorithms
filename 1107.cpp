#include <iostream>
using namespace std;

int soda(int n, int k){
    int ans = 0;
    while(true){
        int bottles;
        bottles = n/k;
        if(bottles == 0) break;
        ans += bottles;
        n -= (k-1)*bottles;
    }
    return ans;
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        cout << soda(n,k) << '\n';
    }
    return 0;
}