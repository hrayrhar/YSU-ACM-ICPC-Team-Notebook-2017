const int N = 1000007;
 
struct CentroidDecomposition {
   vector<int> G[N];
   bool used[N];
   int size[N]; // subtree size
   int maxi[N]; // max subtree size
 
   struct node {
      int v;
      vector<node*> to;
      unordered_map<int, int> id; // child id of a vertex in subtree
      vector<int> nodes; // nodes in subtree
 
      // keep additional data here
 
      node(int v = 0) : v(v) {}
   };
   typedef node* pnode;
   pnode root;
 
   void dfs(int u, int par, vector<int> &mas) {
      mas.pb(u);
      size[u] = 1;
      maxi[u] = 1;
      for (int to : G[u]) {
         if (to != par && !used[to]) {
            dfs(to, u, mas);
            size[u] += size[to];
            maxi[u] = max(maxi[u], size[to]);
         }
      }
   }
 
   void buildData(pnode root) {
      root->nodes.pb(root->v);
      for (int i = 0; i < sz(root->to); ++i) {
         pnode to = root->to[i];
         for (int u : to->nodes) {
            root->nodes.pb(u);
            root->id[u] = i;
         }
      }
   }
 
   pnode build(int u) {
      vector<int> mas;
      dfs(u, -1, mas);
      int n = sz(mas);
      int best = N, pos = -1;
      for (int u : mas) {
         maxi[u] = max(maxi[u], n - size[u]);
         if (maxi[u] < best) {
            best = maxi[u];
            pos = u;
         }
      }
      u = pos;
      used[u] = true;
      node *root = new node(u);
      for (int to : G[u])
         if (!used[to]) root->to.pb(build(to));
      buildData(root);
      return root;
   }
 
} cd;
 

// build
for (int i = 0; i < n - 1; ++i) {
   int u, v;
   scanf("%d%d", &u, &v);
   cd.G[u].pb(v);
   cd.G[v].pb(u);
}
cd.root = cd.build(1);