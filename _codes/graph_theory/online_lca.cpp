int n, m, par[N], dep[N], up[20][N];
vector<int> G[N];
 
void dfs(int u, int p = 1, int d = 0) {
   par[u] = p;
   dep[u] = d;
   for (int i = 0; i < sz(G[u]); ++i) {
      int to = G[u][i];
      if (to != p) dfs(to, u, d + 1);
   }
}
 
int lca(int u, int v) {
   if (dep[u] < dep[v]) swap(u, v);
   int diff = dep[u] - dep[v];
   for (int i = 0; (1 << i) <= diff; ++i)
      if (((diff >> i) & 1) == 1) u = up[i][u];
   if (u == v) return u;
   for (int i = 19; i >= 0; --i)
      if (up[i][u] != up[i][v])
         u = up[i][u], v = up[i][v];
   return up[0][u];
}
 
// preprocessing

dfs(1);
for (int i = 1; i <= n; ++i) up[0][i] = par[i];
for (int k = 1; k < 20; ++k)
  for (int i = 1; i <= n; ++i)
     up[k][i] = up[k - 1][up[k - 1][i]];
