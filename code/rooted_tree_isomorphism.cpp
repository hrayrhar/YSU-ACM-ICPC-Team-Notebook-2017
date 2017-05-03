// Slow string implementation
 
string dfsSlow(int root, int par, vector<int> *G) {
    vector<string> childs;
    for (int to : G[root]) {
        if (to != par) childs.pb(dfsSlow(to, root, G));
    }
    sort(all(childs));
    string cur = "(";
    for (auto s : childs) cur += s;
    cur += ")";
    return cur;
}
 
// fast algorithm, DETERMINISTIC
 
map<vector<int>, int> ID;
int curid = 0;
 
int getId(vector<int> &v) {
    if (ID.count(v)) return ID[v];
    ID[v] = curid++;
    return curid - 1;
}
 
int dfs(int root, int par, set<int> *G) {
    vector<int> childs;
    for (int to : G[root]) {
        if (to != par) childs.pb(dfs(to, root, G));
    }
    sort(all(childs));
    return getId(childs);
}
 
// faster algorithm: vector<int>'s in map is slow
// we will hash that vectors then add hashes to the map
 
map<LL, int> ID;
int curid = 0;
 
LL getVectorHash(vector<int> &v) {
    static const LL P = 1000003;
    LL h = 1;
    for (int u : v) h = h * P + u;
    return h;
}
 
int getId(vector<int> &v) {
    LL h = getVectorHash(v);
    if (ID.count(h)) return ID[h];
    ID[h] = curid++;
    return curid - 1;
}
 
int dfs(int root, int par, set<int> *G) {
    vector<int> childs;
    for (int to : G[root]) {
        if (to != par) childs.pb(dfs(to, root, G));
    }
    sort(all(childs));
    return getId(childs);
}