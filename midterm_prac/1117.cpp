#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Point{
public:
    Point(){
        x=0,y=0,z=0;
    }
    int x,y,z;
};
vector<Point> points(1000000);
bool compx(int a, int b){
    if(points[a].x!=points[b].x) return points[a].x < points[b].x;
    else{
        if(points[a].y!=points[b].y) return points[a].y < points[b].y;
        else return points[a].z < points[b].z;
    }
}
bool compy(int a, int b){
    if(points[a].y!=points[b].y) return points[a].y < points[b].y;
    else{
        if(points[a].z!=points[b].z) return points[a].z < points[b].z;
        else return points[a].x < points[b].x;
    }
}

bool compz(int a, int b){
    if(points[a].z!=points[b].z) return points[a].z < points[b].z;
    else{
        if(points[a].x!=points[b].x) return points[a].x < points[b].x;
        else return points[a].y < points[b].y;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> xsort(n),ysort(n),zsort(n),xsame(n),xysame(n),xyzsame(n),ysame(n),yzsame(n),zsame(n),zxsame(n);
    for(int i = 0 ; i < n ; i++){
        cin >> points[i].x >> points[i].y >> points[i].z;
    }
    for(int i = 0 ; i < n ; i++ ){
        xsort[i] = i;
        ysort[i] = i;
        zsort[i] = i;
    }
    sort(xsort.begin(),xsort.end(),compx);
    sort(ysort.begin(),ysort.end(),compy);
    sort(zsort.begin(),zsort.end(),compz);
    int lastx=-1,lasty=-1,lastz=-1;
    for(int i = 0 ; i < n ; i++){
        if(i==n-1){
            int diff = i - lastz - 1;
            for(int curz = i ; curz > lastz ; curz--){
                xyzsame[xsort[curz]]+=diff;
            }
            diff = i - lasty - 1;
            for(int cury = i ; cury > lasty ; cury--){
                xysame[xsort[cury]]+=diff;
            }
            diff = i-lastx-1;
            for( int curx = i ; curx > lastx ; curx--){
                xsame[xsort[curx]]+=diff;
            }
            continue;
        }
        if(points[xsort[i+1]].x!=points[xsort[i]].x){
            int diff = i-lastx-1;
            for( int curx = i ; curx > lastx ; curx--){
                xsame[xsort[curx]]+=diff;
            }
            lastx = lasty = lastz = i;
        }
        else{ // x is same
            if(points[xsort[i+1]].y!=points[xsort[i]].y){
                int diff = i - lasty - 1;
                for(int cury = i ; cury > lasty ; cury--){
                    xysame[xsort[cury]]+=diff;
                }
                lasty = lastz = i;
            }
            else{ //xyissame
                if(points[xsort[i+1]].z != points[xsort[i]].z){
                    int diff = i - lastz - 1;
                    for(int curz = i ; curz > lastz ; curz--){
                        xyzsame[xsort[curz]]+=diff;
                    }
                    lastz = i;
                }
            }
        }
    }
    lasty=-1,lastz=-1;
    for(int i = 0 ; i < n ; i++){
        if(i==n-1){
            int diff = i-lasty-1;
            for( int cury = i ; cury > lasty ; cury--){
                ysame[ysort[cury]]+=diff;
            }
            diff = i - lastz - 1;
            for(int curz = i ; curz > lastz ; curz--){
                yzsame[ysort[curz]]+=diff;
            }
            continue;
        }
        if(points[ysort[i+1]].y!=points[ysort[i]].y){
            int diff = i-lasty-1;
            for( int cury = i ; cury > lasty ; cury--){
                ysame[ysort[cury]]+=diff;
            }
            lasty = lastz = i;
        }
        else{ // y is same
            if(points[ysort[i+1]].z!=points[ysort[i]].z){
                int diff = i - lastz - 1;
                for(int curz = i ; curz > lastz ; curz--){
                    yzsame[ysort[curz]]+=diff;
                }
                lastz = i;
            }
        }
    }
    lastz=-1,lastx=-1;
    
    for(int i = 0 ; i < n ; i++){
        if(i==n-1){
            int diff = i-lastz-1;
            for( int curz = i ; curz > lastz ; curz--){
                zsame[zsort[curz]]+=diff;
            }
            diff = i - lastx - 1;
            for(int curx = i ; curx > lastx ; curx--){
                zxsame[zsort[curx]]+=diff;
            }
            continue;
        }
        if(points[zsort[i+1]].z!=points[zsort[i]].z){
            int diff = i-lastz-1;
            for( int curz = i ; curz > lastz ; curz--){
                zsame[zsort[curz]]+=diff;
            }
            lastz = lastx = i;
        }
        else{ // z is same
            if(points[zsort[i+1]].x!=points[zsort[i]].x){
                int diff = i - lastx - 1;
                for(int curx = i ; curx > lastx ; curx--){
                    zxsame[zsort[curx]]+=diff;
                }
                lastx = i;
            }
        }
    }

    for(int i = 0 ; i < n ; i++ ){
        cout << xsame[i] << " " << ysame[i] << " " << zsame[i] << " " << xysame[i] << " " << zxsame[i] << " " << yzsame[i] << " " << xyzsame[i] << endl;
    }
}