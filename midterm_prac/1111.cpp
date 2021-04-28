#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class num{
public:
    num(){
        val = 0;
        l = 0;
        r = 0;
    }
    
    bool operator<(const num& other)const{
        return val < other.val;
    }
    long long val,l,r;
};
void count(vector<num>&a, vector<num>&left, vector<num>&right){
    int i = 0, j = 0, k = 0;
    int lsize = left.size(), rsize = right.size();
    while(j < lsize && k < rsize){
        if(left[j]<right[k]){
            left[j].r += k; //number of rights that is less than left[j] (which is already placed)
            a[i++] = left[j++];
        }
        else if(right[k]<left[j]){
            right[k].l += lsize - j; //number of lefts that is larger than right[k]
            a[i++] = right[k++];
        }
        else{ //right[k] == left[j]
            int rLess = k;
            while(left[j].val==right[k].val&&j<lsize){
                left[j].r += rLess;
                a[i++] = left[j++];
            }
        }
    }
    while(j<lsize){
        left[j].r += rsize;
        a[i++]=left[j++];
    }
    while(k<rsize) a[i++] = right[k++];
}
void dnc(vector<num>& a){
    int n = a.size();
    if(n==1) return;
    int half = n/2;
    vector<num> left(half),right(n-half);
    for(int i = 0 ; i < half; i++) left[i] = a[i];
    for(int i = 0 ; i < n-half ; i++) right[i] = a[i+half];
    dnc(left);
    dnc(right);
    count(a,left,right);
}
int main(){
    int n;
    cin >> n;
    vector<num> a(n);
    for(int i = 0 ; i < n ; i++) cin >> a[i].val;
    dnc(a);
    long long sum = 0;
    for(int i = 0 ; i < n ; i++) sum += a[i].l * a[i].r;
    
    cout << sum << endl;
}