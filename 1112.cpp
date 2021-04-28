#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;
const double E = std::exp(1.0);

double W(double y) {
    ll l = 0, r = 1e16;
    ll mid = (l+r)/2;
    while(l<r){
        mid = (l+r)/2;
        double val = (double)mid/1e7;
        if(val*pow(E,val)>=y) r = mid;
        else l = mid+1;
    }
    return (double)l/1e7;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        double y;
        cin >> y;
        cout << fixed << setprecision(12) << W(y) << '\n';
    }
    return 0;
}