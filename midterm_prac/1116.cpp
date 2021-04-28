#include <iostream>
#include <queue>
using namespace std;

int main(){
    priority_queue<int> q;
    int n,num,count=0;
    long long cost = 0;
    cin >> n;
    for(int i = 0 ; i < n ; i++){
        cin >> num;
        q.push(num);
    }
    while(count < n){
        int first = q.top();
        q.pop();
        int second = q.top();
        q.pop();
        if(first==second){
            if(first) count+=2;
            first = second = 0;
        }
        else{
            int diff = first-second;
            cost += diff;
            if(first>0&&second>0){
                first = first-second;
                second = 0;
                count++;
            }
            else{
                first = 0;
                count++;
            }
        }
        q.push(first),q.push(second);
    }
    cout << cost << endl;
}