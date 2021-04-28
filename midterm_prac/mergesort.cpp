#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void merge(vector<int>&a, vector<int>& left, vector<int>& right){
    int i=0,j=0,k=0;
    while(i<left.size()&&j<right.size()){
        if(left[i]<right[j]) a[k++] = left[i++];
        else a[k++] = right[j++];
    }
    while(i<left.size()) a[k++] = left[i++];
    while(j<right.size()) a[k++] = right[j++];
}

void mergesort(vector<int>& a){
    int n = a.size();
    if(n==1) return;
    int half = n/2;
    vector<int> left(half);
    vector<int> right(a.size()-half);
    for(int i = 0 ; i < half ; i++) left[i] = a[i];
    for(int j = 0 ; j < a.size()-half ; j++) right[j] = a[j+half];
    mergesort(left);
    mergesort(right);
    merge(a,left,right);
    
}
int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n ; i++) cin >> a[i];
    mergesort(a);
    for(int i = 0 ; i< n ; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}