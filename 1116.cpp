#include <iostream>
#include <queue>
using namespace std;

int main(){

    priority_queue<int> a;
    int n;
    cin >> n;
    int size = n;
    while(size--){
        int input;
        cin >> input;
        a.push(input);
    }
    int cnt = 0;
    unsigned long long sum = 0;
    while(cnt != n){
        int first = a.top();
        a.pop();
        int second = a.top();
        a.pop();
        int dif = first - second;
        if(first == second){
            first = 0;
            second = 0;
            cnt+=2;
        }
        else if(second > 0){
            first = first-second;
            second = 0;
            cnt+=1;
        }
        else{
            first = 0;
            cnt+=1;
        }
        sum+=dif;
        a.push(first);
        a.push(second);
    }
    cout << sum << endl;
}