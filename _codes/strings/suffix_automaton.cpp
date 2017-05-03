const int N = 100007;
const int A = 26;
struct node {
   int len, link;
   int nxt[A];
 
} V[2 * N];
bool terminal[2 * N];
int size, last;
char *st;
 
void prepare() {
   size = 1;
   last = 0;
   V[0].link = -1;
   V[0].len = 0;
   for (int i = 0; i < 2 * N; ++i) {
      fill(V[i].nxt, V[i].nxt + A, -1);
   }
   fill(terminal, terminal + 2 * N, false);
}
 
void addchar(int c) {
   int cur = size++;
   V[cur].len = V[last].len + 1;
   int now = last;
   for (; now != -1 && V[now].nxt[c] == -1; now = V[now].link) {
      V[now].nxt[c] = cur;
   }
   if (now == -1) {
      V[cur].link = 0;
   }
   else {
      int to = V[now].nxt[c];
      if (V[to].len == V[now].len + 1) {
         V[cur].link = to;
      }
      else {
         int clone = size++;
         V[clone].len = V[now].len + 1;
         for (int i = 0; i < A; ++i) {
            V[clone].nxt[i] = V[to].nxt[i];
         }
         V[clone].link = V[to].link;
         for (; now != -1 && V[now].nxt[c] == to; now = V[now].link) {
            V[now].nxt[c] = clone;
         }
         V[cur].link = clone;
         V[to].link = clone;
      }
   }
 
   last = cur;
}
 
void build(char *str) {
   st = str;
   int n = strlen(st);
   prepare();
   for (int i = 0; i < n; ++i) {
      addchar(st[i] - 'a');
   }
}
 
void markTerminals() {
   for (int cur = last; cur != -1; cur = V[cur].link) {
      terminal[cur] = true;
   }
}