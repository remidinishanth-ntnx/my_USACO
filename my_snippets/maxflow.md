## Problems where flow is used
* Maximum matching in Bipartite graphs(mostly used)
* Edge-disjoint paths
* Node-disjoint paths

## Flow Algorithms
* Ford-Fulkerson Algorithm
* Edmonds-Karp Algorithm
* Dinic Algorithm
* Push-relabel Algorithm
* Scaling Algorithm

## Problems
* https://www.codechef.com/problems/GNUM
* https://www.codechef.com/problems/CHEFAFD
* https://www.codechef.com/problems/RIN
* https://www.codechef.com/problems/CHEFKC
* https://www.codechef.com/problems/BIBOARD

```cpp
struct TEdge{
    int from,to,cap,f;
};

vector<TEdge> edges;
vector<int> adj[VCOUNT];
vector<bool> vis;

void add_edge(int from,int to,int cap){
    adj[from].push_back(edges.size());
    edges.push_back({from,to,cap,0});
    adj[to].push_back(edges.size());
    edges.push_back({to,from,0,0});
}

//almost a DFS
//what is largest amount of flow w 
//we can push starting from vertex v
//returned value is amount pushed
int push(int v,int w){
    if(v==sink) return w;
    if(vis[v]) return 0;
    vis[v]=1;
    for(int ind:adj[v]){
        int go=edges[ind].c-edges[ind].f;
        if(go==0) continue;
        int res=push(edges[ind].to,min(w,go));
        if(res==0) continue; // didn't manage to push
        edges[ind].f+=res;
        edges[ind^1].f-=res;
        return res;
    }
    return 0;
}

while(push(src,INF)>0) vis.clear();

while(int sent=push(src,INF)) total+=sent,vis.clear();
```

Only applying DFS is just finding some augmenting path and the running time of above algorithm can be pseudo-polynomial O(mf) for flow f.

If we use BFS instead, then the augmented path will be shortest in terms on number of hops(hop count) then the augmented path is fixed and the running time is polynomial
O(nm^2), this is Edmonds Karp algorithm.

If we use BFS and then Level graph and then blocking flow then we get Dinic algorithm and this is O(n^2m).


### Dinic Algo

1. Construct a level graph by doing BFS from source to label all the levels of the current flow graph, residual edges of the level graph myst have (cap-flow)>0

2. If the sink was never reached while building the level graph then stop and return the max flow.

3. Using only valid edges in the level graph, do multiple DFSs from s->t until a blocking flow is reached, and sum over the  bottleneck values of all the augmenting paths found to calculate the max flow.

Repeat Steps 1 to 3

Idea of blocking flows is to destroy all Shortest paths of a given distance, so it increases distance

IMPORTANT!!!! The interface of algorithm assumes that vertices has numbers from 0 to (n-1)

```cpp
const int MAXN = ...; // number of vertices
const int INF = 1000000000; // infinity constant
 
struct edge {
	int a, b, cap, flow;
};
 
int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vector e;
vector g[MAXN];
 
// add edge from a to b with capacity cap
void add_edge (int a, int b, int cap) {
	assert(a < n);
	assert(b < n);
	edge e1 = { a, b, cap, 0 };
	edge e2 = { b, a, 0, 0 };
	g[a].push_back ((int) e.size());
	e.push_back (e1);
	g[b].push_back ((int) e.size());
	e.push_back (e2);
}
 
bool bfs() {
	int qh=0, qt=0;
	q[qt++] = s;
	memset (d, -1, n * sizeof d[0]);
	d[s] = 0;
	while (qh < qt && d[t] == -1) {
		int v = q[qh++];
		for (size_t i=0; i < g[v].size(); ++i) {
			int id = g[v][i],
				to = e[id].b;
			if (d[to] == -1 && e[id].flow < e[id].cap) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
		}
	}
	return d[t] != -1;
}
 
int dfs (int v, int flow) {
	if (!flow)  return 0;
	if (v == t)  return flow;
	for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
		int id = g[v][ptr[v]],
			to = e[id].b;
		if (d[to] != d[v] + 1)  continue;
		int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
		if (pushed) {
			e[id].flow += pushed;
			e[id^1].flow -= pushed;
			return pushed;
		}
	}
	return 0;
}
// this funciton returns max flow from s to t on graph g
int dinic() {
	int flow = 0;
	for (;;) {
		if (!bfs()) break;
		memset (ptr, 0, n * sizeof ptr[0]);
		while (int pushed = dfs (s, INF))
			flow += pushed;
	}
	return flow;
}
```

source: http://neerc.ifmo.ru/trains/toulouse/2016/code/dinic.html

Check Um_nik https://codeforces.com/contest/1184/submission/56662441
