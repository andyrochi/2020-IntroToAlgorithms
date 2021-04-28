#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define pp pair<long long, long long>

vector<long long> rLess, lLarge;

void merge(vector<pp>&a, vector<pp>&b, vector<pp>&c){
    int i = 0, j = 0, k = 0;
    int bsize = b.size(), csize = c.size();
    while(i < bsize && j < csize){
        if(b[i].first <= c[j].first){
            a[k] = b[i];
            int diff = j;
            rLess[b[i].second] += diff;
            k++;
            i++;
        }
        else{
            a[k] = c[j];
            lLarge[c[j].second] += (bsize - i);
            k++;
            j++;
        }
    }
    while(i<b.size()){
        a[k] = b[i];
        rLess[b[i].second] += csize;
        k++;
        i++;
    }
    while(j<c.size()){
        a[k++] = c[j++];
    }
}

void dnc(vector<pp>& a, int size){
    if(size <= 1) return;
    vector<pp> b;
    vector<pp> c;
    copy(a.begin(),a.begin()+size/2,back_inserter(b));
    copy(a.begin()+size/2,a.end(),back_inserter(c));
    dnc(b,size/2);
    dnc(c,size - size/2);
    merge(a,b,c);
}
int main(){
    
    int n;
    cin >> n;
    vector<pp> a(n);
    rLess.resize(n);
    lLarge.resize(n);
    for(int i = 0 ; i < n ; i++){
        cin >> a[i].first;
        a[i].second = i;
    }
    dnc(a,n);
    long long sum = 0LL;
    for(int i = 0 ; i < a.size() ; i++){
        sum += lLarge[i]*rLess[i];
    }
    cout << sum << endl;
    return 0;
}