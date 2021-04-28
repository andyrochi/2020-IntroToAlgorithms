#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define MAX 5001
#define swap(a,b) { a = a + b; b = a - b; a = a - b; }

int parent[MAX];
int csize[MAX];
int check[MAX][MAX] = {0};
int adList[MAX][MAX] = {0}; 

void make_set(int v){
    parent[v] = v;
    csize[v] = 1;
}

int find_set(int v){
    if(v==parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b){
    a = find_set(a);
    b = find_set(b);
    
    if(a!=b){
        if(csize[a]<csize[b]) swap(a,b);
        parent[b] = a;
        csize[a] += csize[b];
        csize[b] = csize[a];
    }
}

void reset(int n){
    for(int i = 0 ; i < n ; i++) make_set(i);
    for(int i = 0 ; i < n ; i++){
        for(int j = i+1; j < n ; j++){
            if(adList[i][j]) union_sets(i,j);
        }
    }
}

int main(){
    int n,m,q;
    cin >> n >> m >> q;
    
    vector<pair<int,int> > input;

    for(int i = 0 ; i < m ; i++){
        int u,v;
        cin >> u >> v;
        adList[u][v]++;
        adList[v][u]++;
    }
    
    for(int k = 0 ; k < q ; k++){
        int i,j;
        cin >> i >> j;
        if(i<0){
            input.push_back({i,j});
            continue;
        }
        else{
            if(adList[i][j]>0){
                input.push_back({i,j});
                adList[i][j]--;
                adList[j][i]--;
            }
        }
    }

    reset(n);
    vector<int>output;
    for(int k = input.size()-1 ; k >= 0 ; k--){
        int i = input[k].first;
        int j = input[k].second;
        if(i < 0){
            output.push_back(csize[find_set(j)]);
        }
        else{
            union_sets(i,j);
        }
    }
    
    for(int i = output.size()-1 ; i >=0 ; i--){
        printf("%d\n", output[i]);
    }
    
}
