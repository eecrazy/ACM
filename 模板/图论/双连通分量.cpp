const int maxn=1010;
vector<int> edge[maxn];
vector<vector<int>>connect;
int dfn[maxn],low[manx],in_seq[maxn];
int stack[maxn],list[maxn];
int cnt,top,pop,len;
void biconnect(int v)
{
	stack[++top]=v;
	dfn[v]=low[v]=pop++;
	int i,succ;
	for(i=edge[v].size()-1;i>=0;i--)
	{
		succ=edge[v][i];
		if(dfn[succ]=-1)
		{
			biconnect(succ);
			if(low[succ]>=dfn[succ])
			{
				cnt++;
				len=0;
				do
				{
					in_seq[stack[top]]=cnt;
					list[len++]=stack[top];
					top--;
				}while(stack[top+1]!=succ);
				in_seq[v]=cnt;
				list[len++]=v;
				vector<int> tmp(list,list+len);
				connect.push_back(tmp);
			}
			low[v]=min(low[v],low[succ]);
		}
		else
		{
			low[v]=min(low[v],dfn[succ]);
		}
	}
} 