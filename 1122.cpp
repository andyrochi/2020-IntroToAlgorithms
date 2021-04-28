#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int dp1[501][501]={0};
int dp2[501][501]={0};
int main(){
    int n,W,V;
    cin >> n >> W >> V;
    vector<int> wt(n+1);
    vector<int> vol(n+1);
    vector<int> prof(n+1);
    for(int i = 1 ; i <= n ; i++){
        cin>>wt[i]>>vol[i]>>prof[i];
    }
    int (*dpcur)[501]= dp2;
    int (*dplast)[501] = dp1;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1; j <= V ; j++){
            for(int k = 1 ; k <= W ; k++){
                if(wt[i]>k || vol[i]>j) dpcur[j][k] = dplast[j][k];
                else dpcur[j][k] = max(dplast[j][k],prof[i]+dplast[j-vol[i]][k-wt[i]]);
            }
        }
        swap(dpcur,dplast);
    }
    cout << dpcur[V][W] << endl;
    return 0;
}