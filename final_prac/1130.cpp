#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
#define pii pair<int,int>
#define f first
#define s second
#define mp make_pair
#define Tie cin.sync_with_stdio(0),cin.tie(0);
using namespace std;
int maze[105][105]={0};
int eSpot[1001][105][105] = {0};
pii dir[5] = {{-1,0},{0,1},{1,0},{0,-1},{0,0}};
struct enemy{
    enemy(){}
    enemy(pii spot, int mode)
        : spot(spot)
        , mode(mode)
    {}
    pii spot;
    int mode;
};
struct status{
    status(){}
    status(pii spot,int time)
        :spot(spot), time(time){}
    pii spot;
    int time;
};
int main(){Tie
    int n,m,t;
    cin >> n >> m >> t;
    vector<enemy> enemies;
    pii start;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0; j < m ; j++){
            cin >> maze[i][j];
            if(maze[i][j]>=4&&maze[i][j]<=7){
                enemies.emplace_back(mp(i,j),maze[i][j]);
                eSpot[0][i][j] = 1;
            }
            if(maze[i][j]==2){ 
                eSpot[0][i][j] = 2;
                start = {i,j};
            }
        }
    }
    //move enemy for every second
    for(int i = 1 ; i <= t ; i++){
        //for each enemy
        for(int j = 0 ; j < enemies.size() ; j++){
            //check mode first
            enemy cur = enemies[j];
            int mode = cur.mode;
            int ni = cur.spot.f + dir[mode-4].f;
            int nj = cur.spot.s + dir[mode-4].s;
            //out of bound
            if(ni<0||ni>=n||nj<0||nj>=m){
                enemies[j].mode += 1;
                if(enemies[j].mode==8) enemies[j].mode = 4;
                eSpot[i][cur.spot.f][cur.spot.s] = 1;
                continue;
            }
            //is wall
            if(maze[ni][nj]==0){
                enemies[j].mode += 1;
                if(enemies[j].mode==8) enemies[j].mode = 4;
                eSpot[i][cur.spot.f][cur.spot.s] = 1;
                continue;
            }
            eSpot[i][ni][nj]=1;
            enemies[j].spot = {ni,nj};
        }
    }

    queue<status> q;
    q.push(status(start,0));
    int ans = 0;
    while(!q.empty()){
        status cur = q.front();
        q.pop();
        int curtime = cur.time;
        //five directions
        for(int i = 0 ; i < 5 ; i++){
            int ni = cur.spot.f + dir[i].f;
            int nj = cur.spot.s + dir[i].s;
            //out of bounds
            if(ni<0||ni>=n||nj<0||nj>=m) continue;
            if(maze[ni][nj]==0) continue; //is wall
            if(eSpot[curtime][ni][nj]==1||eSpot[curtime+1][ni][nj]==1) continue; //have enemy
            if(eSpot[curtime+1][ni][nj]==2) continue;
            //answer found
            if(maze[ni][nj]==3){
                ans = curtime+1;
                break;
            }
            //visit
            if(curtime+1<t){
                eSpot[curtime+1][ni][nj]=2;
                q.push(status({ni,nj},curtime+1));
            }
        }
        if(ans) break;
    }
    if(ans==0) printf("-1\n");
    else printf("%d\n", ans);
}