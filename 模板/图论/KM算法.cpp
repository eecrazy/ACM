// 求最大权二分匹配的KM算法
// 最大权二分匹配问题就是给二分图的每条边一个权值，选择若干不相交的边，
// 得到的总权值最大。解决这个问题可以用KM算法。理解KM算法需要首先理解
// “可行顶标”的概念。可行顶标是指关于二分图两边的每个点的一个值lx[i]或ly[j]，
// 保证对于每条边w[i][j]都有lx[i]+ly[j]-w[i][j]>=0。如果所有
// 满足lx[i]+ly[j]==w[i][j]的边组成的导出子图中存在一个完美匹配，
// 那么这个完美匹配肯定就是原图中的最大权匹配。理由很简单：这个匹配的
// 权值之和恰等于所有顶标的和，由于上面的那个不等式，另外的任何匹配方案
// 的权值和都不会大于所有顶标的和。

// 但问题是，对于当前的顶标的导出子图并不一定存在完美匹配。这时，可以用
// 某种方法对顶标进行调整。调整的方法是：根据最后一次不成功的寻找交错路
// 的DFS，取所有i被访问到而j没被访问到的边(i,j)的lx[i]+ly[j]-w[i][j]的
// 最小值d。将交错树中的所有左端点的顶标减小d，右端点的顶标增加d。经过
// 这样的调整以后：原本在导出子图里面的边，两边的顶标都变了，不等式的
// 等号仍然成立，仍然在导出子图里面；原本不在导出子图里面的边，它的
// 左端点的顶标减小了，右端点的顶标没有变，而且由于d的定义，不等式
// 仍然成立，所以他就可能进入了导出子图里。

// 初始时随便指定一个可行顶标，比如说lx[i]=max{w[i][j]|j是右边的点}，
// ly[i]=0。然后对每个顶点进行类似Hungary算法的find过程，如果某次find
// 没有成功，则按照这次find访问到的点对可行顶标进行上述调整。这样就可以
// 逐步找到完美匹配了。

// 值得注意的一点是，按照上述d的定义去求d的话需要O(N^2)的时间，因为d需要
// 被求O(N^2)次，这就成了算法的瓶颈。可以这样优化：设slack[j]表示右边的
// 点j的所有不在导出子图的边对应的lx[i]+ly[j]-w[i][j]的最小值，在find过程
// 中，若某条边不在导出子图中就用它对相应的slack值进行更新。然后求d只要
// 用O(N)的时间找到slack中的最小值就可以了。

// 如果是求最小权匹配，只需要把那个不等式反一下就行了。算法需要作出的
// 改变是：lx的初值为所有临界边中的最小值，find中t反号。

// URAL1076.cpp
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=160,OO=2147483647;
int w[maxn][maxn];
int lx[maxn],ly[maxn];
int linky[maxn];
int visx[maxn],visy[maxn];
int N;
int slack[maxn];

void input(){
	scanf("%d",&N);
	for(int i=0;i<N;++i)
		for(int j=0;j<N;++j)
			scanf("%d",&w[i][j]);
}
bool find(int x){
	visx[x]=true;
	for(int y=0;y<N;++y){
		if(visy[y])continue;
		int t=lx[x]+ly[y]-w[x][y];
		if(t==0){
			visy[y]=true;
			if(linky[y]==-1||find(linky[y])){
				linky[y]=x;
				return true;
			}
		}
		else{
			if(slack[y]>t)
				slack[y]=t;
		}
	}
	return false;
}
void KM(){
	memset(linky,-1,sizeof(linky));
	memset(lx,0,sizeof(lx));
	memset(ly,0,sizeof(ly));
	for(int i=0;i<N;++i)
		for(int j=0;j<N;++j)
			if(w[i][j]>lx[i])
				lx[i]=w[i][j];
	for(int x=0;x<N;++x){
		for(int i=0;i<N;++i)
			slack[i]=OO;
		for(;;){
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			if(find(x))break;
			int d=OO;
			for(int i=0;i<N;++i){
				if(!visy[i])
					if(d>slack[i])
						d=slack[i];
			}
			for(int i=0;i<N;++i){
				if(visx[i])
					lx[i]-=d;
			}
			for(int i=0;i<N;++i){
				if(visy[i])
					ly[i]+=d;
				else
					slack[i]-=d;
			}
		}
	}
}
void output(){
	int res=0;
	for(int j=0;j<N;++j){
		for(int i=0;i<N;++i)
			res+=w[i][j];
		res-=w[linky[j]][j];
	}
	printf("%d\n",res);
}
int main(){
	input();
	KM();
	output();
}