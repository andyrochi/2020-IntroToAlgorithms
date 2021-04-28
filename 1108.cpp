#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int bsearch(vector<int> &a, int target){
    int beg = 0, end = a.size();
    while(beg <= end){
        int pos = (beg + end)/2;
        if(a[pos] == target) return pos;
        else if(target > a[pos]) beg = pos+1;
        else end = pos-1;
    }
    //cout << "not found" << endl;
    return -1;
}
int twoSum(vector<int> &a, int target) {
    // TODO
    sort(a.begin(),a.end());
    int pos = bsearch(a,target);
    int cnt = 0;
    int beg = 0, end = a.size()-1;
    if(pos == 0) return cnt;
    else if (pos == -1){
        beg = 0;
        end = a.size()-1;
    }
    else{
        beg = 0;
        end = pos-1;
    }
    while(beg < end){
            int sum = a[beg]+a[end];
            if(sum == target){
                cnt++;
                beg++;
            }
            else if (sum > target){
                end--;
            }
            else{
                beg++;
            }
        
    }
    return cnt;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int n, target;
    cin >> n >> target;
    vector<int> a(n);
    for (int &x : a) {
        cin >> x;
    }
    
    cout << twoSum(a,target) << '\n';
}