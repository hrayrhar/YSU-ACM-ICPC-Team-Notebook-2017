p[0] = 0;
for (int i = 1; i < n + m + 1; i++) {
    int pos = p[i - 1];
    while (pos>0 && s[pos] != s[i]) pos = p[pos - 1];
    if (s[pos] == s[i]) pos++;
    p[i] = pos;
}
