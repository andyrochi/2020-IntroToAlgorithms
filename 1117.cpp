#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct Point{
Point(){
    x = 0;
    y = 0;
    z = 0;
}
int x;
int y;
int z;
} point;

point* points;

bool compxy(int a, int b){
    if(points[a].x < points[b].x) return true;
    else{
        if(points[a].x == points[b].x){
            if(points[a].y < points[b].y) return true;
            else if(points[a].y == points[b].y){
                if(points[a].z < points[b].z) return true;
            }
        }
    }
    return false;
}

bool compyz(int a, int b){
    if(points[a].y < points[b].y) return true;
    else{
        if(points[a].y == points[b].y){
            if(points[a].z < points[b].z) return true;
            else if(points[a].z == points[b].z){
                if(points[a].x < points[b].x) return true;
            }
        }
    }
    return false;
}

bool compzx(int a, int b){
    if(points[a].z < points[b].z) return true;
    else{
        if(points[a].z == points[b].z){
            if(points[a].x < points[b].x) return true;
            else if(points[a].x == points[b].x){
                if(points[a].y < points[b].y) return true;
            }
        }
    }
    return false;
}

inline void update(vector<int>& index, vector<int>& counter, int count, int last, int i){
    for(int j = i-1; j > last; j--) counter[index[j]] = count;
}

int main(){

    int n;
    cin >> n;
    points = new point[n];
    vector<int> index(n), x(n),y(n),z(n),xy(n),yz(n),zx(n),xyz(n);
    
    for(int i = 0 ; i < n ; i++) index[i] = i;
    for(int i = 0 ; i < n ; i++) cin >> points[i].x >> points[i].y >> points[i].z;
    sort(index.begin(),index.end(),compxy);
    
    //count x same, xy same, xyz same
    int xcount = 0, xycount = 0, xyzcount = 0,xlast = -1,xylast = -1,xyzlast = -1;
    for(int i = 1 ; i < n ; i++){
        if(points[index[i]].x==points[index[i-1]].x){
            xcount++;
            if(points[index[i]].y == points[index[i-1]].y){
                xycount++;
                if(points[index[i]].z == points[index[i-1]].z){
                    xyzcount++;
                }
                else{
                    update(index,xyz,xyzcount,xyzlast,i);
                    xyzcount = 0;
                    xyzlast = i-1;
                }
            }
            else{
                //x same but y different, update xycount values
                update(index,xy,xycount,xylast,i);
                update(index,xyz,xyzcount,xyzlast,i);
                
                xycount = 0; //refresh value
                xyzcount = 0;
                xylast = i-1; //update xylast
                xyzlast = i-1;
            }
        }
        else{
            //x is different
            //update xcount values
            update(index,x,xcount,xlast,i);
            update(index,xy,xycount,xylast,i);
            update(index,xyz,xyzcount,xyzlast,i);
           
            xlast = i-1;
            xylast = i-1;
            xyzlast = i-1;
            xcount = 0;
            xycount = 0;
            xyzcount = 0;
        }
        if(i == n-1){
            for(int j = i ; j > xlast ; j--) x[index[j]] = xcount;
            for(int j = i ; j > xylast ; j--) xy[index[j]] = xycount;
            for(int j = i ; j > xyzlast; j--) xyz[index[j]] = xyzcount;
        }
    }
    
    //init index again
    for(int i = 0 ; i < n ; i++) index[i] = i;
    //sort index by y, see y and yz
    sort(index.begin(),index.end(),compyz);
    
    //count y same, yz same
    int ycount = 0, yzcount = 0, ylast = -1,yzlast = -1;
    for(int i = 1 ; i < n ; i++){
        if(points[index[i]].y==points[index[i-1]].y){
            ycount++;
            if(points[index[i]].z == points[index[i-1]].z){
                
                yzcount++;
            }
            else{
                //y same but z different, update yzcount values
                update(index,yz,yzcount,yzlast,i);
                
                yzcount = 0;
                yzlast = i-1; //update xylast
            }
        }
        else{
            //y is different
            //update ycount values
            
            update(index,y,ycount,ylast,i);
            update(index,yz,yzcount,yzlast,i);
           
            ylast = i-1;
            yzlast = i-1;
            ycount = 0;
            yzcount = 0;
        }
        if(i == n-1){
            for(int j = i ; j > ylast ; j--) y[index[j]] = ycount;
            for(int j = i ; j > yzlast; j--) yz[index[j]] = yzcount;
        }
    }

    //init index again
    for(int i = 0 ; i < n ; i++) index[i] = i;
    sort(index.begin(),index.end(),compzx);

    //sort index by z, see z and zx
    int zcount = 0, zxcount = 0, zlast = -1,zxlast = -1;
    for(int i = 1 ; i < n ; i++){
        if(points[index[i]].z==points[index[i-1]].z){
            zcount++;
            if(points[index[i]].x == points[index[i-1]].x){
                
                zxcount++;
            }
            else{
                //z same but x different, update zxcount values
                update(index,zx,zxcount,zxlast,i);
                
                zxcount = 0;
                zxlast = i-1; //update zxlast
            }
        }
        else{
            //z is different
            //update zcount values and zxcount values
            
            update(index,z,zcount,zlast,i);
            update(index,zx,zxcount,zxlast,i);
           
            zlast = i-1;
            zxlast = i-1;
            zcount = 0;
            zxcount = 0;
        }
        if(i == n-1){
            for(int j = i ; j > zlast ; j--) z[index[j]] = zcount;
            for(int j = i ; j > zxlast; j--) zx[index[j]] = zxcount;
        }
    }

    for(int i = 0 ; i < n ; i++){
        cout << n-1-(x[i] + y[i] + z[i] - xy[i] - yz[i] - zx[i] + xyz[i]) << " ";
    }
    return 0;
}