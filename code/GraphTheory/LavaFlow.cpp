struct Cell{
    int x,y,t;
};
 
const int MAX = 1005;
int n,m;
 
char maze[MAX][MAX];
int vis[MAX][MAX];
int player[MAX][MAX];
char path[MAX][MAX];
set<pii> isExit;
queue<Cell> q;
string res;
 
bool isValid(int x, int y){
    if(x < 0 || x >= n || y < 0 || y >= m) return false;
    if(maze[x][y] == '#') return false;
    return true;
}
 
bool isSafe(int x, int y, int u, int v){
    return player[x][y] == -1 and maze[x][y] != 'M' and (vis[x][y] == -1 or player[u][v] + 1 < vis[x][y]);
}
 
 
void restorePath(int u, int v, int x, int y){
	 while (x != u || y != v) {
        res.push_back(path[u][v]);
 
        if (res.back() == 'U') u++;
        if (res.back() == 'D') u--;
        if (res.back() == 'L') v++;
        if (res.back() == 'R') v--;
    }
}
 
bool lavaFlow(int x,int y){
    q.push({x,y,1});
    player[x][y] = 0;
 
	while(!q.empty()){
		int u =  q.front().x;
		int v = q.front().y;
        int t = q.front().t;
 
		q.pop();
 
        vector<pii> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
 
		for(auto it: dir){
            int i = u+it.fs;
            int j = v+it.sc;
 
            if(isValid(i,j)){
                if(t == 0){
                    if(vis[i][j] == -1){
                        vis[i][j] = vis[u][v]+1;
                        q.push(Cell{i,j,0});
                    }
                }else{
                    if(isSafe(i,j,u,v)){
                        path[i][j] = (it.fs == 1) ? 'D' : (it.fs == -1) ? 'U' : (it.sc == 1) ? 'R' : 'L';
                        player[i][j] = player[u][v]+1;
                        q.push(Cell{i,j,1});
                        if (isExit.find({i,j}) != isExit.end()) {
                            if (player[i][j] < vis[i][j] || vis[i][j] == -1) {
                                restorePath(i, j, x, y);
                                return true;
                            }
                        }
                    }
                }
            }
 
        }
	}
 
	return false;
}
