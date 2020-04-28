namespace simplex{
	const LD eps=1e-10;
	const int N=3000+10,M=3000+10;
	int n,m;
	int Left[M],Down[N],idx[N],va[N];
	LD a[M][N],b[M],c[N],v;
	//maximize cTx, subject to Ax <= b and x >= 0
	void init(int p,int q) {
		n=p; m=q;
		for1(i,m) for1(j,n) a[i][j]=0;
		for1(j,m) b[j]=0; for1(i,n) c[i]=0;
		for1(i,n) idx[i]=0;
		v=0;
	}
	void pivot(int x,int y) {
		swap(Left[x],Down[y]);
		LD k=a[x][y];
		a[x][y]=1; b[x]/=k;
		int t=0;
		for1(j,n) {
			a[x][j]/=k;
			if (abs(a[x][j])>eps) va[++t]=j;
		}
		for1(i,m) if(i!=x&&abs(a[i][y])>eps) {
			k=a[i][y];
			a[i][y]=0;
			b[i]-=k*b[x];
			for1(j,t) a[i][va[j]]-=k*a[x][va[j]];
		}
		k=c[y];
		c[y]=0;
		v+=k*b[x];
		for1(j,t) c[va[j]]-=k*a[x][va[j]];
	}
 
	LD x[ N ];
	LD ans;
	int solve() {
		for1(i,n) Down[i]=i;
		for1(i,m) Left[i]=n+i;
		while(1) {
			int x=0;
			for1(i,m) if (b[i]<-eps&&(x==0||b[i]<b[x])) x=i;
			if(x==0) break;
			int y=0;
			for1(j,n) if (a[x][j]<-eps) if (y==0||a[x][j]<a[x][y]) y=j;
			if(y==0) {  return -1; } //Infeasible
			pivot(x,y);
		}
		while(1) {
			int y=0;
			for1(i,n) if (c[i]>eps&&(y==0||c[i]>c[y])) y=i;
			if(y==0) break;
			int x=0;
			for1(j,m) if (a[j][y]>eps) if (x==0||b[j]/a[j][y]<b[x]/a[x][y]) x=j;
			if(x==0) {  return -2; } // Unbounded
			pivot(x,y);
		}
		ans = v;
		for1(i,m) if(Left[i]<=n) idx[Left[i]]=i;
		for1(i,n) x[i] = b[idx[i]];
		return 1;
	}
}