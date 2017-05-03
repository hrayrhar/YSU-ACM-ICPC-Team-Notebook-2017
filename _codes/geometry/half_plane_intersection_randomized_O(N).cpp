const LD eps = 1e-8;
 
struct pt {
    LD x, y;
    pt (LD x=0, LD y=0): x(x), y(y) {
    }
     
    void read() {
        int a, b;
        scanf("%d%d", &a, &b);
        x=a;
        y=b;
    }
     
    pt operator + (const pt &o) const {
        return pt(x+o.x, y+o.y);
    }
     
    pt operator - (const pt &o) const {
        return pt(x-o.x, y-o.y);
    }
     
} p[N];
int n;
 
struct Plane {
    LD a, b, c;
    int s;
     
    Plane(LD aa=0, LD bb=0, LD cc=0, int s=0): s(s) {
        LD norm = sqrtl(aa*aa+bb*bb);
        a = aa / norm;
        b = bb / norm;
        c = cc / norm;
    }
};
 
LD dot(pt u, pt v) {
    return u.x * v.x + u.y * v.y;
}
 
LD sign(LD x) {
    if (x < -eps) return -1;
    if (x > +eps) return 1;
    return 0;
}
 
int get_sign(pt A, Plane p) {
    return sign(p.a * A.x + p.b * A.y + p.c);
}
 
struct HalfPlaneIntersection {
     
    vector<Plane> planes;
     
    void init() {
        planes.clear();
        planes.resize(0);
    }
     
    void add(Plane p) {
        if (p.s == 1) {
            p.c -= eps;
        }
        else {
            p.c += eps;
        }
        planes.pb(p);
    }
     
    bool check() {
        random_shuffle(all(planes));
        planes.pb(Plane(1, 0, INF, 1));
        planes.pb(Plane(1, 0, -INF, -1));
        planes.pb(Plane(0, 1, INF, 1));
        planes.pb(Plane(0, 1, -INF, -1));
        reverse(all(planes));
         
        pt cur(-INF, 0);
        for (int iter = 4; iter < sz(planes); ++iter) {
            auto p = planes[iter];
             
            if (get_sign(cur, p) == -p.s) {
                pt dir = pt(-p.b, p.a);
                vector<pt> A, B;
                 
                FOR(i, iter) {
                    auto q = planes[i];
                     
                    LD det = p.a * q.b - p.b * q.a;
                    if (fabsl(det) < eps) continue;
                    LD detx = q.c * p.b - p.c * q.b;
                    LD dety = p.c * q.a - q.c * p.a;
                    pt X = pt(detx/det, dety/det);
                     
                    if (get_sign(X + dir, q) == q.s) {
                        A.pb(X);
                    }
                    else {
                        B.pb(X);
                    }
                }
                 
                // A and B are not empty (note 4 initial half planes)
                pt amax = A[0];
                for (auto P : A) {
                    if (dot(P, dir) > dot(amax, dir)) amax = P;
                }
                 
                pt bmax = B[0];
                for (auto P : B) {
                    if (dot(P, dir) < dot(bmax, dir)) bmax = P;
                }
                 
                if (amax.x < bmax.x) cur = amax;
                else cur = bmax;
                 
                FOR(i, iter+1) {
                    if (get_sign(cur, planes[i]) == -planes[i].s) return false;
                }
            }
        }
         
        return true;
    }
     
} hp;
 
 
bool check(int k) {
    hp.init();
    FOR(i, n) {
        int j=(i+k)%n;
         
        LD a = p[i].y - p[j].y;
        LD b = p[j].x - p[i].x;
        LD c = -a * p[i].x - b * p[i].y;
         
        int z=(i-1+n)%n;
        int s = sign(a*p[z].x + b*p[z].y + c);
         
        hp.add(Plane(a, b, c, s));
    }
    return hp.check();
}