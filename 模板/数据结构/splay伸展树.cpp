struct SplayTree
{
	int nodeCnt,root,type[maxNodeCnt],parent[maxNodeCnt],childs[maxNodeCnt][2],
	size[maxNodeCnt],stack[maxNodeCnt],reversed[maxNodeCnt];
	void clear()
	{
		root=0;
		size[0]=0;
		nodeCnt=1;
	}
	int malloc()
	{
		type[nodeCnt]=2;
		childs[nodeCnt][0]=childs[nodeCnt][1]=0;
		size[nodeCnt]=1;
		reversed[nodeCnt]=0;
		return nodeCnt++;
	}
	void update()
	{
		size[x]=size[childs[x][0]]+1+size[childs[x][1]];
	}

	void pass(int x)
	{
		if(reversed[x])
		{
			swap(childs[x][0],childs[x][1]);
			type[childs[x][0]]=0;
			reversed[childs[x][0]]^=1;
			type[childs[x][1]]=1;
			reversed[childs[x][1]]^=1;
			reversed[x]=0;

		}
	}
	void rotate(int x)
	{
		int t=type[x],y=parent[x],z=childs[x][1-t];
		type[x]=type[y];
		parent[x]=parent[y];
		if(type[x]!=2)
		{
			childs[parent[x]][type[x]]=x;
		}
		type[y]=1-t;
		parent[y]=x;
		childs[x][1-t]=y;
		if(z)
		{
			type[z]=t;
			parent[z]=y;
		}
		childs[y][t]=z;
		update(y);
	}
	void splay(int x)
	{
		int stackCnt=0;
		stack[stackCnt++]=x;
		for(int i=x;type[i]!=2;i=parent[i])
		{
			stack[stackCnt++]=parent[i];
		}
		for(int i=stackCnt-1;i>-1;--i)
		{
			pass(stack[i]);
		}

		while(type[x]!=2)
		{
			int y=parent[x];
			if(type[x]==type[y])
			{
				rotate(y);
			}
			else
			{
				rotate(x);
			}
			if(type[x]==2)
			{
				break;
			}
			rotate(x);
		}
		update(x);
	}
	int find(int x,int rank)
	{
		while(true)
		{
			pass(x);
			if(size[childs[x][0]]+1==rank)
			{
				break;
			}
			if(rank<=size[childs[x][0]])
			{
				x=childs[x][0];
			}
			else
			{
				rank-=size[childs[x][0]]+1;

				x=childs[x][1];
			}
		}
		return x;
	}
	void split(int &x,int &y,int a)
	{
		y=find(x,a+1);
		splay(y);
		x=childs[y][0];
		type[x]=2;
		childs[y][0]=0;
		update(y);
	}
	void split3(int &x,int &y,int &z,int a,int b)
	{
		split(x,z,b);
		split(x,y,z-1);
	}
	void join(int &x,int y)
	{
		x=find(x,size[x]);
		splay(x);
		childs[x][1]=y;
		type[y]=1;
		parent[y]=x;
		update(x);
	}
	void join3(int &x,int y,int z)
	{
		join(y,z);
		join(x,y);
	}
	int getRank(int x)
	{
		splay(x);
		root=x;
		return size[childs[x][0]];
	}
	void reverse(int a,int b)
	{
		int x, y;
		split3(root,x,y,a+1,b+1);
		reversed[x]^=1;
		join3(root,x,y);
	}
};