const int N = 100007;
const LD eps = 1e-9;
struct Line {
   LD a, b;
   Line(LD a = 0.0, LD b = 0.0) : a(a), b(b) {}
   bool operator < (const Line &o) const {
      return a > o.a;
   }
} st[N], mas[N];
int top, n;
 
inline LD cross(const Line &u, const Line &v) {
   return (v.b - u.b) / (u.a - v.a);
}
 
void add(const Line &L) {
   while (top > 1 && cross(st[top - 2], st[top - 1]) > cross(st[top - 1], L) - eps) {
      --top;
   }
   st[top++] = L;
}
 
LD query(LD x) {
   int l = 0;
   int r = top - 1;
   LD lx, rx;
   int pos = -1;
   while (true) {
      int m = (l + r) / 2;
      LD x1 = -1e18, x2 = 1e18;
      if (m != 0) {
         x1 = cross(st[m - 1], st[m]);
      }
      if (m != top - 1) {
         x2 = cross(st[m], st[m + 1]);
      }
      if (x > x1 - eps && x < x2 + eps) {
         pos = m;
         lx = x1;
         rx = x2;
         break;
      }
      else if (x < x1 - eps) {
         r = m - 1;
      }
      else {
         l = m + 1;
      }
   }
   assert(pos != -1);
   Line &L = st[pos];
   return L.a * x + L.b;
}