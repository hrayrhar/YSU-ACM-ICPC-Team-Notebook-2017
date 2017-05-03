/***  O(MOD) methods to precalculate all inverses
a)
    r[1] = 1;
    for (int i=2; i<m; ++i)
        r[i] = (m - (m/i) * r[m%i] % m) % m;

b)
    r[a*b] = r[a] * r[b] // O(1)
    r[p] = power(p, MOD-2) // O(log(MOD))
    total: O(MOD)
***/
 
const LL MOD = 1000000000 + 7LL;
const int N = 2000007;
 
LL f[N], invf[N];
int lp[N];
int pr_cnt, pr[N];
 
void sieve() {
    lp[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (lp[i] == 0) {
            pr[pr_cnt++] = i;
            lp[i] = i;
        }
        for (int j = 0; j < pr_cnt && pr[j] <= lp[i] && pr[j] * i < N; ++j) {
            lp[pr[j] * i] = pr[j];
        }
    }
}
 
LL power(LL a, LL b) {
    if (b == 0) return 1;
    if (b & 1) return a * power(a, b-1) % MOD;
    LL r = power(a, b >> 1);
    return r * r % MOD;
}
 
inline LL inv(LL a) {
    return power(a, MOD-2);
}
 
inline LL C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return f[n] * invf[k] % MOD * invf[n-k] % MOD;
}
 
void precalc() {
    f[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = i * f[i-1] % MOD;
    }
    sieve();
    for (int i = 1; i < N; ++i) {
        if (lp[i] == i) invf[i] = inv(i);
        else invf[i] = invf[i / lp[i]] * invf[lp[i]] % MOD;
    }
    invf[0] = 1;
    for (int i = 1; i < N; ++i) {
        invf[i] = invf[i] * invf[i-1] % MOD;
    }
}