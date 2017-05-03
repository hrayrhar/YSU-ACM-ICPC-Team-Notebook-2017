void DFT(comp *a, int n) {
   int bitlen = 0;
   while ((1 << bitlen) < n) ++bitlen;
   for (int i = 0; i < n; ++i) {
      int r = rev(i, bitlen);
      if (i < r) swap(a[i], a[r]);
   }
   for (int len = 2; len <= n; len <<= 1) {
      int half = (len >> 1);
      comp wlen(cos(2 * pi / len), sin(2 * pi / len));
      for (int i = 0; i < n; i += len) {
         comp power = 1;
         for (int j = i, l = i, r = i + half; j < i + half; ++j, ++l, ++r, power *= wlen) {
            comp u = a[l], v = power * a[r];
            a[j] = u + v;
            a[j + half] = u - v;
         }
      }
   }
}
 
void inverseDFT(comp *a, int n) {
   DFT(a, n);
   for (int i = 0; i < n; ++i) a[i] /= n;
   reverse(a + 1, a + n);
}