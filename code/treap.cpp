const int N = 100007;
struct node {
   int key, prio, size;
   node *left, *right;
   node() {}
   node(int key, int prio) {
      this->key = key;
      this->prio = prio;
      left = right = 0;
      size = 1;
   }
} *root;
typedef node* pnode;
int n;
LL k, a[N];
 
int getSize(pnode p) {
   return (p ? p->size : 0);
}
 
void fixSize(pnode p) {
   if (p) {
      p->size = getSize(p->left) + 1 + getSize(p->right);
   }
}
 
void split(pnode p, int key, pnode &l, pnode &r) {
   if (!p) {
      l = r = NULL;
   }
   else if (key < p->key) {
      split(p->left, key, l, p->left);
      r = p;
   }
   else {
      split(p->right, key, p->right, r);
      l = p;
   }
   fixSize(p);
}
 
void merge(pnode a, pnode b, pnode &p) {
   if (!a) {
      p = b;
   }
   else if (!b) {
      p = a;
   }
   else if (a->prio > b->prio) {
      merge(a->right, b, a->right);
      p = a;
   }
   else {
      merge(a, b->left, b->left);
      p = b;
   }
   fixSize(p);
}
 
void insert(pnode &p, pnode it) {
   if (!p) {
      p = it;
   }
   else if (it->prio > p->prio) {
      split(p, it->key, it->left, it->right);
      p = it;
   }
   else {
      if (p->key < it->key) {
         insert(p->right, it);
      }
      else {
         insert(p->left, it);
      }
   }
   fixSize(p);
}
 
void insert2(pnode &p, pnode it) {
   pnode a, b;
   split(p, it->key, a, b);
   merge(a, it, a);
   merge(a, b, p);
}
 
pnode find(pnode p, int key) {
   if (!p) {
      return p;
   }
   if (p->key == key) {
      return p;
   }
   if (p->key < key) {
      return find(p->right, key);
   }
   return find(p->left, key);
}
 
void erase(pnode &p, int key) {
   if (!p) {
      return;
   }
   if (p->key == key) {
      merge(p->left, p->right, p);
   }
   else if (p->key < key) {
      erase(p->right, key);
   }
   else {
      erase(p->left, key);
   }
   fixSize(p);
}
 
int getKth(pnode p, int k) {
   assert(p);
   if (getSize(p->left) >= k) {
      return getKth(p->left, k);
   }
   if (getSize(p->left) == k - 1) {
      return p->key;
   }
   return getKth(p->right, k - getSize(p->left) - 1);
}
 
int countSmaller(pnode p, int x) {
   if (!p) {
      return 0;
   }
   if (p->key >= x) {
      return countSmaller(p->left, x);
   }
   return 1 + getSize(p->left) + countSmaller(p->right, x);
}
 
void unite(pnode a, pnode b, pnode &p) {
   if (!a) {
      p = b;
   }
   if (!b) {
      p = b;
   }
   if (a->prio < b->prio) {
      swap(a, b);
   }
   pnode lt, rt;
   split(b, a->key, lt, rt);
   unite(a->left, lt, a->left);
   unite(a->right, rt, a->right);
   fixSize(p);
   p = a;
}
 
void print(pnode p) {
   if (!p) {
      return;
   }
   print(p->left);
   cerr << p->key << " ";
   print(p->right);
}