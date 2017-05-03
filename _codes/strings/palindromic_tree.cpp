struct node {
   int len, suff;
   int to[2]; // size of the alphabet
 
   node() {
      to[0] = to[1] = -1;
      suff = -1;
      len = -1;
   }
 
} T[N];
int size = 2; // 0 -> -1  |   1 -> e
int maxPal = 0;
char st[N], ans[N];
 
bool addChar(int i, int c) {
   bool ret = false;
   while (true) {
      int curLen = T[maxPal].len;
      if (st[i] == st[i - curLen - 1]) {
         int v;
         if (T[maxPal].to[c] == -1) {
            v = size++;
            T[maxPal].to[c] = v;
            T[v].len = curLen + 2;
            ret = true;
         }
         else v = T[maxPal].to[c];
 
         if (T[v].len == 1) T[v].suff = 1;
         else {
            while (true) {
               maxPal = T[maxPal].suff;
               if (st[i] == st[i - T[maxPal].len - 1]) {
                  T[v].suff = T[maxPal].to[c];
                  break;
               }
            }
         }
         maxPal = v;
         break;
      }
      maxPal = T[maxPal].suff;
   }
   return ret;
}
 
 
// init 
T[1].len = 0;
T[1].suff = 0; // e -> "-1"
