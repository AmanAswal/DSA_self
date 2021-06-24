#include<iostream>
#include<vector>

using namespace std;

// 1091. Shortest Path in Binary Matrix
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    if(grid.size() == 0 || grid[0].size() == 0) return -1;

    int n = grid.size();
    int m = n;
    
    if(grid[0][0] == 1 || grid[n - 1][n - 1]) return -1;
    
    queue<int> que;
    vector<vector<int>> dir = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {-1,-1},{-1,1} ,{1,-1} };

    grid[0][0] = 1; // mark true

    que.push(0 * m + 0);    // idx = (r * m + c)

    int level = 1; // answer in terms of nodes 
    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            int idx = que.front(); que.pop();

            int r = idx / m;
            int c = idx % m;

            if(r == n - 1 && c == m - 1){
                return level;
            }

            for(int d = 0; d < dir.size(); d++){
                int x = r + dir[d][0];
                int y = c + dir[d][1];

                if(x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 0){
                    grid[x][y] = 1; // mark true
                    que.push(x * m + y);    // encode and push
                }
            }
        }
        level++;
    }   
    return -1;
}

// 785. Is Graph Bipartite?
bool isBipartite(vector<vector<int>>& graph, vector<int> &vis, int src) {
    queue<int> que;
    que.push(src);
    int color = 0; // red
    bool isCycle = false;   // not asked in ques though

    while(que.size() != 0){
        int size = que.size();
        
        while(size-- > 0){
            int rvtx = que.front(); que.pop();

            if(vis[rvtx] != -1){
                isCycle = true;

                if(vis[rvtx] != color) return false;   // not bipartite
                
                continue;
            }

            vis[rvtx] = color;

            for(int e : graph[rvtx]){
                if(vis[e] == -1)
                    que.push(e);
            }
        }
        color = (color + 1) % 2;
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph){
    int n = graph.size();
    // -1 : not visited, 0 : red, 1 : green
    vector<int> vis(n, -1);

    // for(int i = 0; i < n; i++){
    //     if(vis[i] == -1 && !isBipartite(graph, vis, i))
    //         return false;
    // }
    // return true;

    bool res = true;
    for(int i = 0; i < n; i++){
        if(vis[i] == -1)
            res = res && isBipartite(graph, vis, i);
    }
    return res;
}

// 994. Rotting Oranges
int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    int time = 0;
    queue<int> que;

    vector<vector<int>> dir = { {0,1}, {1,0}, {0, -1}, {-1,0} };

    int freshOranges = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){

            if(grid[i][j] == 2) 
                que.push(i * m + j);
            else if(grid[i][j] == 1) 
                freshOranges++;
        }
    }

    if(freshOranges == 0) return 0;

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0)
        {
            int idx = que.front(); que.pop();
            
            int r = idx / m;
            int c = idx % m;

            for(int d = 0; d < dir.size(); d++){
                int x = r + dir[d][0];
                int y = c + dir[d][1];

                if(x >= 0 && y >=0 && x < n && y < m && grid[x][y] == 1)
                {
                    freshOranges--;
                    grid[x][y] = 2;
                    que.push(x * m + y);

                    if(freshOranges == 0)
                        return time + 1;
                }
            }
        }
        time++;
    }
    return -1;
}

// 663 · Walls and Gates
void wallsAndGates(vector<vector<int>> &rooms) {
    int n = rooms.size();
    int m = rooms[0].size();

    vector<vector<int>> dir = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    
    queue<int> que;

    int countOfRooms = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < M; j++){
            if(rooms[i][j] == 0)
                que.push(i * m + j);
            else if(rooms[i][j] == 2147483647)
                countOfRooms++;
        }
    }
    
    if(countOfRooms == 0) return;

    int level = 0;
    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0)
        {
            int idx = que.front(); que.pop();

            int r = idx / m;
            int c = idx % m;

            for(int d = 0; d < dir.size(); d++){
                int x = r + dir[d][0];
                int y = c + dir[d][1];

                if(x >= 0 && y >= 0 && x < n && y < m && rooms[x][y] == 2147483647)
                {
                    countOfRooms--;
                    rooms[x][y] = level + 1;
                    que.push(x * m + y);
                    
                    if(countOfRooms == 0)
                        return;
                }
            }
        }
        level++;
    }
}

// khans algo questions

// 207. Course Schedule
vector<int> khansAlgo(int N, vector<vector<int>> &graph){
    vector<int> inDegree(N, 0);

    for(int i = 0; i < N; i++){
        for(int e : graph[i])
            inDegree[e]++;
    }

    queue<int> que;
    vector<int> ans;

    for(int i = 0; i < N; i++)
        if(inDegree[i] == 0)
            que.push(i);
    
    int level = 0;

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0)
        {
            int rvtx = que.front(); que.pop();
            ans.push_back(rvtx);

            for(int e : graph[rvtx]){
                if(--inDegree[e] == 0)
                    que.push(e);
            }
        }
        level++;
    }

    // for(int ele : ans) cout << ele << " ";

    // to check cycle is present or not
    return ans;
}

bool canFinish(int N, vector<vector<int>>& arr) {
    vector<vector<int>> graph(N);

    for(vector<int> ar : arr){
        graph[ar[0]].push_back(ar[1]);
    }

    return khansAlgo(N,graph).size() == N;
}

//210. Course Schedule II
vector<int> findOrder(int N, vector<vector<int>>& arr) {
    vector<vector<int>> graph(N);

    for(vector<int> ar : arr){
        graph[ar[0]].push_back(ar[1]);
    }

    vector<int>ans = khansAlgo(N, graph);
    if(ans.size() != N) return {};    
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(){
    return 0;
}