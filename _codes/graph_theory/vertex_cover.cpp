const int N = 2007;
int n, m, k, mt[N];
int ptr[N], deg[N], G[N][N];
bool used[N];
char ans[N];
queue<int> Q;
 
bool kuhn(int u)
{
   used[u] = true;
   for (int i = 0; i < ptr[u]; ++i)
   {
      int to = G[u][i];
      if (mt[to] == -1 || (!used[mt[to]] && kuhn(mt[to])))
      {
         mt[to] = u;
         mt[u] = to;
         return true;
      }
   }
   return false;
}


// init some matching 
for (int i = 1; i <= n + m; ++i)
  mt[i] = -1;

for (int i = 1; i <= n; ++i) deg[i] = ptr[i];

int size = 0;
FOR(iter, n)
{
  int u = -1;
  int best = N * N;
  for (int i = 1; i <= n; ++i)
  {
     if (deg[i] >= 1 && deg[i] < best)
     {
        best = deg[i];
        u = i;
     }
  }
  if (u == -1) break;
  deg[u] = 0;
  FOR(i, ptr[u])
  {
     int to = G[u][i];
     if (mt[to] == -1)
     {
        mt[to] = u;
        mt[u] = to;
        ++size;
        FOR(j, ptr[to]) --deg[G[to][j]];
        break;
     }
  }
}

// kuhn
for (int i = 1; i <= n; ++i)
{
  if (mt[i] == -1)
  {
     for (int j = 1; j <= n; ++j) used[j] = false;
     size += kuhn(i);
  }
}
 
// bfs from 2 unmatched sides 
for (int i = 1; i <= n + m; ++i) ans[i] = 'E';
for (int i = 1; i <= n + m; ++i)
{
  if (mt[i] == -1)
  {
     ans[i] = 'N';
     Q.push(i);
  }
}
while (!Q.empty())
{
  int u = Q.front();
  Q.pop();
  if (ans[u] == 'N')
  {
     FOR(i, ptr[u])
     {
        int to = G[u][i];
        if (ans[to] == 'E')
        {
           ans[to] = 'A';
           Q.push(to);
        }
     }
  }
  else
  {
     int to = mt[u];
     if (ans[to] == 'E')
     {
        ans[to] = 'N';
        Q.push(to);
     }
  }
}