int get(int x, int y){
	if (x <= 0 || y <= 0)
		return 0;
	int val = mul(Q.get(x, y), mul(x + 1, y + 1)) + Fij.get(x, y) - mul(Fi.get(x, y), y + 1) - mul(Fj.get(x, y), x + 1);
	return (val%MO + MO) % MO;
}
void update(int x, int y,int val){
	if (x > n || y > m)
		return;
//	cout << x << " " << y<<" "<<val << endl;
	Q.update(x, y, val);
	Fi.update(x, y, mul(val,x));
	Fj.update(x, y, mul(val,y));
	Fij.update(x, y, mul(val, mul(x, y)));
}
void add_val(int sx, int sy, int fx, int fy, int val){//val==1
	update(sx, sy, val);
	update(sx, fy+1, (MO-val)%MO);
	update(fx+1, sy , (MO-val)%MO);
	update(fx + 1, fy+1, val);
}
int get_sum(int sx, int sy, int fx, int fy){
	//cout << sx<<" "<<sy<<" "<<fx<<" "<<fy<<" "<<Q.get(fx, fy) << endl;
	int val = get(fx, fy) - get(sx - 1, fy) - get(fx, sy - 1) + get(sx - 1, sy - 1);
	val = (val%MO + MO) % MO;
	return val;
}