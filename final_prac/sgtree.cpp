#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 500005;
int tree[MAXN<<2];

void build(int v,int tl,int tr,vector<int>& a){
    if(tl==tr) return tree[v] = a[tl],void();
    int mid = tl+tr>>1;
    build(v<<1,tl,mid,a);
    build(v<<1|1,mid+1,tr,a);
    tree[v] = tree[v<<1] + tree[v<<1|1];
}

void update(int v,int tl,int tr,int i,int val){
    if(tl==tr) return tree[v]=val,void();
    int mid = tl+tr>>1;
    if(i <= mid) update(v<<1,tl,mid,i,val);
    else update(v<<1|1,mid+1,tr,i,val);
    tree[v] = tree[v<<1] + tree[v<<1|1];
}

int query(int v,int tl,int tr,int l,int r){
    if(l==tl&&r==tr) return tree[v];
    int mid = tl+tr>>1;
    if(r<=mid) return query(v<<1,tl,mid,l,r);
    else if(l>mid) return query(v<<1|1,mid+1,tr,l,r);
    //r > mid && l <= mid
    return query(v<<1,tl,mid,l,mid) + query(v<<1|1,mid+1,tr,mid+1,r);
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0 ; i < n ; i++) cin>>a[i];
    build(1,0,n-1,a);
    while(m--){
        int i,j,k;
        cin >> i >> j >> k;
        if(i==0){
            update(1,0,n-1,j,k);
        }
        else{
            int ans;
            if(j>k){
                ans = query(1,0,n-1,j,n-1) + query(1,0,n-1,0,k);
            }
            else ans = query(1,0,n-1,j,k);
            printf("%d\n",ans);
        }
    }
}