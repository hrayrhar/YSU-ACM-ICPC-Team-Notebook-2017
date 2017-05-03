const int N = 1000007;
struct node {
   int pr, size;
   int val;
   node *l, *r;
 
   node(int pr = 0, int val = 0, node *l = NULL, node *r = NULL) :
      pr(pr), l(l), r(r), size(1), val(val) {
   }
} *root;
typedef node* pnode;
int cur, prio[N];
 
inline int getSize(pnode T) {
   return (T ? T->size : 0);
}
 
inline void fix(pnode &T) {
   if (!T) {
      return;
   }
   T->size = getSize(T->l) + getSize(T->r) + 1;
}
 
void merge(pnode A, pnode B, pnode &T) {
   if (!A || !B) {
      T = (A ? A : B);
   }
   else if (A->pr > B->pr) {
      merge(A->r, B, A->r);
      T = A;
   }
   else {
      merge(A, B->l, B->l);
      T = B;
   }
   fix(T);
}
 
void split(pnode T, int x, pnode &LT, pnode &RT, int add = 0) {
   if (!T) {
      LT = RT = 0;
      return;
   }
   int curx = add + getSize(T->l);
   if (x <= curx) {
      split(T->l, x, LT, T->l, add);
      RT = T;
   }
   else {
      split(T->r, x, T->r, RT, add + 1 + getSize(T->l));
      LT = T;
   }
   fix(LT);
   fix(RT);
}