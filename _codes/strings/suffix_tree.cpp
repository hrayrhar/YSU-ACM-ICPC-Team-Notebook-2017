const int N = 300007;
char A[N], B[N], C[N], S[N];
int na, nb, nc, n;
 
struct node {
   int l, r, par, suff;
   char pch;
   map<char, int> nxt;
 
   node(int l = 0, int r = 0, int par = 0, char pch = 0, int suff = -1) :
      l(l), r(r), par(par), pch(pch), suff(suff) {
   }
 
   int len() const {
      return r - l;
   }
} T[2 * N];
 
struct pos {
   int v, p;
   pos(int v = 0, int p = 0) : v(v), p(p) {}
} ptr;
int size = 1;
 
pos go(const pos &ptr, char c) {
   if (T[ptr.v].len() == ptr.p) {
      int v = ptr.v;
      if (T[v].nxt.count(c)) {
         int to = T[v].nxt[c];
         return pos(to, 1);
      }
      return pos(-1, -1);
   }
   if (S[T[ptr.v].l + ptr.p] == c) return pos(ptr.v, ptr.p + 1);
   return pos(-1, -1);
}
 
int split(const pos &ptr) {
   if (T[ptr.v].len() == ptr.p) return ptr.v;
   if (ptr.p == 0) return T[ptr.v].par;
 
   int mid = size++;
   int v = ptr.v;
   int par = T[v].par;
   char midch = S[T[v].l + ptr.p];
 
   //par
   T[par].nxt[T[v].pch] = mid;
 
   //mid
   T[mid].par = par;
   T[mid].pch = T[v].pch;
   T[mid].l = T[v].l;
   T[mid].r = T[v].l + ptr.p;
   T[mid].nxt[midch] = v;
 
   // v
   T[v].par = mid;
   T[v].pch = midch;
   T[v].l = T[mid].r;
 
   return mid;
}
 
pos fastGo(pos ptr, int l, int r) {
   while (l != r) {
      if (T[ptr.v].len() == ptr.p) {
         ptr.v = T[ptr.v].nxt[S[l]];
         ++l;
         ptr.p = 1;
         continue;
      }
      int step = min(T[ptr.v].len() - ptr.p, r - l);
      ptr.p += step;
      l += step;
   }
   if (ptr.p == 0) {
      ptr.p = T[ptr.v].len();
      ptr.v = T[ptr.v].par;
   }
   return ptr;
}
 
pos getSuff(int v) {
   if (T[v].suff != -1) return pos(T[v].suff, T[T[v].suff].len());
   pos ret;
   if (T[v].par == 0) ret = fastGo(0, T[v].l + 1, T[v].r);
   else ret = fastGo(getSuff(T[v].par), T[v].l, T[v].r);
   assert(ret.p == T[ret.v].len());
   T[v].suff = ret.v;
   return ret;
}
 
void extend(int i) {
   char c = S[i];
   while (true) {
      pos goPos = go(ptr, c);
      if (goPos.v == -1) {
         int mid = split(ptr);
         int leaf = size++;
         T[mid].nxt[c] = leaf;
         T[leaf] = node(i, n, mid, c);
         if (ptr.v == 0) {
            ptr = pos(0, 0);
            break;
         }
         int par = T[mid].par;
         if (par == 0) ptr = fastGo(pos(0, 0), T[mid].l + 1, T[mid].r);
         else ptr = fastGo(getSuff(par), T[mid].l, T[mid].r);
      }
      else {
         ptr = goPos;
         break;
      }
   }
}

void print(int u) {
   for (auto p : T[u].nxt) {
      int to = p.second;
      cerr << "edge from " << u << " " << " to " << to << " by string " << string(S + T[to].l, S + T[to].r) << endl;
      print(to);
   }
}
 
// build
T[0].suff = 0;
for (int i = 0; i < n; ++i) extend(i);