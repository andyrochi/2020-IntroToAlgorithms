#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    int n;
    string s1,s2;
    cin >> n >> s1;
    s2 = s1;
    reverse(s2.begin(),s2.end());
    vector<vector<int> > c(n+1);
    for(int i = 0 ; i < n+1 ; i++) c[i].resize(n+1);
    for(int i = 1 ; i < n+1 ; i++ ){
        for(int j = 1 ; j < n+1 ; j++){
            if(s1[i-1]==s2[j-1]){
                if(i==1||j==1) c[i][j]=1;
                else c[i][j] = c[i-2][j-2] + 1;
            }
            else{
                c[i][j] = max(c[i-1][j],c[i][j-1]);
            }
        }
    }
    cout << c[n][n] << endl;
    return 0;
}