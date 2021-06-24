#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Edge{
public:
    int v = 0;
    int w = 0;

    Edge(int v, int w){
        this->v = v;
        this->w = w;
    }
};

const int N = 11;
vector<vector<Edge>> graph(N);

void addEdge(int u, int v, int w){
    graph[u].push_back(Edge(v, w));
    // graph[v].push_back(Edge(u, w));
}

void display(){
    for(int u = 0; u < N; u++){
        cout << u << " -> ";

        for(Edge e : graph[u]){
            cout << "(" << e.v << "," << e.w << ")";
        }
        cout << endl;
    }
}

void dfs_topo(int src, vector<bool> &vis, vector<int> &ans)
{
    // mark
    vis[src] = true;

    // for unvisited nbrs, call again
    for(Edge e : graph[src]){
        if(!vis[e.v])
            dfs_topo(e.v, vis, ans);
    }

    // push to stack
    ans.push_back(src);
}

void topologicalOrder_DFS(){
    vector<bool> vis(N, false);
    vector<int> ans;

    for(int i = 0; i < N; i++){
        if(!vis[i])
            dfs_topo(i, vis, ans);
    }

    for(int ele : ans) cout << ele << " ";
}


// indegree array
// indegree[i] == 0 ? que.push(i);
// normal bfs, rvtx, ans.push_back(rvtx);
// --indegree[e.v] == 0 ? que.push(e.v);
// to check cycle -> if(ans.size() == N) yes : no;
void khansAlgo(){
    vector<int> inDegree(N, 0);

    for(int i = 0; i < N; i++){
        for(Edge e : graph[i])
            inDegree[e.v]++;
    }

    queue<int> que;
    vector<int> ans;

    for(int i = 0; i < N; i++)
        if(indegree[i] == 0)
            que.push(i);
    
    int level = 0;

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0)
        {
            int rvtx = que.front(); que.pop();
            ans.push_back(rvtx);

            for(Edge e : graph[rvtx]){
                if(--indegree[e.v] == 0)
                    que.push(e.v);
            }
        }
        level++;
    }

    for(int ele : ans) cout << ele << " ";

    // to check cycle is present or not
    // return ans.size() == N;
}

void constructGraph(){

    // for(int i = 0; i < e; i++){
    //     int u, v, w;
    //     cin >> u >> v >> w;
    //     addEdge(u, v, w);
    // }

    addEdge(5,0,10);
    addEdge(5,1,10);
    addEdge(4,0,10);
    addEdge(4,8,40);
    addEdge(0,6,2);
    addEdge(1,2,2);
    addEdge(2,3,8);
    addEdge(6,7,3);
    addEdge(7,3,3);
    addEdge(8,9,3);
    addEdge(9,10,3);
    addEdge(10,3,3);
}

int main()
{
    constructGraph();
    topologicalOrder_DFS();
    return 0;
}