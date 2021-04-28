#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 50050
int a[MAX] = {0};
struct node{
    int all,sum,ls,rs;
}tree[MAX<<2];

void pushup(int v){
    int lc = v<<1, rc=v<<1|1;
    tree[v].all = tree[lc].all + tree[rc].all;
    tree[v].sum = max(tree[lc].sum,tree[rc].sum);
    tree[v].sum = max(tree[v].sum, tree[lc].rs+tree[rc].ls);
    tree[v].ls  = max(tree[lc].ls, tree[lc].all+tree[rc].ls);
    tree[v].rs  = max(tree[rc].rs, tree[rc].all+tree[lc].rs);
}

void build(int v,int tl,int tr){
    if(tl==tr) return tree[v].all = tree[v].sum = tree[v].ls = tree[v].rs = a[tl], void();
    int mid = tl+tr>>1;
    build(v<<1,tl,mid);
    build(v<<1|1,mid+1,tr);
    pushup(v);
}

void update(int i, int v,int tl,int tr, int val){
    if(tl==tr) return tree[v].all = tree[v].sum = tree[v].ls = tree[v].rs = val, void();
    int mid = tl+tr>>1;
    if(i <= mid) update(i,v<<1,tl,mid,val);
    else         update(i,v<<1|1,mid+1,tr,val);
    pushup(v);
}

node query(int v,int l,int r,int tl,int tr){
    if(tl==l&&tr==r) return tree[v];
    int mid = tl+tr>>1;
    if(r <= mid) return query(v<<1,l,r,tl,mid);
    if(l >  mid) return query(v<<1|1,l,r,mid+1,tr);
    node lc = query(v<<1,l,mid,tl,mid), rc = query(v<<1|1,mid+1,r,mid+1,tr);
    node res;
    res.all = lc.all + rc.all;
    res.sum = max(lc.sum,rc.sum);
    res.sum = max(res.sum, lc.rs+rc.ls);
    res.ls  = max(lc.ls, lc.all+rc.ls);
    res.rs  = max(rc.rs, rc.all+lc.rs);
    return res;
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
            cout << query(1,x-1,y-1,0,n-1).sum << endl;
        }
    }

}