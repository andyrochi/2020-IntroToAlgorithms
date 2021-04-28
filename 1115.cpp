#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

class Node{
public:
    Node(){
        yy = 0;
        yn = 0;
        ny = 0;
        nn = 0;
    }
    Node(ll yy, ll yn, ll ny, ll nn){
        this->yy = yy;
        this->yn = yn;
        this->ny = ny;
        this->nn = nn;
    }
    ll yy;
    ll yn;
    ll ny;
    ll nn;

};
vector<Node> sTree;
vector<int> a;
ll findMax(ll a, ll b, ll c){
    ll middle = max(a,b);
    return max(middle,c);
}

ll maxYY(Node& L, Node& R){
    ll yyny = (L.yy<0||R.ny<0)? -1 : L.yy + R.ny;
    ll ynyy = (L.yn<0||R.yy<0)? -1 : L.yn + R.yy;
    ll ynny = (L.yn<0||R.ny<0)? -1 : L.yn + R.ny;
    return findMax(yyny, ynyy, ynny);
}
ll maxYN(Node& L, Node& R){
    ll yynn = (L.yy<0||R.nn<0)? -1 : L.yy + R.nn;
    ll ynyn = (L.yn<0||R.yn<0)? -1 : L.yn + R.yn;
    ll ynnn = (L.yn<0||R.nn<0)? -1 : L.yn + R.nn;
    return findMax(yynn, ynyn, ynnn);
}
ll maxNY(Node& L, Node& R){
    ll nyny = (L.ny<0||R.ny<0)? -1 : L.ny + R.ny;
    ll nnyy = (L.nn<0||R.yy<0)? -1 : L.nn + R.yy;
    ll nnny = (L.nn<0||R.ny<0)? -1 : L.nn + R.ny;
    return findMax(nyny,nnyy,nnny);
}
ll maxNN(Node& L, Node& R){
    ll nynn = (L.ny<0||R.nn<0)? -1 : L.ny + R.nn;
    ll nnyn = (L.nn<0||R.yn<0)? -1 : L.nn + R.yn;
    ll nnnn = (L.nn<0||R.nn<0)? -1 : L.nn + R.nn;
    return findMax(nynn,nnyn,nnnn);
}

/*Function to build the tree*/
void build(int v, int tl, int tr){
    if(tl == tr){
        sTree[v].yy = a[tl];
        sTree[v].yn = -1;
        sTree[v].ny = -1;
        sTree[v].nn = 0;
    }

    else{
        int tm = (tl+tr)/2;
        build(2*v,tl,tm);
        build(2*v+1,tm+1,tr);
        if(tr-tl == 1){
            sTree[v].yy = -1;
            sTree[v].yn = a[tl];
            sTree[v].ny = a[tr];
            sTree[v].nn = 0;
        }
        else{
            sTree[v].yy = maxYY(sTree[2*v],sTree[2*v+1]);
            sTree[v].yn = maxYN(sTree[2*v],sTree[2*v+1]);
            sTree[v].ny = maxNY(sTree[2*v],sTree[2*v+1]);
            sTree[v].nn = maxNN(sTree[2*v],sTree[2*v+1]);
        }
    }
}

/*Function return largest YY,YN,NY,NN of the segment*/
Node query(int v, int tl, int tr, int l, int r){
    if(l>r) return Node(-1,-1,-1,-1);
    if(l == tl && r == tr) return sTree[v];
    int tm = (tl + tr) / 2;
    //all on left
    if(r <= tm){
        return query(2*v,tl,tm,l,r);
    }
    //all on right
    if(l > tm){
        return query(2*v+1,tm+1,tr,l,r);
    }
    //cross middle
    Node L = query(2*v,tl,tm,l,tm);
    Node R = query(2*v+1,tm+1,tr,tm+1,r);
    return Node(maxYY(L,R),maxYN(L,R),maxNY(L,R),maxNN(L,R));
}

ll maxFour(Node q){
    vector<ll> arr;
    arr.push_back(q.yy);
    arr.push_back(q.yn);
    arr.push_back(q.ny);
    arr.push_back(q.nn);
    return *(max_element(arr.begin(),arr.end()));
}

void update(int v, int tl, int tr, int pos, int val){
    if(tl == tr) sTree[v] = Node(val,-1,-1,0);
    else{
        int tm = (tl+tr)/2;
        if(pos <= tm) update(2*v,tl,tm,pos,val);
        else update(2*v+1,tm+1,tr,pos,val);
        sTree[v].yy = maxYY(sTree[2*v],sTree[2*v+1]);
        sTree[v].yn = maxYN(sTree[2*v],sTree[2*v+1]);
        sTree[v].ny = maxNY(sTree[2*v],sTree[2*v+1]);
        sTree[v].nn = maxNN(sTree[2*v],sTree[2*v+1]);
    }
}

int main(){
    
    int n,m;
    cin >> n >> m;
    a.resize(n);
    for(int i = 0 ; i < n ; i++) cin >> a[i];
    sTree.resize(4*n);
    build(1,0,n-1);
    
    while(m--){
        int o;
        cin >> o;
        if(o==1){
            int l,r;
            cin >> l >> r;
            cout << maxFour(query(1,0,n-1,l,r)) << endl;
            
        }
        else{
            int index,val;
            cin >> index >> val;
            update(1,0,n-1,index,val);
        }
    }
    return 0;
}