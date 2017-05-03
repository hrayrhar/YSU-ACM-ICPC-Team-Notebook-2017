// g ^ x = a (mod p)
int discreteLog(int g, int a, int p) {
    int s = (int)sqrt(p + 0.0);
    vector<pair<int, int> > A, B;
    int gs = power(g, s, p), cur = 1;
    for (int t = 0; t * s < p - 1; ++t, cur = cur * gs % p) {
        A.pb(mp(cur, t));
    }
    int invg = power(g, p - 2, p);
    cur = a;
    for (int i = 0; i < s; ++i, cur = cur * invg % p) {
        B.pb(mp(cur, i));
    }
    sort(all(A));
    sort(all(B));
    int i = 0, j = 0;
    while (i < sz(A) && j < sz(B)) {
        if (A[i].first == B[j].first) return A[i].second * s + B[j].second;
        if (A[i].first < B[j].first) ++i;
        else ++j;
    }
    assert(false);
}

// to find square root

int g = findGenerator(p);
int r = discreteLog(g, a, p);
if (r & 1) puts("No root");
else {
    int x1 = power(g, r / 2, p);
    int x2 = p - x1;
    if (x1 > x2) swap(x1, x2);
    if (x1 == x2) {
        assert(p == 2);
        puts("1");
    }
    else printf("%d %d\n", x1, x2);
}