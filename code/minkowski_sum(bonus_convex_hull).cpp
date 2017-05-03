const LD pi = acosl(-1.0);
const LD eps = 1e-11;
const int N = 250007;
 
#define vect pt
struct pt {
    LL x, y;
    pt() : x(0), y(0) { }
    pt(LL x, LL y) : x(x), y(y) {}
 
    pt operator + (const pt &o) const {
        return pt(x + o.x, y + o.y);
    }
 
    pt operator - (const pt &o) const {
        return pt(x - o.x, y - o.y);
    }
 
    bool operator < (const pt &o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
 
    LD len() const {
        return sqrtl((LD)x * x + (LD)y * y);
    }
 
    pt rotate() const {
        return pt(y, -x);
    }
};
vector<pt> mas[N];
LL ans = 0;
 
LD get_angle(LD ux, LD uy, LD x, LD y) {
    LD l1 = sqrtl(ux * ux + uy * uy);
    LD l2 = sqrtl(x * x + y * y);
    if (l1 < eps || l2 < eps) return 2 * pi;
    LD t = (ux * x + uy * y) / l1 / l2;
    if (t < -1.0 + eps) return pi;
    if (t > 1.0 - eps) return 0;
    return acosl(t);
}
 
void minkowski_sum(int na, pt *A, int nb, pt *B, int &nc, pt *C) {
    int posa = 0;
    FOR(i, na) {
        if (A[i].x > A[posa].x || (A[i].x == A[posa].x && A[i].y > A[posa].y)) posa = i;
    }
    int posb = 0;
    FOR(i, nb) {
        if (B[i].x > B[posb].x || (B[i].x == B[posb].x && B[i].y > B[posb].y)) posb = i;
    }
    nc = 0;
    C[nc++] = A[posa] + B[posb];
    LD rot = 0.0;
    while (true) {
        int nposa = (posa + 1) % na;
        int nposb = (posb + 1) % nb;
        vect ua = vect(A[nposa].x - A[posa].x, A[nposa].y - A[posa].y).rotate();
        vect ub = vect(B[nposb].x - B[posb].x, B[nposb].y - B[posb].y).rotate();
 
        if (na == 3 && nb == 2 && rot > 0) {
            cerr << ua.x << " " << ua.y << " " << cosl(rot) << sinl(rot) << endl;
        }
        LD anga = get_angle(0.0 + ua.x, 0.0 + ua.y, cosl(rot), sinl(rot));
        LD angb = get_angle(0.0 + ub.x, 0.0 + ub.y, cosl(rot), sinl(rot));
 
        if (anga < angb) {
            rot += anga;
            posa = nposa;
        }
        else {
            rot += angb;
            posb = nposb;
        }
        if (rot > 2 * pi - eps) break;
        C[nc++] = A[posa] + B[posb];
    }
}
 
pt tmp[N], H[N];
pt A[N], B[N], C[N];
int na, nb, nc;
 
LL cross(vect a, vect b) {
    return a.x * b.y - a.y * b.x;
}
 
bool ccw(pt A, pt B, pt C) {
    return cross(B - A, C - B) > 0;
}
 
void convex_hull(int &na, pt *A) {
    if (na <= 2) return;
    int nh = 0;
    sort(A, A + na);
    int ptr = 0;
    FOR(i, na) {
        while (ptr >= 2 && !ccw(tmp[ptr - 2], tmp[ptr - 1], A[i])) --ptr;
        tmp[ptr++] = A[i];
    }
    FOR(i, ptr - 1) H[nh++] = tmp[i];
    ptr = 0;
    for (int i = na - 1; i >= 0; --i) {
        while (ptr >= 2 && !ccw(tmp[ptr - 2], tmp[ptr - 1], A[i])) --ptr;
        tmp[ptr++] = A[i];
    }
    FOR(i, ptr - 1) H[nh++] = tmp[i];
    na = nh;
    FOR(i, na) A[i] = H[i];
}
 
void solvefor(int l, int r) {
    if (l == r) return;
 
    int m = (l + r) / 2;
    solvefor(l, m);
    solvefor(m + 1, r);
 
    na = 0;
    for (int i = l; i <= m; ++i) {
        for (pt P : mas[i]) A[na++] = P;
    }
    nb = 0;
    for (int i = m + 1; i <= r; ++i) {
        for (pt P : mas[i]) B[nb++] = pt(-P.x, -P.y);
    }
    convex_hull(na, A);
    convex_hull(nb, B);
 
    if (na == 0 || nb == 0) return;
 
    minkowski_sum(na, A, nb, B, nc, C);
    FOR(i, nc) {
        ans = max(ans, C[i].x * C[i].x + C[i].y * C[i].y);
    }
}
