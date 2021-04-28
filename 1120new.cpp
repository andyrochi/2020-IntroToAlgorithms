#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    string s1,s2;
    cin >> s1;
    s2 = s1;
    reverse(s2.begin(),s2.end());
    vector< vector<int> > dp;
    dp.resize(n+1);
    for(int i = 0 ; i < n+1 ; i++) dp[i].resize(n+1);
    for(int i = 0 ; i < n+1 ; i++){ dp[0][i]=0; dp[i][0] = 0;}
    
    for(int i = 1 ; i < n+1 ; i++ ){
        for(int j = 1 ; j < n+1 ; j++ ){
            if(s1[i-1]==s2[j-1]){
                if(i==1||j==1) dp[i][j] = 1;
                else dp[i][j] = dp[i-2][j-2] + 1;
            }
            else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
        }
    }
    cout << dp[n][n] << endl;
}