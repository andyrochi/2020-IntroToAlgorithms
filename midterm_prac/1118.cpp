#include <iostream>
#include <vector>
using namespace std;
int tree[500001<<2];

void build(vector<int>& a,int v,int tl,int tr){
    if(tl==tr) return tree[v]=a[tl],void();
    int mid = tl+tr>>1;
    build(a,v<<1,tl,mid);
    build(a,v<<1|1,mid+1,tr);
    tree[v] = tree[v<<1] + tree[v<<1|1];
}
void update(int i,int v,int tl,int tr, int val){
    if(tl==tr) return tree[v] = val,void();
    int mid = tl+tr>>1;
    if(i<=mid) update(i,v<<1,tl,mid,val);
    else update(i,v<<1|1,mid+1,tr,val);
    tree[v] = tree[v<<1]+tree[v<<1|1];
}
int query(int v,int l, int r, int tl, int tr){
    if(tl==l&&tr==r) return tree[v];
    int mid = tl+tr>>1;
    if(r <= mid) return query(v<<1,l,r,tl,mid);
    if(l > mid) return query(v<<1|1,l,r,mid+1,tr);
    return query(v<<1,l,mid,tl,mid)+query(v<<1|1,mid+1,r,mid+1,tr);
}
int main(){
    int n,m;
    cin >> n>>m;
    vector<int>a(n);
    for(auto& i: a) cin >> i;
    build(a,1,0,n-1);
    while(m--){
        int op,j,k;
        cin >> op >> j >> k;
        if(op==0){
            update(j,1,0,n-1,k);
        }
        else{
            if(j<=k) cout << query(1,j,k,0,n-1) << endl;
            else cout << query(1,j,n-1,0,n-1) + query(1,0,k,0,n-1) << endl;
        }
    }
}
