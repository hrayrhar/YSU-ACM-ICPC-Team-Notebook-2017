// dp[i][j] = min_{k<j}{ dp[i-1][k] + cost(k,j) }
// if opt[i][j] <= opt[i][j+1]

int dp[N][N];

int cost(int l, int r) {
    // ...
}

void calcdp(int k, int l, int r, int optl, int optr) {
    if (l > r) return;
    
    int m = (l+r) / 2;
    int best = INF;
    int pos = -1;
    
    for (int j = optl; j <= min(m, optr); ++j) {
        int val = dp[k-1][j-1] + cost(j, m);
        if (val < best) {
            best = val;
            pos = j;
        }
    }
    
    dp[k][m] = best;
    
    calcdp(k, l, m-1, optl, pos);
    calcdp(k, m+1, r, pos, optr);
}

scanf("%d", &n);
for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
}
}
// init 
for (int k = 1; k <= n; ++k) {
    // init ?
    calcdp(k, 1, n, 1, n);
}