const int K = 30;
typedef long long LL;
inline LL F(LL x)
{
	if(x&(1ll<<(K+1)))
		return x^(1ll<<(K+1));
	return x;
}
struct all_palind
{
	static const int N = 3*100000+5;
	LL pl[ N ];
	LL gpl[ N ];
	int n;
	char s[ N ];
	struct triple
	{
		int i, d, k;
		triple(int _i = 0,int _d = 0,int _k = 0):i(_i), d(_d), k(_k){}
	};
	vector< triple > g;
	void init(int _n)
	{
		n = _n;
	}
	void phase(int j)
	{
		vector< triple > g1;
		for(int u = 0; u < (int)g.size(); ++ u)
		{
			int i = g[u].i;
			if(i > 1 && s[i-1]==s[j])
				g1.push_back( triple(g[u].i-1, g[u].d, g[u].k) );
		}
		vector< triple > g2;
		int r = -j;
		for(int u = 0; u < (int)g1.size(); ++ u)
		{
			int i = g1[u].i;
			if(i-r!=g1[u].d)
			{
				g2.push_back( triple(i, i-r, 1) );
				if(g1[u].k > 1)
					g2.push_back( triple(i+g1[u].d, g1[u].d, g1[u].k-1) );
			}
			else
				g2.push_back( g1[u] );
			r = i+(g1[u].k-1)*g1[u].d;
		}
		if(j > 1 && s[j-1]==s[j])
		{
			g2.push_back( triple(j-1, j-1-r, 1) );
			r = j-1;
		}
		g2.push_back( triple(j, j-r, 1) );
 
		g.clear();
		triple tr = g2[0];
		for(int u = 1; u < (int)g2.size(); ++ u)
		{
			if(tr.d==g2[u].d)
				tr.k+=g2[u].k;
			else
			{
				g.push_back( tr );
				tr = g2[u];
			}
		}
		g.push_back( tr );
 
		for(int u = 0; u < (int)g.size(); ++ u)
		{
			int i = g[u].i, d = g[u].d;
			int r = i+(g[u].k-1)*d;
			LL m = pl[ r - 1 ];
			if(g[u].k > 1)
				m = m|gpl[ i-d ];
			if(d <= i)
				gpl[ i-d ] = m;
			pl[j]|=m;
		}
		pl[j] = F(pl[j]<<1);
		if(g[0].i==1)
			pl[j]|=1;
	}
};