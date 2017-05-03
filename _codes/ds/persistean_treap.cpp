struct node {
    node *l, *r;
    bool rev;
    int size;
    char data;
 
    node(char data = 'a') : data(data) {
        l = r = NULL;
        rev = false;
        size = 1;
    }
};
typedef node* pnode;
 
const int N = 200007;
char st[N];
 
pnode copyNode(pnode other) {
    if (other == NULL) return NULL;
    pnode ret = new node();
    ret->l = other->l;
    ret->r = other->r;
    ret->rev = other->rev;
    ret->size = other->size;
    ret->data = other->data;
    return ret;
}
 
int getSize(pnode T) {
    return T ? T->size : 0;
}
 
void fix(pnode T) {
    if (T) T->size = 1 + getSize(T->l) + getSize(T->r);
}
 
void push(pnode &T) {
    if (!T->rev) return;
    T->l = copyNode(T->l);
    T->r = copyNode(T->r);
    swap(T->l, T->r);
    T->rev = false;
    if (T->l) T->l->rev ^= 1;
    if (T->r) T->r->rev ^= 1;
}
 
void split(pnode T, int cnt, pnode &L, pnode &R) {
    if (!T) {
        L = R = NULL;
        return;
    }
    pnode cur = copyNode(T);
    push(cur);
    if (getSize(cur->l) >= cnt) {
        split(cur->l, cnt, L, cur->l);
        R = cur;
    }
    else {
        split(cur->r, cnt - 1 - getSize(cur->l), cur->r, R);
        L = cur;
    }
    fix(L);
    fix(R);
}
 
void merge(pnode L, pnode R, pnode &T) {
    if (!L || !R) {
        T = copyNode((L ? L : R));
        return;
    }
    int lsize = getSize(L);
    int rsize = getSize(R);
    if (rand() % (lsize + rsize) < lsize) {
        T = copyNode(L);
        push(T);
        merge(T->r, R, T->r);
    }
    else {
        T = copyNode(R);
        push(T);
        merge(L, T->l, T->l);
    }
    fix(T);
}
 
void print(pnode T) {
    if (!T) return;
    push(T);
    print(T->l);
    putchar(T->data);
    print(T->r);
}
 