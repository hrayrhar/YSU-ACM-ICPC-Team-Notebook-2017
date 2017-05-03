const int N = 100007;
int n, dep[N], par[N], size[N];
vector<int> G[N];
bool heavy[N];
 
vector<vector<int> > chains;
int id[N], pos[N];
 
void dfs(int u, int p = 0, int d = 0) {
   par[u] = p;
   dep[u] = d;
   size[u] = 1;
   int maxi = 0, pos = 0;
   for (int i = 0; i < sz(G[u]); ++i) {
      int to = G[u][i];
      if (to != p) {
         dfs(to, u, d + 1);
         if (size[to] > maxi) {
            maxi = size[to];
            pos = to;
         }
         size[u] += size[to];
      }
   }
   heavy[pos] = true;
}
 
int makeHLD(int u) {
   bool f = false;
   for (int i = 0; i < sz(G[u]); ++i) {
      int to = G[u][i].first;
      if (to == par[u]) continue;
      int ind = makeHLD(to);
      if (ind != -1) {
         chains[ind].pb(u);
         id[u] = ind;
         f = true;
      }
   }
   if (!f) {
      id[u] = sz(chains);
      chains.pb(vector<int>());
      chains[id[u]].pb(u);
   }
   if (heavy[u]) return id[u];
   return -1;
}
 
struct segTree {
   
   int n, *T;
 
   void init(int s) {
      n = s;
      T = new int[4 * s + 2];
      memset(T, 0, 4 * (4 * s + 2));
   }
   
   // ...
};
vector<segTree> S;
 
int getLca(int u, int v) {
   while (id[u] != id[v]) {
      if (dep[chains[id[u]][0]] < dep[chains[id[v]][0]]) v = par[chains[id[v]][0]];
      else u = par[chains[id[u]][0]];
   }
   return dep[u] < dep[v] ? u : v;
}
 
int go(int u, int v) {
   int ret = -1000000000;
   while (id[u] != id[v]) {
      ret = max(ret, S[id[u]].get(1, 0, S[id[u]].n - 1, 0, pos[u]));
      u = par[chains[id[u]][0]];
   }
   if (u == v) return ret;
   ret = max(ret, S[id[u]].get(1, 0, S[id[u]].n - 1, pos[v] + 1, pos[u]));
   return ret;
}

// build

dfs(1);
chains.clear();
makeHLD(1);
for (int i = 0; i < sz(chains); ++i) reverse(all(chains[i]));
for (int i = 0; i < sz(chains); ++i)
  for (int j = 0; j < sz(chains[i]); ++j)
     pos[chains[i][j]] = dep[chains[i][j]] - dep[chains[i][0]];

S.clear();
S.resize(sz(chains));
for (int i = 0; i < sz(chains); ++i) {
  S[i].init(sz(chains[i]));
  for (int j = 0; j < S[i].n; ++j)
     S[i].update(1, 0, S[i].n - 1, j, w[chains[i][j]]);
}