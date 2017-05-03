const LD pi = acosl(-1.0);
const LD eps = 1e-7;
struct pt {
   LD x, y;
   pt(LD x = 0.0, LD y = 0.0) : x(x), y(y) {}
 
   void rotate(LD ang) {
      LD fi = atan2l(y, x);
      LD len = sqrtl(x * x + y * y);
      fi += ang;
      x = len * cosl(fi);
      y = len * sinl(fi);
   }
};
vector<pair<pt, pt> > seg;
int n;
 
bool inSegment(pt &M, pt &A, pt &B) {
   return min(A.x, B.x) < M.x + eps && M.x < max(A.x, B.x) + eps &&
      min(A.y, B.y) < M.y + eps && M.y < max(A.y, B.y) + eps;
}

bool intersects(LD a, LD b, LD c, LD d) {
   if (a > b) swap(a, b);
   if (c > d) swap(c, d);
   return max(a, c) < min(b, d) + eps;
}
 
bool intersects(pt &A, pt &B, pt &C, pt &D) {
   LD a1 = A.y - B.y;
   LD b1 = B.x - A.x;
   LD c1 = -a1 * A.x - b1 * A.y;
 
   LD a2 = C.y - D.y;
   LD b2 = D.x - C.x;
   LD c2 = -a2 * C.x - b2 * C.y;
 
   LD det = a1 * b2 - a2 * b1;
 
   if (fabsl(det) < eps) {
      if (fabsl(c1 * b2 - c2 * b1) < eps && fabsl(c1 * a2 - c2 * a1) < eps)
         return intersects(A.x, B.x, C.x, D.x) && intersects(A.y, B.y, C.y, D.y);
      return false;
   }
   else {
      pt M;
      M.x = (b1 * c2 - b2 * c1) / det;
      M.y = (a2 * c1 - a1 * c2) / det;
      return inSegment(M, A, B) && inSegment(M, C, D);
   }
}
 
inline bool intersects(int i, int j) {
   return intersects(seg[i].first, seg[i].second, seg[j].first, seg[j].second);
}
 
LD sweepX;
struct segment {
   int id;
   segment(int id = 0) : id(id) {}
   bool operator < (const segment &o) const {
      pt& A = seg[id].first;
      pt& B = seg[id].second;
      pt& C = seg[o.id].first;
      pt& D = seg[o.id].second;
      /*
      ete unenq vertical hatvacner, hetevyal kerpov enq y hashvum, aglorithmy jisht e ashxatum naev
      vertical uxixneri depqum, vorpes y yntrum enq kamayakan, orinak hatvaci araji keti Y
      bolor verticalnery skzbic insert en arvum, heto deleta TESTED
      ete ayspes anenq, nerqevum(144-159) petq che pttel ketery
      LD y1 = fabsl(B.x - A.x) > eps ? A.y + (B.y - A.y) * (sweepX - A.x) / (B.x - A.x) : A.y;
      LD y2 = fabsl(D.x - C.x) > eps ? C.y + (D.y - C.y) * (sweepX - C.x) / (D.x - C.x) : C.y;
      */
      LD y1 = A.y + (B.y - A.y) * (sweepX - A.x) / (B.x - A.x);
      LD y2 = C.y + (D.y - C.y) * (sweepX - C.x) / (D.x - C.x);
      if (fabsl(y1 - y2) < eps) return id < o.id;
      return y1 < y2;
   }
};
set<segment> status;

// main 
scanf("%d", &n);
for (int i = 0; i < n; ++i) {
  int ax, ay, bx, by;
  scanf("%d%d%d%d", &ax, &ay, &bx, &by);
  seg.pb(mp(pt(ax, ay), pt(bx, by)));
}

while (true) {
  LD rotAngle = rand() / (LD)RAND_MAX * 2.0 * pi;
  bool ok = true;
  for (int i = 0; i < n; ++i) {
     seg[i].first.rotate(rotAngle);
     seg[i].second.rotate(rotAngle);
     if (fabsl(seg[i].first.x - seg[i].second.x) < eps) {
        ok = false;
        break;
     }
  }
  if (ok) break;
}
vector<pair<LD, int> > events;

for (int i = 0; i < n; ++i) {
  if (seg[i].first.x > seg[i].second.x) swap(seg[i].first, seg[i].second);

  events.pb(mp(seg[i].first.x, -i - 1));
  events.pb(mp(seg[i].second.x, +i + 1));
}
sort(all(events));
for (int i = 0; i < 2 * n; ++i) {
  int ty = events[i].second;
  sweepX = events[i].first;
  if (ty < 0) // open
  {
     int id = -ty - 1;
     auto it = status.lower_bound(segment(id));
     if (it != status.begin()) {
        auto oit = it;
        --oit;
        if (intersects(oit->id, id)) {
           printf("YES\n%d %d\n", id + 1, oit->id + 1);
           return 0;
        }
     }
     if (it != status.end() && intersects(id, it->id)) {
        printf("YES\n%d %d\n", id + 1, it->id + 1);
        return 0;
     }
     status.insert(segment(id));
  }
  else // close
  {
     int id = ty - 1;
     auto it = status.lower_bound(segment(id));
     if (it != status.begin() && it != status.end()) {
        auto lit = it; --lit;
        auto rit = it; ++rit;
        if (rit != status.end() && intersects(lit->id, rit->id)) {
           printf("YES\n%d %d\n", lit->id + 1, rit->id + 1);
           return 0;
        }
     }
     status.erase(segment(id));
  }
}
puts("NO");