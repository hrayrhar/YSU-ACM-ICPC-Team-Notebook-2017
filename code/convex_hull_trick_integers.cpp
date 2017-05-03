struct convex_hull {
    int top, pointer;

    struct uxix{
        long long k,b;
    } mas[N];

    void init() {
        top = 0;
        pointer = 0;
    }

    void add(long long k,long long b){
        k = -k; b = -b;
        uxix cur;
        cur.k=k;
        cur.b=b;
        while(top>=2){
            uxix u, v;
            u = mas[top-1];
            v = mas[top-2];
            assert(k >= u.k);
            assert(u.k >= v.k);
            if ((LD)(v.b - u.b) / (u.k - v.k) >  (LD)(u.b - b) / (k - u.k)) 
                --top;
            else
                break;
        }
        mas[top++] = cur;
    }
    /*
    // O(logN) general case
    long long get(long long x){
        if (top == 0) return INF;
        int ina=0,inb=top-1,answ;
        while(ina<=inb){
            int mid=(ina+inb)/2;
            long long p, q;
            if(mid==0) {
                p = -INF;
                q = 1;
            }
            else {
                p = mas[mid-1].b - mas[mid].b;
                q = mas[mid].k - mas[mid-1].k;
            }
            if((LD)p / q <= x){
                answ=mid;
                ina=mid+1;
            }
            else
                inb=mid-1;
        }
        long long pat=mas[answ].k * x + mas[answ].b;
        return -pat;
    }*/
    
    // Amortized O(1), if queries are sorted
    long long get(long long x){
        if (top == 0) return INF;
        pointer = min(pointer , top-1);
        while(pointer < top-1){
            long long p,q;
            q = mas[pointer+1].k - mas[pointer].k;
            p = mas[pointer].b - mas[pointer+1].b;
            if((LD)p / q <= x)
                ++pointer;
            else
                break;
        }
        long long pat=mas[pointer].k * x + mas[pointer].b;
        return -pat;
    }

} hull;
