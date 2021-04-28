#include <iostream>
#include <cstdio>
#include <vector>
#define Tie std::cin.sync_with_stdio(0),std::cin.tie(0);
using namespace std;
int main(){Tie

    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> trace(n);
    for(int i = 0 ; i < n ; i++) cin >> a[i];
    int max = a[0];
    for(int i = 0 ; i < n ; i++){
        //printf("i=[%d]:", i);
        if(a[i]>=max){
            cout << -1 << ' ';
            max = a[i];
        }
        else{
            int j = i-1;
            while(j>=0){
                if(a[j]>a[i]){
                    cout << a[j] << ' ';
                    trace[i] = j;
                    break;
                }
                else{
                    j = trace[j];
                }
            }
        }
    }

}