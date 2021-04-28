#include <iostream>
#include <set>
#include <math.h>
using namespace std;

int main(){
    int n,k;
    cin >> n >> k;
    multiset<int> mulset;
    double rate = (double)k/100;
    int count = 1;
    multiset<int>::const_iterator it;
    while(n--){
        int x;
        cin >> x;
        
        if(x==0){
            if(rate == 0){
                cout << *mulset.begin() << endl;
                continue;
            }
            int per = ceil(rate*mulset.size());
            while(count < per){
                count++;
                it++;
            }
            while(count > per){
                count--;
                it--;
            }
            cout << *it << endl;
        }
        else{
            
            if(mulset.empty()){
                mulset.insert(x);
                it = mulset.begin();
            }
            else{
                mulset.insert(x);
                if(x<*it){
                    count++;
                }
            }
            
        }
    }
}