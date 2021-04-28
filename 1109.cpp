#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int findSingleton(vector<int> &a) {
    // TODO
    int ans;
    sort(a.begin(),a.end()); //nlgn
    for(int i = 0 ; i < a.size() ;){
        if(a[i] == a[i+1]){
            i += 2;
        }
        else{
            return a[i];
        }
    }
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> a(2 * n - 1);
    for (int &x : a) {
        cin >> x;
    }
    cout << findSingleton(a) << '\n';
}