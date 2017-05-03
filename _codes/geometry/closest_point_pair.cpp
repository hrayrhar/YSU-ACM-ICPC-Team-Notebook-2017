struct point {
   double x, y;
   int ind;
   double operator + (const point & a) const
   {
      return sqrt((a.x - x) * (a.x - x) + (a.y - y) * (a.y - y));
   }
} p[100007], temp[100007]; // temp for merge
double best = 1e18;
int n, ind1, ind2;
 
bool cmp1(const point & a, const point & b)  // sort by x
{
   return (a.x < b.x || (a.x == b.x && a.y < b.y));
}
 
bool cmp2(const point & a, const point & b)  // sort by y
{
   return (a.y < b.y || (a.y == b.y && a.x < b.x));
}

void merge(int l, int r) // merge for merge_sort by y
{
   int m = (l + r) / 2, i = l, j = m + 1, k;
   for (k = l; k <= r; ++k) {
      if (i > m) {
         temp[k] = p[j++];
      }
      else if (j > r) {
         temp[k] = p[i++];
      }
      else if (cmp2(p[i], p[j])) {
         temp[k] = p[i++];
      }
      else {
         temp[k] = p[j++];
      }
   }
   for (k = l; k <= r; ++k) {
      p[k] = temp[k];
   }
}
 
void update(int i, int j) {
   double dis = p[i] + p[j];
   if (dis < best) {
      best = dis;
      ind1 = p[i].ind;
      ind2 = p[j].ind;
      if (ind1 > ind2) {
         swap(ind1, ind2);
      }
   }
}
 
void solve(int l, int r) {
   double midx;
   int i, j, m;
   if (r - l <= 3)
   {
      for (i = l; i <= r; ++i) {
         for (j = i + 1; j <= r; ++j) {
            update(i, j);
         }
      }
      sort(p + l, p + r + 1, cmp2);
      return;
   }
   m = (l + r) / 2;
   midx = p[m].x;
   solve(l, m);
   solve(m + 1, r);
   merge(l, r);

   static int t[100007];
   int tsz = 0;
   for (i = l; i <= r; ++i) {
      if (fabs(p[i].x - midx) < best) {
         j = tsz - 1;
         while (j >= 0 && p[i].y - p[t[j]].y < best) {
            update(i, t[j]);
            j--;
         }
         t[tsz++] = i;
      }
   }
 
}
 
// run
scanf("%d", &n);
sort(p, p + n, cmp1);
solve(0, n - 1);