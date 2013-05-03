#include <cstdio>

int main()
{
	int n;
	while(cin>>n)
	{
		if(n%12==0)
			cout<<"YES"<<endl;
		else
		{
			if(n%4==0)
				cout<<"3"<<endl;
			else
				if(n%6==0)
					cout<<"4"<<endl;
				else
					cout<<"NO"<<endl;
		}
	}
}