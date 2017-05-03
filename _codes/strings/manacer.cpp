n = strlen(st);
   int l = 0, r = -1;
   for (int i = 0; i < n; ++i) {
      d1[i] = 1;
      if (i <= r) d1[i] = min(d1[l + (r - i)], r - i + 1);
      while (i + d1[i] < n && i - d1[i] >= 0 && st[i + d1[i]] == st[i - d1[i]]) ++d1[i];
      if (i + d1[i] - 1 > r) {
         l = i - d1[i] + 1;
         r = i + d1[i] - 1;
      }
   }
   l = 0, r = -1;
   for (int i = 0; i < n; ++i) {
      d2[i] = 0;
      if (i <= r) d2[i] = min(d2[l + (r - i) + 1], r - i + 1);
      while (i + d2[i] < n && i - d2[i] - 1 >= 0 && st[i + d2[i]] == st[i - d2[i] - 1]) ++d2[i];
      if (i + d2[i] - 1 > r) {
         l = i - d2[i] + 1 - 1;
         r = i + d2[i] - 1;
      }
   }
