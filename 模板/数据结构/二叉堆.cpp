const int MAXSIZE=100000;
struct BinaryHeap
{
	int heap[MAXSIZE],id[MAXSIZE],pos[MAXSIZE],n,counter;
	BinaryHeap () :n(0),counter(0){}
	BinaryHeap (int array[],int offset):n(0),counter(0)
	{
		for(int i=0;i<offset;++i)
		{
			heap[++n]=array[i];
			id[n]=pos[n]=n;
		}
		for(int i=n/2;i>=1;--i)
		{
			down(i);
		}
	}
	void push(int v)
	{
		heap[++n]=v;
		id[n]=++counter;
		pos[id[n]]=n;
		up(n);
	}
	int top()
	{
		return heap[1];
	}
	int pop()
	{
		swap(heap[1],heap[n]);
		swap(id[1],id[n--]);
		pos[id[1]]=1;
		down(1);
		return id[n+1];
	}
	int get(int i)
	{
		return heap[pos[i]];
	}
	void change(int i,int value)
	{
		heap[pos[i]]=value;
		down(pos[i]);
		up(pos[i]);

	}

	void erase(int i)
	{
		heap[pos[i]]=INT_MIN;
		up(pos[i]);
		pop();
	}
	void up(int i)
	{
		int x=heap[i],y=id[i];
		for(int j=i/2;j>=1;j/=2)
		{
			if(heap[j]>x)
			{
				heap[i]=heap[j];
				id[i]=id[j];
				pos[id[i]]=i;
				i=j;
			}
			else
			{
				break;
			}
		}
		heap[i]=x;
		id[i]=y;
		pos[y]=i;
	}
	void down(int i)
	{
		int x=heap[i],y=id[i];
		for(int j=i*2;j<=n;j*=2)
		{
			j+=j<n&&heap[j]>heap[j+1];
			if(heap[j]<x)
			{
				heap[i]=heap[j];
				id[i]=id[j];
				pos[id[i]]=i;
				i=j;
			}
			else
			{
				break;
			}
		}
		heap[i]=x;
		id[i]=y;
		pos[y]=i;
	}
	bool empty()
	{
		return n==0;
	}
	int size()
	{
		return n;
	}
};