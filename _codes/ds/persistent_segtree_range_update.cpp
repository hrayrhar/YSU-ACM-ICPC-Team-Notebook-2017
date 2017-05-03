struct node
{
    node *l, *r;
    int sum, add;
 
    node(int sum = 0, int add = 0) : sum(sum), add(add), l(NULL), r(NULL) { } // creates a leaf
 
    node(node *left, node *right) // creates a node
    {
        add = 0;
        sum = 0;
        l = left;
        r = right;
    }
};
typedef node* pnode;
 
inline int get(pnode T, int tl, int tr)
{
    if (!T)
    {
        return 0;
    }
    return T->add * (tr - tl + 1) + T->sum;
}
 
inline void fix(pnode &T, int tl, int tr)
{
    int tm = (tl + tr) / 2;
    T->sum = get(T->l, tl, tm) + get(T->r, tm + 1, tr);
}
 
pnode push(pnode &T, int tl, int tr)
{
    pnode ret = new node();
    if (T->l)
    {
        ret->l = new node(T->l->l, T->l->r);
        ret->l->add = T->l->add;
        ret->l->sum = T->l->sum;
        ret->l->add += T->add;
    }
    if (T->r)
    {
        ret->r = new node(T->r->l, T->r->r);
        ret->r->add = T->r->add;
        ret->r->sum = T->r->sum;
        ret->r->add += T->add;
    }
    ret->sum = T->sum + (tr - tl + 1) * T->add;
    ret->add = 0;
    return ret;
}
 
pnode build(int a[], int tl, int tr)
{
    if (tl == tr)
    {
        return new node(a[tl], 0);
    }
    int tm = (tl + tr) / 2;
    pnode ret = new node(build(a, tl, tm), build(a, tm + 1, tr));
    fix(ret, tl, tr);
    return ret;
}
 
pnode rsq(pnode &T, int tl, int tr, int l, int r, int &s)
{
    pnode ret = push(T, tl, tr);
    if (tl == l && tr == r)
    {
        s = ret->sum;
        return ret;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm)
    {
        ret->l = rsq(ret->l, tl, tm, l, r, s);
    }
    else if (l > tm)
    {
        ret->r = rsq(ret->r, tm + 1, tr, l, r, s);
    }
    else
    {
        int s1, s2;
        ret->l = rsq(ret->l, tl, tm, l, tm, s1);
        ret->r = rsq(ret->r, tm + 1, tr, tm + 1, r, s2);
        s = s1 + s2;
    }
    fix(T, tl, tm);
    return ret;
}
 
pnode update(pnode &T, int tl, int tr, int l, int r, int delta)
{
    if (tl == l && tr == r)
    {
        pnode ret = new node(T->l, T->r);
        ret->add = T->add + delta;
        ret->sum = T->sum;
        return ret;
    }
    int tm = (tl + tr) / 2;
    pnode ret = push(T, tl, tr);
    if (r <= tm)
    {
        ret = new node(update(ret->l, tl, tm, l, r, delta), ret->r);
    }
    else if (l > tm)
    {
        ret = new node(ret->l, update(ret->r, tm + 1, tr, l, r, delta));
    }
    else
    {
        ret = new node(update(ret->l, tl, tm, l, tm, delta), update(ret->r, tm + 1, tr, tm + 1, r, delta));
    }
    fix(ret, tl, tr);
    return ret;
}