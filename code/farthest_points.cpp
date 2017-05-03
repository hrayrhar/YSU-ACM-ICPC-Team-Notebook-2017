struct pt {
     
    LD x, y;
     
    pt(LD x=0, LD y=0): x(x), y(y) {
     
    }
     
    void read() {
        int a, b;
        scanf("%d%d", &a, &b);
        x = a;
        y = b;
    }
     
    pt operator + (const pt &o) const {
        return pt(x+o.x, y+o.y);
    }
     
    pt operator - (const pt &o) const {
        return pt(x-o.x, y-o.y);
    }
     
    LD dist(const pt &o) const {
        return (x-o.x)*(x-o.x) + (y-o.y)*(y-o.y);
    }
     
    pt prod(LD c) const {
        return pt(c*x, c*y);
    }
     
    bool operator < (const pt &o) const {
        static const LD eps=1e-5;
        if (fabsl(x-o.x) > eps) return x < o.x;
        return y < o.y - eps;
    }
     
}  hull[N];
int n, nhull;
 
LD cross(pt u, pt v) {
    return u.x * v.y - u.y * v.x;
}
 
LD dot(pt u, pt v) {
    return u.x * v.x + u.y * v.y;
}
 
bool ccw(pt A, pt B, pt C) {
    static const LD eps = 1e-5;
    return cross(B-A, C-B) > eps;
}
 
void convex_hull(pt *A, int n) {
    // build convex hull, write answer in (hull, nhull)
}
 
LD dist_from_line(pt A, pt B, pt C) {
    pt u = B-A;
    swap(u.x, u.y);
    u.x = -u.x;
    return fabsl(dot(u, C-A));
}
 
LD get_distance(pt *A, int n) {
    convex_hull(A, n);
 
    LD ret = 0.0;
    int n = nhull;
    pt *A = hull;
     
    if (n <= 3) {
        FOR(i, n) FOR(j, i) {
            ret = max(ret, A[i].dist(A[j]));
        }
        return ret;
    }
     
    int r = 1;
    while(dist_from_line(A[0], A[1], A[(r+1)%n]) > dist_from_line(A[0], A[1], A[r])) r = (r+1) % n;
    ret = max(ret, A[r].dist(A[0]));
     
    for (int i = 1; i < n; ++i) {
        while(dist_from_line(A[i], A[(i+1)%n], A[(r+1)%n]) > dist_from_line(A[i], A[(i+1)%n], A[r])) r = (r+1) % n;
        ret = max(ret, A[r].dist(A[i]));
    }
    return ret;
}