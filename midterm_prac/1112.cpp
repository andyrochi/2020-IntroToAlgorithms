#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define ll long long
const double E = exp(1.0);
double bsearch(int y){
    ll l = 0,r=1e16;
    while(l<r){
        ll mid = (l+r)/2;
        //cout << mid << " ";
        double x = mid/1e12;
        if(x*pow(E,x)<y) l = mid+1;
        else r = mid;
    }
    //cout << l << endl;
    return (double)l/1e12;
}
int main(){
    int t,y;
    cin >> t;
    while(t--){
        cin >> y;
        cout << fixed << setprecision(12) << bsearch(y) << endl;
    }

    return 0;
}