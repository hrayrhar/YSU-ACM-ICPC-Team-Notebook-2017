struct DSU_withRollbacks {
   int *par, *size;
   int n, ncomps;
 
   enum { PAR, SIZE, NCOMPS };
    
   struct Change {
      int type, index, oldValue;
      Change() {}
      Change(int type, int index, int oldValue) : type(type), index(index), oldValue(oldValue) {}
   } *changes;
   int top;
    
   void init(int n) {
      this->n = n;
      par = new int [n];
      size = new int [n];
      changes = new Change[2 * n];
      ncomps = n;
      top = 0;
      FOR(i, n) {
         par[i] = i;
         size[i] = 1;
      }
   }
 
   int get(int i) {
      if (par[i] == i) return i;
      return get(par[i]);
   }   
    
   void unite(int i, int j) {
      i = get(i);
      j = get(j);
      if (i == j) return;
      if (size[i] < size[j]) swap(i, j);
       
      changes[top++] = Change(PAR, j, par[j]);
      changes[top++] = Change(SIZE, i, size[i]);
      changes[top++] = Change(NCOMPS, -1, ncomps);
       
      size[i] += size[j];
      par[j] = i;
      --ncomps;
   }
    
   int snapshot() {
      return top;
   }
    
   void toSnapshot(int snap) {
      while (top != snap) {
         --top;
         if (changes[top].type == PAR) {
            par[changes[top].index] = changes[top].oldValue;
         }
         if (changes[top].type == SIZE) {
            size[changes[top].index] = changes[top].oldValue;
         }
         if (changes[top].type == NCOMPS) {
            ncomps = changes[top].oldValue;
         }
      }
   }
};