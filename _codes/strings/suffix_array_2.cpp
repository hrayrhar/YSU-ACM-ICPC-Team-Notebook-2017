const int N = 100007;
const int A = 256;
char st[N];
int n;
 
struct SA {
 
   int C[20][N], p[N], tp[N], cnt[N];
 
   void build() {
      FOR(i, A) cnt[i] = 0;
      FOR(i, n) ++cnt[st[i]];
      FOR(i, A) {
         if (i) cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; i >= 0; --i) {
         p[--cnt[st[i]]] = i;
      }
      C[0][p[0]] = 0;
      for (int i = 1, cur = 0; i < n; ++i) {
         if (st[p[i]] != st[p[i - 1]]) ++cur;
         C[0][p[i]] = cur;
      }
      for (int h = 1, lev = 0; h < n; h <<= 1, ++lev) {
         FOR(i, n) tp[i] = (p[i] - h + n) % n;
         FOR(i, n) cnt[i] = 0;
         FOR(i, n) ++cnt[C[lev][i]];
         FOR(i, n) {
            if (i) cnt[i] += cnt[i - 1];
         }
         for (int i = n - 1; i >= 0; --i) {
            int ind = tp[i];
            p[--cnt[C[lev][ind]]] = ind;
         }
 
         C[lev + 1][p[0]] = 0;
         for (int i = 1, cur = 0; i < n; ++i) {
            if (C[lev][p[i - 1]] != C[lev][p[i]] || C[lev][(p[i - 1] + h) % n] != C[lev][(p[i] + h) % n]) ++cur;
            C[lev + 1][p[i]] = cur;
         }
      }
   }
} sa;
 
int getlcp(int i, int j) {
   int ans = 0;
   for (int h = 19; h >= 0; --h) {
      if ((1 << h) > n) continue;
      if (sa.C[h][i] == sa.C[h][j]) {
         i += (1 << h);
         j += (1 << h);
         ans += (1 << h);
      }
   }
   return ans;
}
 
int compare(int i, int j, int len) {
   for (int h = 19; h >= 0; --h) {
      if ((1 << h) > len) continue;
      if (sa.C[h][i] < sa.C[h][j]) return -1;
      if (sa.C[h][i] > sa.C[h][j]) return 1;
      i = (i + (1 << h)) % n;
      j = (j + (1 << h)) % n;
      len -= (1 << h);
   }
   return 0;
}