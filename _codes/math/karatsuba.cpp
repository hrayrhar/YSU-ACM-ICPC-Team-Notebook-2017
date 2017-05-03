LL BASE = 100000;
typedef LL type;
struct poly {
    vector<type> a;
 
    poly() {}
 
    poly(const vector<type> &mas) {
        a = mas;
    }
 
    static void normalize(vector<type> &a) {
        int deg = sz(a) - 1, cur = 0;
        while (cur < deg) cur += cur + 1;
        for (int i = sz(a); i <= cur; ++i) a.pb(0);
    }
 
    void normalize() {
        normalize(a);
    }
 
    void shift(int k) {
        vector<type> b(k + sz(a), 0);
        for (int i = k; i < sz(b); ++i) b[i] = a[i - k];
        a = b;
    }
 
    poly operator + (const poly &o) const {
        poly ret;
        int n = max(sz(a), sz(o.a));
        ret.a.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i < sz(a)) ret.a[i] += a[i];
            if (i < sz(o.a)) ret.a[i] += o.a[i];
        }
        return ret;
    }
 
    poly operator - (const poly &o) const {
        poly ret;
        int n = max(sz(a), sz(o.a));
        ret.a.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i < sz(a)) ret.a[i] += a[i];
            if (i < sz(o.a)) ret.a[i] -= o.a[i];
        }
        return ret;
    }
 
    poly operator * (const poly &o) const {
        poly ret;
        if (sz(a) == 1 && sz(o.a) == 1) {
            ret.a.resize(1);
            ret.a[0] = a[0] * o.a[0];
            return ret;
        }
        int n = max(sz(a), sz(o.a));
        if (n < 100) {
            ret.a.resize(sz(a) - 1 + sz(o.a) - 1 + 1, 0);
            for (int i = 0; i < sz(a); ++i)
                for (int j = 0; j < sz(o.a); ++j) ret.a[i + j] += a[i] * o.a[j];
            return ret;
        }
        vector<type> A(n, 0), B(n, 0);
        for (int i = 0; i < sz(a); ++i) A[i] = a[i];
        for (int i = 0; i < sz(o.a); ++i) B[i] = o.a[i];
        normalize(A);
        normalize(B);
        n = sz(A);
        int h = n / 2;
        vector<type> P1(h), Q1(h), P2(h), Q2(h), S1(h), S2(h);
        for (int i = 0; i < h; ++i) {
            P1[i] = A[i];
            P2[i] = B[i];
            Q1[i] = A[i + h];
            Q2[i] = B[i + h];
            S1[i] = A[i] + A[i + h];
            S2[i] = B[i] + B[i + h];
        }
        poly MP = poly(P1) * poly(P2);
        poly MQ = poly(Q1) * poly(Q2);
        poly PQ = poly(S1) * poly(S2) - MP - MQ;
        MQ.shift(h + h);
        PQ.shift(h);
        return MP + PQ + MQ;
    }
};