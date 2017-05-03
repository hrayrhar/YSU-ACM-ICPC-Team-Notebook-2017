const int N = 20007;
const int LOG = 16;
char st[N];
int n;
int cnt[N], p[N], tp[N], c[N], tc[N];
int lcp[N], mlog[N], mini[LOG][N];
 
void build() {
   FOR(i, n) ++cnt[st[i]];
   FOR(i, N) {
      if (i) cnt[i] += cnt[i - 1];
   }
   for (int i = n - 1; i >= 0; --i) {
      p[--cnt[st[i]]] = i;
   }
   c[p[0]] = 0;
   for (int i = 1, cur = 0; i < n; ++i) {
      if (st[p[i]] != st[p[i - 1]]) ++cur;
      c[p[i]] = cur;
   }
   for (int h = 0; (1 << h) < n; ++h) {
      FOR(i, n) {
         tp[i] = p[i] - (1 << h);
         if (tp[i] < 0) tp[i] += n;
      }
 
      memset(cnt, 0, sizeof cnt);
      FOR(i, n) ++cnt[c[i]];
      FOR(i, N) {
         if (i) cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; i >= 0; --i) {
         p[--cnt[c[tp[i]]]] = tp[i];
      }
 
      tc[p[0]] = 0;
      for (int i = 1, cur = 0; i < n; ++i) {
         int m1 = (p[i] + (1 << h)) % n;
         int m2 = (p[i - 1] + (1 << h)) % n;
         if (c[p[i]] != c[p[i - 1]] || c[m1] != c[m2]) ++cur;
         tc[p[i]] = cur;
      }
      FOR(i, n) c[i] = tc[i];
   }
}
 
void calc_lcps() {
   int *pos = new int[n];
   FOR(i, n) pos[p[i]] = i;
   int cur = 0;
   FOR(i, n) {
      int ind = pos[i];
      if (ind == n - 1) {
         cur = 0;
         continue;
      }
      cur = max(0, cur - 1);
      while (p[ind] + cur < n && p[ind + 1] + cur < n && st[p[ind] + cur] == st[p[ind + 1] + cur]) {
         ++cur;
      }
      lcp[ind] = cur;
   }
}
 
void build_sparse_table() {
   mlog[1] = 0;
   for (int i = 2; i < N; ++i) mlog[i] = 1 + mlog[i >> 1];
   FOR(i, n - 1) mini[0][i] = lcp[i];
   FOR(h, LOG - 1) {
      FOR(i, n - 1) {
         if (i + (1 << (h + 1)) > n - 1) break;
         mini[h + 1][i] = min(mini[h][i], mini[h][i + (1 << h)]);
      }
   }
}
 
int get_min(int i, int j) {
   if (i == j) return N;
   --j;
   int k = mlog[j - i + 1];
   return min(mini[k][i], mini[k][j - (1 << k) + 1]);
}