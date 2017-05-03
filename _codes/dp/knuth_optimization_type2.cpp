// dp[i][j] = Min_{i < k < j} { dp[i][k] + dp[k+1][j] + cost(i, j) }
// if opt[l][r-1] <= opt[l][r] <= opt[l+1][r]

LL dp[N][N];
int opt[N][N];


int cost(int l, int r) {
    // ...
}

void solve() {
    
    for (int l = n-1; l >= 0; --l) {
        dp[l][l] = 0; 
        opt[l][l] = l;
        
        if (l+1 < n) {
            dp[l][l+1] = cost(l, l+1);
            opt[l][l+1] = l;
        }
        
        for (int r = l+2; r < n; ++r) {
            dp[l][r] = INF;
            
            int L = opt[l][r-1];
            int R = opt[l+1][r];
            
            for (int j = L; j <= R; ++j) {
                int val = dp[l][j] + dp[j+1][r] + getsum(l, r);
                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    opt[l][r] = j;
                }
            }
        }
    }
}