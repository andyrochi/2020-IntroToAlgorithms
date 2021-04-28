#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 500050
#define myMax(x,y,z,w) max(max(x,y),max(z,w))
struct node{
    node(){
        yy=0;
        yn=0;
        ny=0;
        nn=0;
    }
    int yy,yn,ny,nn;
}E[MAX<<2];
int a[MAX];

void pushup(int v){
    int lc = v<<1,rc=v<<1|1;
    E[v].nn = max(E[lc].nn+E[rc].yn,E[lc].ny+E[rc].nn);
    E[v].nn = max(E[v].nn, E[lc].nn+E[rc].nn);
    E[v].ny = max(E[lc].ny+E[rc].ny, E[lc].nn+E[rc].ny);
    E[v].ny = max(E[v].ny, E[lc].nn+E[rc].yy);
    E[v].yn = max(E[lc].yy+E[rc].nn, E[lc].yn+E[rc].yn); 
    E[v].yn = max(E[v].yn, E[lc].yn + E[rc].nn);
    E[v].yy = max(E[lc].yy+E[rc].ny, E[lc].yn+E[rc].yy); 
    E[v].yy = max(E[v].yy, E[lc].yn + E[rc].ny);
}

void build(int v,int tl,int tr){
    if(tl==tr){
        E[v].yy = a[tl];
        return;
    }
    int mid=tl+tr>>1;
    build(v<<1,tl,mid);
    build(v<<1|1,mid+1,tr);
    pushup(v);
}

void update(int i,int v,int tl, int tr, int val){
    if(tl==tr) return E[v].yy = val, void();
    int mid = tl+tr>>1;
    if(i<=mid) update(i,v<<1,tl,mid,val);
    else       update(i,v<<1|1,mid+1,tr,val);
    pushup(v);
}

node query(int v,int l,int r,int tl,int tr){
    if(tl==l&&tr==r) return E[v];
    int mid = tl+tr>>1;
    if(r<=mid) return query(v<<1,l,r,tl,mid);
    if(l>mid)  return query(v<<1|1,l,r,mid+1,tr);
    node lc = query(v<<1,l,mid,tl,mid), rc = query(v<<1|1,mid+1,r,mid+1,tr);
    node res;
    res.nn = max(lc.nn+rc.yn,lc.ny+rc.nn);
    res.nn = max(res.nn, lc.nn+rc.nn);
    res.ny = max(lc.ny+rc.ny, lc.nn+rc.ny);
    res.ny = max(res.ny, lc.nn+rc.yy);
    res.yn = max(lc.yy+rc.nn, lc.yn+rc.yn); 
    res.yn = max(res.yn, lc.yn + rc.nn);
    res.yy = max(lc.yy+rc.ny, lc.yn+rc.yy); 
    res.yy = max(res.yy, lc.yn + rc.ny);
    return res;
}

int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 0 ; i < n ; i++) cin >> a[i];
    build(1,0,n-1);
    while(m--){
        int i,j,k;
        cin >> i >> j >> k;
        if(i==0){
            update(j,1,0,n-1,k);
        }
        else{
            node ans = query(1,j,k,0,n-1);
            cout << myMax(ans.yy,ans.yn,ans.ny,ans.nn) << endl;
        }
    }
}