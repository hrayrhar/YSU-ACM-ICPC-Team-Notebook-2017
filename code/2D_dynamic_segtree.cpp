struct intNode {
    intNode *l, *r;
    int tl, tr;
    LL g;
 
    intNode(int tl = 0, int tr = 0, LL g = 0, intNode *l = NULL, intNode *r = NULL):
        tl(tl), tr(tr), g(g), l(l), r(r) { }
};
typedef intNode* intPnode; 
 
void intCreate(intPnode &T, int tl, int tr) {
    if (!T) T = new intNode(tl, tr);
}
 
LL intValue(intPnode &T) {
    return T == NULL ? 0 : T->g;
}
 
LL intGet(intPnode &T, int tl, int tr, int l, int r) {
    if (T == NULL) return 0;
    //intCreate(T, tl, tr); // eats more useless memory
    if (tl == l && tr == r) return intValue(T);
    int tm = (tl + tr) / 2;
    if (r <= tm) return intGet(T->l, tl, tm, l, r);
    if (l > tm) return intGet(T->r, tm + 1, tr, l, r);
    return gcd(intGet(T->l, tl, tm, l, tm), intGet(T->r, tm + 1, tr, tm + 1, r));
}
 
void intUpdate(intPnode &T, int tl, int tr, int pos, LL val, bool multipleLines = false, intPnode lson = NULL, intPnode rson = NULL) {
    intCreate(T, tl, tr);
    if (tl == tr) {
        if (!multipleLines) T->g = val;
        else {
            LL left = intGet(lson, 0, N, tl, tr);
            LL right = intGet(rson, 0, N, tl, tr);
            T->g = gcd(left, right);
        }
        return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm) intUpdate(T->l, tl, tm, pos, val, multipleLines, lson, rson);
    else intUpdate(T->r, tm + 1, tr, pos, val, multipleLines, lson, rson);
    T->g = gcd(intValue(T->l), intValue(T->r));
}
 
struct extNode {
    extNode *l, *r;
    int tl, tr;
    intNode *root;
 
    extNode(int tl = 0, int tr = 0, intNode *root = NULL, extNode *l = NULL, extNode *r = NULL) :
        tl(tl), tr(tr), root(root), l(l), r(r) { }
};
typedef extNode* extPnode;
extPnode root;
 
void extCreate(extPnode &T, int tl, int tr) {
    if (!T) T = new extNode(tl, tr);
}
 
LL extGet(extPnode &T, int tl, int tr, int lx, int rx, int ly, int ry) {
    if (T == NULL) return 0;
    //extCreate(T, tl, tr); // eats more useless memory
    if (tl == lx && tr == rx) return intGet(T->root, 0, N, ly, ry);
    int tm = (tl + tr) / 2;
    if (rx <= tm) return extGet(T->l, tl, tm, lx, rx, ly, ry);
    if (lx > tm) return extGet(T->r, tm + 1, tr, lx, rx, ly, ry);
    return gcd(extGet(T->l, tl, tm, lx, tm, ly, ry), extGet(T->r, tm + 1, tr, tm + 1, rx, ly, ry));
}
 
void extUpdate(extPnode &T, int tl, int tr, int x, int y, LL val) {
    extCreate(T, tl, tr);
    if (tl == tr) {
        intUpdate(T->root, 0, N, y, val);
        return;
    }
    int tm = (tl + tr) / 2;
    if (x <= tm) extUpdate(T->l, tl, tm, x, y, val);
    else extUpdate(T->r, tm + 1, tr, x, y, val);
    intUpdate(T->root, 0, N, y, val, true, T->l ? T->l->root : NULL, T->r ? T->r->root : NULL);
}