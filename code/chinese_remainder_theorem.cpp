int power(int a, int b, int mod) {
    if (b == 0) return 1;
    if (b & 1) return (a * power(a, b - 1, mod)) % mod;
    int ret = power(a, b >> 1, mod);
    return (ret * ret) % mod;
}
 
int getInverse(int a, int mod) {
    a %= mod;
    return power(a, mod - 2, mod);
}
 
LL solve(vector<int> p, vector<int> r) {
    LL M = 1;
    int n = sz(p);
    for (int i = 0; i < n; ++i) M *= p[i];
    vector<vector<int> > inv(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j) inv[i][j] = getInverse(p[i], p[j]);
    vector<LL> x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = r[i];
        for (int j = 0; j < i; ++j) {
            x[i] = (x[i] - x[j]) * inv[j][i];
            x[i] %= p[i];
            if (x[i] < 0) x[i] += p[i];
        }
    }
    LL ret = 0;
    LL cur = 1;
    for (int i = 0; i < n; ++i) {
        ret += x[i] * cur;
        cur *= p[i];
        ret %= M;
        cur %= M;
    }
    return ret;
}