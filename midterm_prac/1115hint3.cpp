#include <iostream>
#include <algorithm>
using namespace std;
#define myMax(x,y,z) max(x,max(y,z))

int tree[50000<<2]={0};
int a[50000]={0};
void build(int v,int tl,int tr){
    if(tl==tr) return tree[v] = a[tl],void();
    int mid = tl+tr>>1;
    build(v<<1,tl,mid);
    build(v<<1|1,mid+1,tr);
    tree[v] = myMax(tree[v<<1],tree[v<<1|1],tree[v<<1]+tree[v<<1|1]);
}
void update(int i,int v,int tl,int tr,int val){
    if(tl==tr) return tree[v] = val,void();
    int mid = tl+tr>>1;
    if(i<=mid) update(i,v<<1,tl,mid,val);
    else       update(i,v<<1|1,mid+1,tr,val);
    tree[v] = myMax(tree[v<<1],tree[v<<1|1],tree[v<<1]+tree[v<<1|1]);
}
int query(int v,int l, int r, int tl, int tr){
    if(l==tl&&r==tr) return tree[v];
    int mid = tl+tr>>1;
    if(l>mid) return query(v<<1|1,l,r,mid+1,tr);
    if(r<=mid) return query(v<<1,l,r,tl,mid);
    int left = query(v<<1,l,mid,tl,mid), right = query(v<<1|1,mid+1,r,mid+1,tr);
    return myMax(left,right,left+right);
}
int main(){
    int n,m;
    cin >> n;
    for(int i = 0 ; i < n ; i++) cin >> a[i];
    build(1,0,n-1);
    cin >> m;
    while(m--){
        int op,x,y;
        cin >> op >> x >> y;
        if(op==0){
            update(x-1,1,0,n-1,y);
        }
        else{
            cout << query(1,x-1,y-1,0,n-1) << endl;
        }
    }
}