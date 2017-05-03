n = (int)s.size();
z.resize(n, 0);
z[0] = 0;
for (i = 1; i < n; i++) {
  if (r >= i) {
     z[i] = min(z[i - l], r - i + 1);
  }
  while (z[i] + i < n && s[z[i] + i] == s[z[i]]) z[i]++;
  if (i + z[i] - 1 > r) {
     l = i;
     r = i + z[i] - 1;
  }
}