ector<int> d[N];
int cur, used[N];
bool is[N];
int gen[N];
 
void sieve() {
    fill(is + 2, is + N, true);
    for (int i = 2; i < 200; ++i)
        if (is[i]) for (int j = i * i; j < N; j += i)
            is[j] = false;
    for (int i = 0; i < N; ++i)
        if (is[i]) for (int j = i; j < N; j += i) d[j].pb(i);
}
 
int power(int a, int n, int MOD) {
    int res = 1;
    while (n) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}
 
int findGenerator(int p) {
    if (gen[p]) return gen[p];
    ++cur;
    while (true) {
        int g = rand() % (p - 1) + 1;
        if (used[g] == cur) continue;
        used[g] = cur;
        bool ok = true;
        for (int i = 0; i < sz(d[p - 1]); ++i) {
            int t = d[p - 1][i];
            if (power(g, (p - 1) / t, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return (gen[p] = g);
    }
}