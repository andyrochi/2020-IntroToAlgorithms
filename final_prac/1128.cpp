#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> parent(n);
    vector<int> a(n);
    for(int i = 0 ; i < n ; i++) cin >> a[i];
    parent[0] = -1;
    for(int i = 1 ; i < n ; i++){
        int j = i-1;
        while(parent[j]!=-1){
            if(a[j]>a[i]) break;
            j = parent[j];
        }
        if(a[j]>a[i]) parent[i] = j;
        else parent[i] = -1;
    }
    for(int i = 0 ; i < n; i++){
        if(parent[i]==-1) printf("%d ",-1);
        else printf("%d ",a[parent[i]]);
    }
}