struct edge {
   int u, v, cap, flow;
   edge(int u = 0, int v = 0, int cap = 0, int flow = 0) : u(u), v(v), cap(cap), flow(flow) {}
};

int n, m, s, t, Q[N], ptr[N], dist[N];
vector<edge> edges;
vector<int> G[N];
 
void addEdge(int u, int v, int cap) {
   G[u].pb(sz(edges));
   edges.pb(edge(u, v, cap, 0));
   G[v].pb(sz(edges));
   edges.pb(edge(v, u, 0, 0));
}
 
bool bfs() {
   int l = 0;
   int r = 0;
   fill(dist, dist + N, -1);
   dist[s] = 0;
   Q[r++] = s;
   while (l < r) {
      int u = Q[l++];
      for (int i = 0; i < sz(G[u]); ++i) {
         int id = G[u][i];
         int to = edges[id].v;
         if (dist[to] != -1 || edges[id].flow == edges[id].cap) {
            continue;
         }
         dist[to] = dist[u] + 1;
         Q[r++] = to;
      }
   }
   return dist[t] != -1;
}
 
int dfs(int u, int flow = INF) {
   if (!flow) {
      return 0;
   }
   if (u == t) {
      return flow;
   }
   for (; ptr[u] < sz(G[u]); ++ptr[u]) {
      int id = G[u][ptr[u]];
      int to = edges[id].v;
      if (dist[to] != dist[u] + 1) {
         continue;
      }
      int pushed = dfs(to, min(flow, edges[id].cap - edges[id].flow));
      if (pushed) {
         edges[id].flow += pushed;
         edges[id ^ 1].flow -= pushed;
         return pushed;
      }
 
   }
   return 0;
}
 
LL dinic(int from, int to) {
   LL flow = 0;
   s = from;
   t = to;
   while (bfs()) {
      fill(ptr, ptr + N, 0);
      int pushed;
      while (pushed = dfs(s)) {
         flow += pushed;
      }
   }
   return flow;
}