#include <cstdio>

char a[1000];
int  ca=1;
int main()
{
	while(gets(a)!=NULL)
	{
		if(a[0]=='A'&&a[1]==' ')
		{
			printf("Case %d: UNIQUE\n",ca++);
		}
		else if(a[0]=='A'&&a[1]=='#')
		{
			a[0]='B';
			a[1]='b';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='B'&&a[1]=='b')
		{
			a[0]='A';
			a[1]='#';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='B'&&a[1]==' ')
		{
			printf("Case %d: UNIQUE\n",ca++);
		}
		else if(a[0]=='C'&&a[1]==' ')
		{
			printf("Case %d: UNIQUE\n",ca++);
		}
		else if(a[0]=='C'&&a[1]=='#')
		{
			a[0]='D';
			a[1]='b';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='D'&&a[1]=='b')
		{
			a[0]='C';
			a[1]='#';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='D'&&a[1]==' ')
		{
			printf("Case %d: UNIQUE\n",ca++);
		}

		else if(a[0]=='D'&&a[1]=='#')
		{
			a[0]='E';
			a[1]='b';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='E'&&a[1]=='b')
		{
			a[0]='D';
			a[1]='#';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='E'&&a[1]==' ')
		{
			printf("Case %d: UNIQUE\n",ca++);
		}
		else if(a[0]=='F'&&a[1]==' ')
		{
			printf("Case %d: UNIQUE\n",ca++);
		}
		else if(a[0]=='F'&&a[1]=='#')
		{
			a[0]='G';
			a[1]='b';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='G'&&a[1]=='b')
		{
			a[0]='F';
			a[1]='#';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='G'&&a[1]==' ')
		{
			printf("Case %d: UNIQUE\n",ca++);
		}
		else if(a[0]=='G'&&a[1]=='#')
		{
			a[0]='A';
			a[1]='b';
			printf("Case %d: %s\n",ca++,a);
		}
		else if(a[0]=='A'&&a[1]=='b')
		{
			a[0]='G';
			a[1]='#';
			printf("Case %d: %s\n",ca++,a);
		}
		else
			break;
	}
}%