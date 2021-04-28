#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool valid(vector<int>& wlength,int cols){
    int rowCount = 0;
    int curLength = 0;
    for(int i = 0 ; i < wlength.size() ; i++){
        if(curLength==0) curLength += wlength[i];
        else curLength += 1 + wlength[i];
        while(curLength>cols && rowCount<24){
            curLength = 0;
            rowCount++;
            curLength+=wlength[i];
        }
        if(curLength==cols){
            rowCount++;
            curLength = 0;
        }
    }
    if(rowCount<24 || (rowCount==24&&curLength==0)) return true;
    else return false;
}
int bsearch(vector<int>& wlength){
    int l=1,r = 1000001;
    while(l<r){
        int mid = l+r>>1;
        //cout << mid << endl;
        if(valid(wlength,mid)) r = mid;
        else l = mid+1;
    }
    return l;
}
int main(){
    int n;
    cin >> n;
    vector<int>wlength;
    for(int i = 0 ; i < n ; i++){
        string s;
        cin >> s;
        wlength.push_back(s.length());
    }
    cout << bsearch(wlength) << endl;
}