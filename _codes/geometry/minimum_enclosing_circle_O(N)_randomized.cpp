// One can do 2 nested ternary searches: O(N * (logN)^2)
struct MEC {
 
    bool inside_circle(pt A, pt C, LD R) {
        return A.dist2(C) < R + eps;
    }
 
    LD cross(pt u, pt v) {
        return u.x * v.y - u.y * v.x;
    }
 
    pt intersect_bisectors(pt A, pt B, pt C, pt D) {
        pt AB = (A+B) / 2.0;
        pt CD = (C+D) / 2.0;
 
        pt n1 = A - B;
        pt n2 = C - D;
 
        LD a1 = n1.x;
        LD b1 = n1.y;
        LD c1 = -a1 * AB.x - b1 * AB.y;
 
        LD a2 = n2.x;
        LD b2 = n2.y;
        LD c2 = -a2 * CD.x - b2 * CD.y;
 
        LD det = a1 * b2 - a2 * b1;
        assert(fabsl(det) > eps);
 
        LD detx = c2 * b1 - c1 * b2;
        LD dety = c1 * a2 - c2 * a1;
         
        return pt(detx/det, dety/det);
    }
 
    void update_ans(pt O, vector<pt>& p, pt A, pt B, pt& C, LD& R) {
        LD cur = O.dist2(A);
        if (cur > R) return;
        for (auto E : p) {
            if (!inside_circle(E, O, cur)) return;
        }
        R = cur;
        C = O;
    }
 
    void consider(vector<pt> &p, vector<pt>& side, pt A, pt B, pt& C, LD& R) {
        pt mini(INF,INF,INF);
        pt maxi(-INF, -INF, -INF);
 
        for (auto E : side) {
            pt X = intersect_bisectors(A, E, A, B);
            if (X < mini) mini = X;
            if (maxi < X) maxi = X;
        }
 
        if (mini.x < INF/2) {
            update_ans(mini, p, A, B, C, R);
            update_ans(maxi, p, A, B, C, R);
        }
    }
 
    void two_points_known(vector<pt>& p, pt A, pt B, pt& C, LD& R) {
        pt dir = B-A;
         
        R=INF;
        update_ans((A+B)/2.0, p, A, B, C, R);
         
        vector<pt> lside, rside;
        for (auto E : p) {
            if (cross(dir, E-A) > +eps) lside.pb(E);
            if (cross(dir, E-A) < -eps) rside.pb(E);
        }
        consider(p, lside, A, B, C, R);
        consider(p, rside, A, B, C, R);
    }
 
    void one_point_known(vector<pt>& p, pt A, pt& C, LD& R) {
        random_shuffle(all(p));
 
        C = (p[0] + A) / 2.0;
        R = p[0].dist2(A) / 2.0;
 
        for (int i = 1; i < sz(p); ++i) {
            if (inside_circle(p[i], C, R)) continue;
            vector<pt> mas(p.begin(), p.begin()+i);
            two_points_known(mas, A, p[i], C, R);
        }
    }
 
    LD get(vector<pt> &p) {
        random_shuffle(all(p));
        pt C = p[0];
        LD R = 0.0;
 
        for (int i = 1; i < sz(p); ++i) {
            if (inside_circle(p[i], C, R)) continue;
            vector<pt> mas(p.begin(), p.begin()+i);
            one_point_known(mas, p[i], C, R);
        }
 
        return R;
    }
 
} mec;