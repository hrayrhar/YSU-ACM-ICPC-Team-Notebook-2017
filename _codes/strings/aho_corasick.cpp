int code(char ch) {
    if (ch >= 'a' && ch <= 'z') return ch - 'a';
    if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;
    assert(ch >= '0' && ch <= '9');
    return ch - '0' + 52;
}

const int A = 64;
const int N = 100007;

struct AC {

    int to[64][N], go[64][N];
    int par[N], dep[N], suff[N];
    int cur_node;
    char pch[N];
    
    // additional information
    int next_term[N], min_len[N];
    bool term[N];
    
    AC() {
        memset(suff, -1, sizeof suff);
        memset(go, -1, sizeof go);
        memset(to, -1, sizeof to);
        cur_node = 1;
    }
    
    void add(string st) {
        int cur = 0;
        for (char symbol : st) {
            int ch = code(symbol);
            if (to[ch][cur] == -1) {
                to[ch][cur] = cur_node++;
            }
            int nxt = to[ch][cur];
            pch[nxt] = ch;
            par[nxt] = cur;
            dep[nxt] = dep[cur] + 1;
            cur = nxt;
        }
        term[cur] = true;
    }
    
    int get_suff(int node) {
        if (node == 0) return 0;
        if (par[node] == 0) return 0;
        if (suff[node] != -1) return suff[node];
        
        int ret = get_go(pch[node], get_suff(par[node]));
        suff[node] = ret;
        return ret;
    }
    
    int get_go(int ch, int node) {
        if (to[ch][node] != -1) return to[ch][node];
        if (go[ch][node] != -1) return go[ch][node];
        if (node == 0) return 0;
        int ret = get_go(ch, get_suff(node));
        go[ch][node] = ret;
        return ret;
    }
    
    void calc_term() {
        
        vector<pair<int, int> > mas;
        FOR(i, cur_node) {
            mas.pb(mp(dep[i], i));
        }
        sort(all(mas));
        for (auto p : mas) {
            int i = p.second;
            next_term[i] = -1;
            int to = get_suff(i);
            if (term[to]) next_term[i] = to;
            else next_term[i] = next_term[to];
        }
        
        for (auto p : mas) {
            int i = p.second;
            min_len[i] = N;
            if (term[i]) min_len[i] = dep[i];
            if (next_term[i] != -1) {
                min_len[i] = min(min_len[i], min_len[next_term[i]]);
            }
        }
    }
    
} ac;