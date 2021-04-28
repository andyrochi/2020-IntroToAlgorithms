#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
#define mp make_pair
#define pii pair<int,int>
#define f first
#define s second
int haveEnemy[101][101][1005]={0};
int g[101][101];
struct enemy{
    enemy(pii pos, int dir){
        this->pos = pos;
        this->dir = dir;
    }
    int dir;
    pii pos;
};
struct stat{
    stat(pii pos, int sec){
        this->pos = pos;
        this->sec = sec;
    }
    int sec;
    pii pos;
};
//debug use
void pH(int n,int m,int t){
    puts("");
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            printf("%d ",haveEnemy[i][j][t]);
        }
        puts("");
    }
}
int main(){
    int n,m,t;
    cin >> n >> m >> t;
    pii source;
    vector<enemy> e;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            cin >> g[i][j];
            if(g[i][j]==2){
                source = mp(i,j);
            }
            if(g[i][j]<=7&&g[i][j]>=4){
                
                e.push_back(enemy({i,j},g[i][j]));
            }
        }
    }
    /*
    for(int i = 0 ; i < e.size() ; i++){
        printf("[%d,%d],dir=%d\n",e[i].pos.f,e[i].pos.s,e[i].dir);
    }
    */
    //walk all enemies for every sec
    //up 4 right 5 down 6 left 7
    for(int j = 0 ; j < e.size() ; j++){
        enemy temp(e[j].pos,e[j].dir);
        haveEnemy[temp.pos.f][temp.pos.s][0]=1;
        for(int i = 1; i <= t ; i++){
            int r = temp.pos.f, c = temp.pos.s;
            bool set = false;
            while(!set){
                //up
                if(temp.dir==4){
                    if(r-1<0||g[r-1][c]==0){
                        temp.dir=5;
                    }
                    else{
                        haveEnemy[r-1][c][i] = 1;
                        temp.pos.f = r-1;
                        temp.pos.s = c;
                        set = true;
                    }
                }
                //right
                if(temp.dir==5){
                    if(c+1>=m||g[r][c+1]==0){
                        temp.dir=6;
                    }
                    else{
                        haveEnemy[r][c+1][i] = 1;
                        temp.pos.f = r;
                        temp.pos.s = c+1;
                        set = true;
                    }
                }
                //down
                if(temp.dir==6){
                    if(r+1>=n||g[r+1][c]==0){
                        temp.dir=7;
                    }
                    else{
                        haveEnemy[r+1][c][i] = 1;
                        temp.pos.f = r+1;
                        temp.pos.s = c;
                        set = true;
                    }
                }
                //left
                if(temp.dir==7){
                    if(c-1<0||g[r][c-1]==0){
                        temp.dir=4;
                    }
                    else{
                        haveEnemy[r][c-1][i] = 1;
                        temp.pos.f = r;
                        temp.pos.s = c-1;
                        set = true;
                    }
                }
            }
        }
    }

    //for(int i = 1 ; i <= t ; i++) pH(n,m,i);

    //bfs per step
    int ans = 0;
    stat beg(source,0);
    queue<stat> q;
    q.push(beg);
    haveEnemy[source.f][source.s][0]=2;
    while(!q.empty()){
        stat curStat = q.front();
        q.pop();
        int curSec = curStat.sec;
        pii curPos = curStat.pos;
        int r = curPos.f, c = curPos.s;
        //stay
        if(haveEnemy[r][c][curSec+1]!=1){
            if(curSec+1<t){
                if(haveEnemy[r][c][curSec+1]!=2){
                    q.push(stat(curPos,curSec+1));
                    haveEnemy[r][c][curSec+1] = 2; //don't let others to put
                }
            }
        }
        //up
        if(r-1>=0){
            int cr = r-1, cc = c;
            if(g[cr][cc]!=0){
                //is road and no enemy
                //cout << "here" << endl;
                if(haveEnemy[cr][cc][curSec]!=1&&haveEnemy[cr][cc][curSec+1]!=1){
                    //is dest
                    if(g[cr][cc]==3){
                        ans = curSec+1;
                        break;
                    }
                    //not dest
                    if(curSec+1<t){
                        if(haveEnemy[cr][cc][curSec+1]!=2){
                            q.push(stat({cr,cc},curSec+1));
                            haveEnemy[cr][cc][curSec+1] = 2; //don't let others to put
                        }
                    }
                }
            }
        }
        //right
        if(c+1<m){
            int cr = r, cc= c+1;
            if(g[cr][cc]!=0){
                //is road and no enemy
                if(haveEnemy[cr][cc][curSec]!=1&&haveEnemy[cr][cc][curSec+1]!=1){
                    //is dest
                    if(g[cr][cc]==3){
                        ans = curSec+1;
                        break;
                    }
                    //not dest
                    if(curSec+1<t){
                        if(haveEnemy[cr][cc][curSec+1]!=2){
                            q.push(stat({cr,cc},curSec+1));
                            haveEnemy[cr][cc][curSec+1] = 2; //don't let others to put
                        }
                    }
                }
            }
        }
        //down
        if(r+1<n){
            int cr = r+1, cc=c;
            if(g[cr][cc]!=0){
                //is road and no enemy
                if(haveEnemy[cr][cc][curSec]!=1&&haveEnemy[cr][cc][curSec+1]!=1){
                    //is dest
                    if(g[cr][cc]==3){
                        ans = curSec+1;
                        break;
                    }
                    //not dest
                    if(curSec+1<t){
                        if(haveEnemy[cr][cc][curSec+1]!=2){
                            q.push(stat({cr,cc},curSec+1));
                            haveEnemy[cr][cc][curSec+1] = 2; //don't let others to put
                        }
                    }
                }
            }
        }
        //left
        if(c-1>=0){
            int cr = r, cc = c-1;
            if(g[cr][cc]!=0){
                //is road and no enemy
                if(haveEnemy[cr][cc][curSec]!=1&&haveEnemy[cr][cc][curSec+1]!=1){
                    //is dest
                    if(g[cr][cc]==3){
                        ans = curSec+1;
                        break;
                    }
                    //not dest
                    if(curSec+1<t){
                        if(haveEnemy[cr][cc][curSec+1]!=2){
                            q.push(stat({cr,cc},curSec+1));
                            haveEnemy[cr][cc][curSec+1] = 2; //don't let others to put
                        }
                    }
                }
            }
        }
    }
    /*
    for(int i = 0 ; i <= t ; i++){
        printf("i=%d\n", i);
        pH(n,m,i);
    }*/
    
    if(ans==0)
        printf("-1\n");
    else
        printf("%d\n", ans);
}