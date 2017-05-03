// dp[i][j] = Min_{k < j}{dp[i-1][k] + cost(k, j)}
// if opt[i-1][j] <= opt[i][j] <= opt[i][j+1]

int dp[N][N];
int opt[N][N];

int cost(int l, int r) {
    // ...
}

void solve() {
    
    FOR(k, N) FOR(i, N) {
        dp[k][i] = INF;
    }
    dp[0][0] = 0;
    for (int i = 0; i <= n; ++i) {
        opt[0][i] = 1;
    }
    for (int k = 1; k <= n; ++k) {
        dp[k][0] = 0;
        opt[k][0] = 1;
        opt[k][n+1] = n;
        for (int i = n; i >= 1; --i) {
            for (int j = opt[k-1][i]; j <= opt[k][i+1]; ++j) {
                int val = dp[k-1][j-1] + cost(j, i);
                if (val < dp[k][i]) {
                    dp[k][i] = val;
                    opt[k][i] = j;
                }
            }
        }   
    }
}
