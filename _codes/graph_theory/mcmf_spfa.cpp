const int INF = (1 << 29);
const int V = 207;
struct edge {
    int u, to, cap, cost, back;
    edge(int u = 0, int to = 0, int cap = 0, int cost = 0, int back = 0) :
        u(u), to(to), cap(cap), cost(cost), back(back) {
    }
};
vector<edge> E;
vector<int> G[V];
int nv, source, sink, dist[V], pedge[V], Q[V];
int mcost, mflow;
bool in[V];
 
void addedge(int u, int v, int cap, int cost) {
    G[u].pb(sz(E));
    E.pb(edge(u, v, cap, cost, sz(E) + 1));
    G[v].pb(sz(E));
    E.pb(edge(v, u, 0, -cost, sz(E) - 1));
}
 
bool fordBellmanQueue() {
    fill(dist, dist + V, INF);
    dist[source] = 0;
    int l = 0;
    int r = 0;
    Q[r++] = source;
    in[source] = true;
    while (l != r) {
        int u = Q[l++];
        in[u] = false;
        if (l == V) l = 0;
        for (int id : G[u]) {
            int to = E[id].to;
            int cap = E[id].cap;
            int cost = E[id].cost;
            if (cap && dist[to] > dist[u] + cost) {
                dist[to] = dist[u] + cost;
                pedge[to] = id;
                if (!in[to]) {
                    Q[r++] = to;
                    if (r == V) r = 0;
                    in[to] = true;
                }
            }
        }
    }
    return (dist[sink] != INF);
}
 
void mcmf() {
    while (fordBellmanQueue()) {
        int u = sink;
        int minCap = INF;
        while (u != source) {
            int id = pedge[u];
            minCap = min(minCap, E[id].cap);
            u = E[id].u;
        }
        mflow += minCap;
        mcost += minCap * dist[sink];
        u = sink;
        while (u != source) {
            int id = pedge[u];
            E[id].cap -= minCap;
            E[E[id].back].cap += minCap;
            u = E[id].u;
        }
    }
}