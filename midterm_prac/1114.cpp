#include <iostream>
#include <set>
#include <cmath>
using namespace std;
int main(){
    int n,k;
    cin >> n >> k;
    multiset<int> a;
    double rate = (double)k/100;
    int perc,pos=0;
    multiset<int>::iterator it;
    while(n--){
        int x;
        cin >> x;
        if(x==0){
            if(k!=0&&k!=100){
                perc=ceil(rate*a.size());
                while(pos<perc){
                    pos++;
                    it++;
                }
                /*注意*/
                while(pos>perc){
                    pos--;
                    it--;
                }
            }
            cout << *it << endl;
        }
        else{
            a.insert(x);
            if(k==0) it = a.begin();
            else if(k==100){
                it = a.end();
                it--;
            }
            else{
                if(pos==0){
                    it = a.begin();
                    pos++;
                }
                else if(x<*it) pos++;
            }
        }
    }
}