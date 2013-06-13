#define M 100001
struct Seg_Tree{
	int left,right;
	int mid() {
		return (left + right) >> 1;
	}
}tt[M*4];
int len;
int sorted[M];
int toLeft[20][M];
int val[20][M];
 
void build(int l,int r,int d,int idx) {
	tt[idx].left = l;
	tt[idx].right = r;
	if(tt[idx].left == tt[idx].right)	return ;
	int mid = tt[idx].mid();
	int lsame = mid - l + 1;//lsame表示和val_mid相等且分到左边的
	for(int i = l ; i <= r ; i ++) {
		if(val[d][i] < sorted[mid]) {
			lsame --;//先假设左边的数(mid - l + 1)个都等于val_mid,然后把实际上小于val_mid的减去
		}
	}
	int lpos = l;
	int rpos = mid+1;
	int same = 0;
	for(int i = l ; i <= r ; i ++) {
		if(i == l) {
			toLeft[d][i] = 0;//toLeft[i]表示[ tt[idx].left , i ]区域里有多少个数分到左边
		} else {
			toLeft[d][i] = toLeft[d][i-1];
		}
		if(val[d][i] < sorted[mid]) {
			toLeft[d][i] ++;
			val[d+1][lpos++] = val[d][i];
		} else if(val[d][i] > sorted[mid]) {
			val[d+1][rpos++] = val[d][i];
		} else {
			if(same < lsame) {//有lsame的数是分到左边的
				same ++;
				toLeft[d][i] ++;
				val[d+1][lpos++] = val[d][i];
			} else {
				val[d+1][rpos++] = val[d][i];
			}
		}
	}
	build(l,mid,d+1,LL(idx));
	build(mid+1,r,d+1,RR(idx));
}
 
int query(int l,int r,int k,int d,int idx) {
	if(l == r) {
		return val[d][l];
	}
	int s;//s表示[ l , r ]有多少个分到左边
	int ss;//ss表示 [tt[idx].left , l-1 ]有多少个分到左边
	if(l == tt[idx].left) {
		s = toLeft[d][r];
		ss = 0;
	} else {
		s = toLeft[d][r] - toLeft[d][l-1];
		ss = toLeft[d][l-1];
	}
	if(s >= k) {//有多于k个分到左边,显然去左儿子区间找第k个
		int newl = tt[idx].left + ss;
		int newr = tt[idx].left + ss + s - 1;//计算出新的映射区间
		return query(newl,newr,k,d+1,LL(idx));
	} else {
		int mid = tt[idx].mid();
		int bb = l - tt[idx].left - ss;//bb表示 [tt[idx].left , l-1 ]有多少个分到右边
		int b = r - l + 1 - s;//b表示 [l , r]有多少个分到右边
		int newl = mid + bb + 1;
		int newr = mid + bb + b;
		return query(newl,newr,k-s,d+1,RR(idx));
	}
}
int main() {
	int T;
	scanf("%d",&T);
	while(T --) {
		int n , m;
		scanf("%d%d",&n,&m);
		FOR(i,1,n+1) {
			scanf("%d",&val[0][i]);
			sorted[i] = val[0][i];
		}
		sort(sorted + 1 , sorted + n + 1);
		build(1,n,0,1);
		while(m --) {
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",query(l,r,k,0,1));
		}
	}
	return 0;
}
