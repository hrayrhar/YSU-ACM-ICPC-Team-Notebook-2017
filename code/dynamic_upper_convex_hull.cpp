const int N = 100007;
int n, x[N], c[N], t[N];
LL dp[N];
 
const LD eps = 1e-12;
struct segment {
   LL k, b; // y = kx + b
   LD x1, x2; // x1 < x2
 
   segment(LL k = 0, LL b = 0, LD x1 = -1e7, LD x2 = +1e7) : k(k), b(b), x1(x1), x2(x2) {}
 
   bool operator < (const segment &o) const {
      if (k != o.k) return k < o.k;
      return b < o.b;
   }
};
 
struct segment2 {
   LL k, b;
   LD x;
 
   segment2(LL k = 0, LL b = 0, LD x = 0.0) : k(k), b(b), x(x) {}
 
   bool operator < (const segment2 &o) const {
      if (fabsl(x - o.x) < eps) return k < o.k;
      return x < o.x;
   }
};
set<segment2> hull2;
set<segment> hull;
 
int cmp(LL k, LL b, const segment &s) {
   LD y1line = k * s.x1 + b;
   LD y2line = k * s.x2 + b;
   LD y1seg = s.k * s.x1 + s.b;
   LD y2seg = s.k * s.x2 + s.b;
   if (y1line < y1seg + eps && y2line < y2seg + eps) return -1;
   if (y1line + eps > y1seg && y2line + eps > y2seg) return +1;
   return 0;
}
 
inline void addSegment(segment s) {
   hull.insert(s);
   hull2.insert(segment2(s.k, s.b, s.x1));
}
 
inline void deleteSegment(segment s) {
   hull.erase(s);
   hull2.erase(segment2(s.k, s.b, s.x1));
}
 
void addLine(LL k, LL b) {
   //lines.pb(mp(k, b));
 
   segment cur(k, b);
   if (hull.empty()) {
      addSegment(cur);
      return;
   }
   if (hull.count(cur)) return;
   auto it = hull.lower_bound(cur);
   // go left
   while (!hull.empty() && it != hull.begin()) {
      --it;
      if (cmp(k, b, *it) == 1) deleteSegment(*it);
      else break;
      it = hull.lower_bound(cur);
   }
   it = hull.lower_bound(cur);
   // go right
   while (!hull.empty() && it != hull.end()) {
      if (cmp(k, b, *it) == 1) deleteSegment(*it);
      else break;
      it = hull.lower_bound(cur);
   }
   if (hull.empty()) {
      addSegment(cur);
      return;
   }
   // intersect with left and right
   it = hull.lower_bound(cur);
   if (it == hull.begin()) {
      if (cmp(k, b, *it) == -1) return;
      else {
         LD x = (LD)(b - it->b) / (it->k - k);
         segment tmp = *it;
         tmp.x1 = x;
         deleteSegment(*it);
         addSegment(tmp);
         cur.x2 = x;
         addSegment(cur);
      }
   }
   else if (it == hull.end()) {
      --it;
      if (cmp(k, b, *it) == -1) return;
      LD x = (LD)(b - it->b) / (it->k - k);
      segment tmp = *it;
      tmp.x2 = x;
      deleteSegment(*it);
      addSegment(tmp);
      cur.x1 = x;
      addSegment(cur);
   }
   else {
      auto lit = it; --lit;
      auto rit = it;
      if (cmp(k, b, *lit) == -1 || cmp(k, b, *rit) == -1) return;
      LD x1 = (LD)(b - lit->b) / (lit->k - k);
      LD x2 = (LD)(b - rit->b) / (rit->k - k);
      segment t1 = *lit;
      segment t2 = *rit;
      deleteSegment(t1);
      deleteSegment(t2);
      t1.x2 = x1;
      t2.x1 = x2;
      cur.x1 = x1;
      cur.x2 = x2;
      addSegment(t1);
      addSegment(cur);
      addSegment(t2);
   }
}
 
LL getMax(LL x) {
   segment2 t(-(1LL << 58), 0, x);
   auto it = hull2.lower_bound(t);
   --it;
   return x * it->k + it->b;
}