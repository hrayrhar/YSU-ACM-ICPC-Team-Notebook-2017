const int N = 100007;
int n, timer, tin[N], id[N], ptr, mas[N + N], pos[N], mlog[N + N], mini[20][N + N];
vector<int> G[N];
 
void dfs(int u, int p = -1) {
   id[timer] = u;
   tin[u] = timer++;
   pos[u] = ptr;
   mas[ptr++] = tin[u];
   for (int to : G[u]) {
      if (to != p) {
         dfs(to, u);
         mas[ptr++] = tin[u];
      }
   }
}
 
int lca(int u, int v) {
   int l = pos[u], r = pos[v];
   if (l > r) swap(l, r);
   int k = mlog[r - l + 1];
   int w = id[min(mini[k][l], mini[k][r - (1 << k) + 1])];
   return w;
}
 
 
dfs(0);
mlog[1] = 0;
for (int i = 2; i < ptr; ++i) mlog[i] = 1 + mlog[i >> 1];
for (int i = 0; i < ptr; ++i) mini[0][i] = mas[i];
for (int k = 0; k < 19; ++k) {
   for (int i = 0; i < ptr; ++i) {
      if (i + (1 << (k + 1)) - 1 >= ptr) break;
      mini[k + 1][i] = min(mini[k][i], mini[k][i + (1 << k)]);
   }
}