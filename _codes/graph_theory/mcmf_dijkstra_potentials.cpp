struct MCMF {
    vector<Edge> E;
    vector<int> G[N];
    int n, s, t;
    int Q[N], pre[N], preId[N];
    LL pi[N], dist[N];
    bool is[N];
    LL ansFlow, ansCost;
 
    void addEdge(int u, int v, LL cap, LL cost) {
        G[u].pb(sz(E));
        E.pb(Edge(v, cap, cost));
        G[v].pb(sz(E));
        E.pb(Edge(u, 0, -cost));
    }
 
    void init(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
        assert(t < n);
        FOR(i, n) G[i].clear();
        E.clear();
        ansFlow = ansCost = 0;
    }
 
    void fordBellman() {
        FOR(i, n) {
            is[i] = false;
            dist[i] = INF;
        }
        int l = 0, r = 0;
        Q[r++] = s;
        dist[s] = 0;
        is[s] = true;
        while (l != r) {
            int u = Q[l++];
            if (l == N) l = 0;
            is[u] = false;
            for (int id : G[u]) {
                int to = E[id].to;
                if (E[id].cap - E[id].flow > 0 && dist[to] > dist[u] + E[id].cost) {
                    dist[to] = dist[u] + E[id].cost;
                    if (!is[to]) {
                        is[to] = true;
                        Q[r++] = to;
                        if (r == N) r = 0;
                    }
                }
            }
        }
    }
 
    bool dijkstra() {
        FOR(i, n) dist[i] = INF;
        dist[s] = 0;
        set<pair<LL, int> > S;
        S.insert(mp(0, s));
        while (!S.empty()) {
            int u = S.begin()->second;
            S.erase(S.begin());
            for (int id : G[u]) {
                int to = E[id].to;
                LL cost = E[id].cost + pi[u] - pi[to];
                if (E[id].cap - E[id].flow > 0 && dist[to] > dist[u] + cost) {
                    S.erase(mp(dist[to], to));
                    pre[to] = u;
                    preId[to] = id;
                    dist[to] = dist[u] + cost;
                    S.insert(mp(dist[to], to));
                }
            }
        }
        // new_pi = pi + dist, easy to prove
        FOR(i, n) {
            if (dist[i] != INF) pi[i] += dist[i];
        }
        return dist[t] != INF;
    }
 
    void augment() {
        int u = t;
        LL minCap = INF;
        LL totalCost = 0;
        while (u != s) {
            int id = preId[u];
            minCap = min(minCap, E[id].cap - E[id].flow);
            totalCost += E[id].cost;
            u = pre[u];
        }
 
        ansFlow += minCap;
        ansCost += minCap * totalCost;
 
        u = t;
        while (u != s) {
            int id = preId[u];
            E[id].flow += minCap;
            E[id ^ 1].flow -= minCap;
            u = pre[u];
        }
    }
 
    pair<LL, LL> mcmf() {
        fordBellman();
        FOR(i, n) pi[i] = dist[i];
        while (dijkstra()) {
            augment();
        }
        return mp(ansFlow, ansCost);
    }
 
} mf;