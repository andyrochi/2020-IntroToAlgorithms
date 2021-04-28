#include <iostream>
#include <vector>
using namespace std;
int *tree;

void build(vector<int>& a,int tl,int tr, int i){
    if(tl==tr) tree[i] = a[tl];
    else{
        int mid = (tl+tr)/2;
        build(a,tl,mid,i<<1);
        build(a,mid+1,tr,i<<1|1);
        tree[i] = tree[i<<1] + tree[i<<1|1];
    }
}
int query(int tl, int tr,int l,int r, int i){
    if(l == tl && r == tr) return tree[i];
    int mid = (tl+tr)/2;
    if(r <= mid) return query(tl,mid,l,r,i<<1);
    if(l > mid) return query(mid+1,tr,l,r,(i<<1)|1); 
    return query(tl,mid,l,mid,i<<1) + query(mid+1,tr,mid+1,r,i<<1|1);
}

void update(int tl,int tr,int pos,int val,int i){
    if(tl == tr) tree[i] = val;
    else{
        int mid = (tl+tr) / 2;
        if(pos <= mid){
            update(tl,mid,pos,val,i<<1);
        }
        else{
            update(mid+1,tr,pos,val,i<<1|1);
        }
        tree[i] = tree[i<<1] + tree[i<<1|1];
    }
}


int main(){

    int n,m;
    cin >> n >> m;
    tree = new int [n<<2];
    vector<int> a(n);
    for(int i = 0 ; i < n ; i++) cin >> a[i];

    build(a,0,n-1,1);
    
    while(m--){
        int op;
        cin >> op;
        if(op==0){
            int index,val;
            cin >> index >> val;
            update(0,n-1,index,val,1);
        }
        else{
            int l,r;
            cin >> l >> r;
            if(l <= r)
                cout << query(0,n-1,l,r,1) << endl;
            else
                cout << query(0,n-1,l,n-1,1) + query(0,n-1,0,r,1) << endl;
        }
    }
    return 0;
}