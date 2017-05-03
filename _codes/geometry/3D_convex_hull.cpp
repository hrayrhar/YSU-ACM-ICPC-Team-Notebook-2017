const int N = 1007;
const LD pi = acosl(-1.0);
const LD eps = 1e-9;
const LD INF = 1e18;
 
struct pt {
    LD x, y, z;
     
    pt (LD x=0, LD y=0, LD z=0): x(x), y(y), z(z) {
    }
 
    void read() {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        x = a;
        y = b;
        z = c;
    }
 
    void print() {
        cerr << "( " << x << " " << y << " " << z << " ) ";
    }
 
    pt operator + (const pt &o) const {
        return pt(x+o.x, y+o.y, z+o.z);
    }
 
    LD dist2(const pt &o) const {
        return sqrt((x-o.x)*(x-o.x) + (y-o.y)*(y-o.y));
    }
 
    pt operator - (const pt &o) const {
        return pt(x-o.x, y-o.y, z-o.z);
    }
 
    pt operator * (LD c) const {
        return pt(x*c, y*c, z*c);
    }
 
    pt operator / (LD c) const {
        return pt(x/c, y/c, z/c);
    }
 
    LD len() const {
        return sqrtl(x*x + y*y + z*z);
    }
 
    pt normalize() const {
        return *this * (1.0 / len());
    }
 
    pt to_len(LD need_len) const {
        return this->normalize() * need_len;
    }
 
    bool operator < (const pt &o) const {
        if (fabsl(x-o.x) > eps) return x < o.x;
        if (fabsl(y-o.y) > eps) return y < o.y;
        return z < o.z - eps;
    }
};
 
LD det(LD a, LD b, LD c, LD d) {
    return a*d - b*c;
}
 
LD dot(pt u, pt v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
 
pt cross(pt u, pt v) {
    return pt(det(u.y, u.z, v.y, v.z),
             -det(u.x, u.z, v.x, v.z),
              det(u.x, u.y, v.x, v.y));
}
 
vector<pt> p;
 
struct plane {
    LD a, b, c, d;
    pt A, B, C;
    int i, j, k;
 
    plane(LD a=0, LD b=0, LD c=0, LD d=0): a(a), b(b), c(c), d(d) {
        // note A, B, C stay undefined
    }
 
    plane(int i, int j, int k): A(p[i]), B(p[j]), C(p[k]), i(i), j(j), k(k) {
        pt norm = cross(B-A, C-A).normalize();
        a = norm.x;
        b = norm.y;
        c = norm.z;
        d = -a * A.x - b * A.y - c * A.z;
    }
};
 
 
LD dist_from_plane(pt A, plane& t) {
    return (A.x * t.a + A.y * t.b + A.z * t.c + t.d) / sqrtl(t.a*t.a + t.b*t.b + t.c*t.c);
}
 
LD sign(LD x) {
    if (x < -eps) return -1;
    if (x > eps) return 1;
    return 0;
}

bool inside(pt A, vector<plane>& faces, pt O) {
    for (auto t : faces) {
        int need_sign = sign(dist_from_plane(O, t));
        int cur_sign = sign(dist_from_plane(A, t));
        if (need_sign * cur_sign == -1) return false;
    }
    return true;
}
 
void dfs(int u, vector<vector<int> >& G, vector<bool>& used, vector<int>& order) {
    order.pb(u);
    used[u] = true;
    for (auto to : G[u]) {
        if (!used[to]) {
            dfs(to, G, used, order);
        } 
    }
}
 
void solve() {
    int n;
    scanf("%d", &n);
     
    p.resize(n);
    FOR(i, n) {
        p[i].read();
    }
 
    vector<plane> faces;
    FOR(i, 4) FOR(j, i) FOR(k, j) {
        faces.pb(plane(i, j, k));
    }
 
    pt O = (p[0] + p[1] + p[2] + p[3]) / 4.0; // point strictly inside
 
    for (int ptr = 4; ptr < n; ++ptr) {
        auto P = p[ptr];
        if (inside(P, faces, O)) continue;
 
        vector<plane> new_faces;
        vector<plane> to_delete;
 
        FOR(i, sz(faces)) {
            int need_sign = sign(dist_from_plane(O, faces[i]));
            int cur_sign = sign(dist_from_plane(P, faces[i]));
            if (cur_sign * need_sign != -1) {
                new_faces.pb(faces[i]);
            }
            else {
                to_delete.pb(faces[i]);
            }
        }
 
        unordered_map<int, int> M;
 
        for (auto t : to_delete) {
            int i = t.i;
            int j = t.j;
            int k = t.k;
            M[min(i, j) * N + max(i,j)] += 1;
            M[min(i, k) * N + max(i,k)] += 1;
            M[min(k, j) * N + max(k,j)] += 1;
        }
 
        vector<vector<int> > G(n);
        int some_vertex = -1;
        for (auto pr : M) {
            if (pr.second >= 2) continue;
            int i = pr.first / N;
            int j = pr.first % N;
            some_vertex = i;
            G[i].pb(j);
            G[j].pb(i);
        }
        assert(some_vertex != -1);
        vector<bool> used(ptr, false);
        vector<int> order;
        dfs(some_vertex, G, used, order);
 
        vector<plane> to_add;
        FOR(i, sz(order)) {
            int j = (i+1)%sz(order);
            int u = order[i];
            int v = order[j];
            to_add.pb(plane(ptr, u, v));
        }
 
        for (auto t : to_add) {
            new_faces.pb(t);
        }
        faces = new_faces;
    }
 
}