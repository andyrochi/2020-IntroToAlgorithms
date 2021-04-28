#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*segment tree for sums*/
int* tree;
int* a;
void build(int* a,int v,int tl,int tr){
    if(tl==tr) return tree[v] = a[tl],void();
    int mid = tl+tr>>1;
    build(a,v<<1,tl,mid);
    build(a,v<<1|1,mid+1,tr);
    tree[v] = tree[v<<1] + tree[v<<1|1];
}
void update(int i,int v,int tl,int tr,int val){
    if(tl==tr) return tree[v] = val,void();
    int mid = tl+tr>>1;
    if(i <= mid) update(i,v<<1,tl,mid,val);
    else update(i,v<<1|1,mid+1,tr,val);
    tree[v] = tree[v<<1]+tree[v<<1|1];
}
int query(int v, int l, int r, int tl, int tr){
    if(l==tl&&r==tr) return tree[v];
    int mid = tl+tr>>1;
    if(l > mid) return query(v<<1|1,l,r,mid+1,tr);
    if(r <= mid) return query(v<<1,l,r,tl,mid);
    return query(v<<1,l,mid,tl,mid) + query(v<<1|1,mid+1,r,mid+1,tr);
}

int main(){
    int n;
    cin >> n;
    tree = new int[n<<2];
    a = new int[n];
    for(int i = 0 ; i < n ; i++) cin >> a[i];
    build(a,1,0,n-1);
    int t = 10;
    while(t--){
        int op;
        cin >> op;
        if(op==1){
            cout << "update:";
            int i,val;
            cin >> i >> val;
            update(i,1,0,n-1,val);
            cout << "done" << endl;
        }
        else{
            cout << "query:\n";
            int l,r;
            cin >> l >> r;
            cout << query(1,l,r,0,n-1) << endl;
        }
    }

}