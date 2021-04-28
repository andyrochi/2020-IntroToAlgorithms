#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int MAXM =100005;
const int MAXN =1005;
int dp[MAXN][2*MAXM];
int main(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n+1);
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
    }
    
    for(int i = 0 ; i <= n ; i++)
        dp[i][0] = 1;
    
    int x = k*n; //without adding any a
    int v = m-x; //target after subtracting x
    if(v<=0) printf("%d\n",-v);
    else{
        for(int i = 1; i <= n ; i++){
            for(int j = 1 ; j <= 2*v ; j++){
                if(dp[i-1][j]==1) dp[i][j]=1;
                else if((j-a[i]*(n-i+1))>=0){
                    dp[i][j] = dp[i-1][j-a[i]*(n-i+1)];
                }
            }
        }
    
        int min = 1e5;
        for(int i = 0 ; i <= 2*v ; i++){
            //can do
            if(dp[n][i]){
                int dif = i-v;
                if(dif<0) dif=-dif;
                if(dif<min) min=dif;
            }
        }
        cout << min << '\n';
    }
    
}