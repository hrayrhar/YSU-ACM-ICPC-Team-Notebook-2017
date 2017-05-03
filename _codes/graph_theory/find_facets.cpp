const LD eps = 1e-12;
struct pt {
   LD x, y;
   pt(LD x = 0.0, LD y = 0.0) : x(x), y(y) {};
};
typedef pt vect;
vector<pair<pt, pt> > lines;
vector<vector<pt> > in;
vector<vector<int> > G;
vector<pt> mas;
int n, nlines;
map<LL, LD> M;
 
bool cmp(const pt &A, const pt &B) {
   if (fabsl(A.x - B.x) < eps) return A.y + eps < B.y;
   return A.x + eps < B.x;
}
 
void unique(vector<pt> &mas) {
   if (sz(mas) == 0) return;
   sort(all(mas), cmp);
   vector<pt> tmp;
   tmp.pb(mas[0]);
   for (int i = 1; i < sz(mas); ++i)
      if (cmp(mas[i], mas[i - 1]) || cmp(mas[i - 1], mas[i])) tmp.pb(mas[i]);
   mas = tmp;
}
 
int find(pt &A) {
   for (int i = 0; i < sz(mas); ++i)
      if (!cmp(mas[i], A) && !cmp(A, mas[i])) return i;
   throw "no such point finded";
}
 
bool ccw(vect &u, vect &v) {
   return u.x * v.y - u.y * v.x > eps;
}
 
void dfs(int i, vect &u, vector<int> &facet) {
   if (i == facet.front()) return;
   facet.pb(i);
   vect best = u;
   int pos = -1;
   for (int j : G[i]) {
      vect v(mas[j].x - mas[i].x, mas[j].y - mas[i].y);
      if (ccw(best, v) && ccw(u, v)) best = v, pos = j;
   }
   if (pos == -1) facet.clear();
   else dfs(pos, best, facet);
}
 
int main() {
#ifdef harhro94
   freopen("input.txt", "r", stdin);
   //freopen("output.txt", "w", stdout);
#else 
#define task "areas"
   freopen(task".in", "r", stdin);
   freopen(task".out", "w", stdout);
#endif
 
   int nlines;
   cin >> nlines;
   lines.resize(nlines);
   for (int i = 0; i < nlines; ++i)
      cin >> lines[i].first.x >> lines[i].first.y >> lines[i].second.x >> lines[i].second.y;
   in.resize(nlines);
 
   for (int i = 0; i < nlines; ++i) {
      for (int j = i + 1; j < nlines; ++j) {
         pt A = lines[i].first;
         pt B = lines[i].second;
         pt C = lines[j].first;
         pt D = lines[j].second;
 
         LD a1 = B.y - A.y;
         LD b1 = A.x - B.x;
         LD c1 = B.x * A.y - B.y * A.x;
 
         LD a2 = D.y - C.y;
         LD b2 = C.x - D.x;
         LD c2 = D.x * C.y - D.y * C.x;
 
         LD det = a1 * b2 - a2 * b1;
         if (fabsl(det) < eps) continue;
 
         LD detx = -c1 * b2 + c2 * b1;
         LD dety = -a1 * c2 + a2 * c1;
         mas.pb(pt(detx / det, dety / det));
         in[i].pb(mas.back());
         in[j].pb(mas.back());
      }
   }
   unique(mas);
   for (int i = 0; i < nlines; ++i) unique(in[i]);
   int n = sz(mas);
   G.resize(n);
   for (int i = 0; i < nlines; ++i) {
      int cnt = sz(in[i]);
      for (int j = 1; j < cnt; ++j) {
         int u = find(in[i][j]);
         int v = find(in[i][j - 1]);
         G[u].pb(v);
         G[v].pb(u);
      }
   }
   for (int i = 0; i < n; ++i) {
      for (int j : G[i]) {
         vect u(mas[j].x - mas[i].x, mas[j].y - mas[i].y);
         vector<int> facet;
         facet.pb(i);
         dfs(j, u, facet);
         if (sz(facet) == 0) continue;
         //cerr << "Facet finded !!!\n";
         //for (int p : facet) cerr << "\t" << mas[p].x << " " << mas[p].y << endl;
         //cerr << endl;
         LD S = 0.0;
         for (int u = 1; u < sz(facet); ++u) {
            pt B = mas[facet[u]];
            pt A = mas[facet[u - 1]];
            S += (A.y + B.y) * (B.x - A.x);
         }
         pt A = mas[facet.back()];
         pt B = mas[facet.front()];
         S += (A.y + B.y) * (B.x - A.x);
         S = fabsl(S) / 2.0;
         sort(all(facet));
         LL h = 0;
         for (int p : facet) h = 1000000007 * h + p;
         if (S > 1e-9) M[h] = S;
      }
   }
   vector<LD> S;
   for (pair<LL, LD> p : M) S.pb(p.second);
   cout << sz(S) << endl;
   sort(all(S));
   for (LD s : S) cout << fixed << setprecision(9) << s << endl;
 
#ifdef harhro94
   cerr << fixed << setprecision(3) << "\nExecution time = " << clock() / 1000.0 << "s\n";
#endif
   return 0;
}