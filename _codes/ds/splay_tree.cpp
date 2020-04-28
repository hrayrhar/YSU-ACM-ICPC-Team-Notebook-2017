struct _node{
	int in;
	node l, r;
	node p;
};
bool is_root(node v){
	return v->p==NULL || (v->p->l!=v && v->p->r!=v);
}
bool Type(node v){
	return v->p->r == v;
}
void connect(node v,node p,bool ty){
 
	(ty?p->r:p->l) = v;
	if(v)
		v->p = p;
}
void rotate(node n){
	node p = n->p;
	node g = p->p;
	bool t = Type(n);
	connect(t?n->l:n->r,p,t);
	if(!is_root(p))
		connect(n,g,Type(p));
	else
		n->p = g;
	connect(p,n,t^1);
	update(p);
	update(n);
}
stack< node > st;
void splay(node n){
	node u = n;
	while(1){
		st.push( u);
		if(is_root(u))
			break;
		u = u->p;
	}
	while(!st.empty()){
		push(st.top());st.pop();
	}
	while(!is_root(n)){
		node p = n->p;
		if(!is_root(p))
			rotate(  ( Type(n)^Type(p) ) ? n:p );
		rotate(n);
	}
}
node expose(node n){
	node last = NULL;
	for(node m = n;m;m = m->p){
		splay(m);
		m->r = last;
		last = m;
		update(m);
	}
	splay(n);
	return last;
}
 
node Par(node v){
	v = v->l;
	while(v){
		push(v);
		if(v->r)	
			v = v->r;
		else
			break;
	}
	splay(v);
	return v;
}