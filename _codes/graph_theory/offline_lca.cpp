int n, m, timer, par[N], cand[N], u1[M], u2[M], pos1[M], pos2[M], lca[M];
vector<pair<int, int> > query[M];
vector<int> G[N];
bool used[N];
 
int getPar(int u) {
   return (par[u] == u ? u : (par[u] = getPar(par[u])));
}
 
void unite(int u, int v, int newCand) {
   u = getPar(u);
   v = getPar(v);
   if (rand() & 1) {
      swap(u, v);
   }
   par[u] = v;
   cand[v] = newCand;
}
 
void dfs(int u) {
   used[u] = true;
   par[u] = u;
   cand[u] = u;
   for (int to : G[u]) {
      if (!used[to]) {
         dfs(to);
         unite(to, u, u);
      }
   }
   for (int i = 0; i < sz(query[u]); ++i) {
      int v = query[u][i].first;
      if (used[v]) {
         query[u][i].second = cand[getPar(v)];
      }
   }
}
 
void process() {
   for (int i = 0; i < m; ++i) {
      int u = u1[i];
      int v = u2[i];
      pos1[i] = sz(query[u]);
      query[u].pb(mp(v, -1));
      pos2[i] = sz(query[v]);
      query[v].pb(mp(u, -1));
   }
   dfs(1);
   for (int i = 0; i < m; ++i) {
      int p1 = pos1[i];
      int p2 = pos2[i];
      int u = u1[i];
      int v = u2[i];
      if (query[u][p1].second != -1)
         lca[i] = query[u][p1].second;
      else if (query[v][p2].second != -1)
         lca[i] = query[v][p2].second;
      else
         assert(false);
   }
}