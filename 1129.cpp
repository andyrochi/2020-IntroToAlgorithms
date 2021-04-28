#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <utility>
using namespace std;
#define MAX 5000
#define swap(a,b) { a = a + b; b = a - b; a = a - b; }

int parent[MAX];
int csize[MAX];
int input[500000][2];
int check[MAX][MAX] = {0};
int cnt[MAX][MAX] = {0};

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
    }
}

class Graph{
public:
Graph(){

}
Graph(int size){
    adList.resize(size);
    for(int i = 0 ; i<size;i++) adList[i].resize(size);
}
vector<vector<int> > adList;
};

void reset(Graph& graph, int n){
    for(int i = 0 ; i < n ; i++) make_set(i);
    for(int i = 0 ; i < n ; i++){
        for(int j = i+1; j < n ; j++){
            if(graph.adList[i][j]>0&&(find_set(i)!=find_set(j))) union_sets(i,j);
        }
    }
}

int main(){
    int n,m,q;
    cin >> n >> m >> q;
    Graph graph(n);
    
    for(int i = 0 ; i < m ; i++){
        int u,v;
        cin >> u >> v;
        graph.adList[u][v]++;
        graph.adList[v][u]++;
    }
    
    for(int k = 0 ; k < q ; k++){
        int i,j;
        cin >> i >> j;
        input[k][0]=i;
        input[k][1]=j;
        if(i<0){
            continue;
        }
        else{
            cnt[i][j]++;
            cnt[j][i]++;

            if(graph.adList[i][j]>0){
                graph.adList[i][j]--;
                graph.adList[j][i]--;
                check[i][j]++;
                check[j][i]++;
            }
        }
    }

    reset(graph,n);
    vector<int>output;
    for(int k = q-1 ; k >= 0 ; k--){
        int i = input[k][0];
        int j = input[k][1];
        if(i < 0){
            output.push_back(csize[parent[j]]);
        }
        else{
            if(check[i][j]>0){
                if(cnt[i][j]>check[i][j]){
                    cnt[i][j]--;
                    cnt[j][i]--;
                    continue;
                }
                cnt[i][j]--;
                cnt[j][i]--;
                check[i][j]--;
                check[j][i]--;
                union_sets(i,j);
            }
        }
    }
    
    for(int i = output.size()-1 ; i >=0 ; i--){
        printf("%d\n", output[i]);
    }
    
}
