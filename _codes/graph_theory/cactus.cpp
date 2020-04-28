int topc, tmr, tin[ N ], fup[ N ], p[ N ];
vi gr[ N ], cycles[ N ], graph[ N ];
vpi c[ N ];
void add_cycle(int v,int to){
	int cr = v;
	++ topc;
	while(1){
		c[ cr ].push_back( mp(topc,sz(cycles[topc])) );
		cycles[ topc ].push_back( cr );
		if(cr==to)
			break;
		cr = p[cr];
	}	
}
void dfs(int v,int par){
 
	p[v] = par;
	tin[v] = fup[v] = ++ tmr;
	for(auto to:graph[v]){
		if(to==par)
			continue;
		if(!tin[to]){
			dfs(to,v);
			fup[v] = min(fup[v],fup[to]);
 
			if(fup[to] > tin[v])
				add_cycle(to,v);	
		}else
		if(tin[to] < tin[v]){
			fup[v] = min(fup[v],tin[to]);
			add_cycle(v,to);
		}
	}
}
 
void update(vi & a,vi & b,int d){
	if(sz(b)+d > sz(a))a.resize(sz(b)+d,0);
	forn(i,sz(b))
		a[i+d] = add(a[i+d],b[i]);
}
map< pii, vi > memo;
vi & solvefor(int x,int dad){
	if(memo.count(mp(x,dad)))return memo[ mp(x,dad) ];
	memo[ mp(x,dad) ] = {0,1};
	auto & ans = memo[ mp(x,dad) ];
	for(auto p:c[x]){
		int i = p.first;
		int pos = p.second;
		int c_len = sz(cycles[i]);
		if(i==dad)continue;
		forn(j,c_len){
			int d = (j-pos+c_len)%c_len;
			int y = cycles[i][j];
			if(d==0)continue;
			update(ans,solvefor(y,i),d);
			if(c_len > 2)
				update(ans,solvefor(y,i),c_len-d);
		}
	}
	return ans;
}