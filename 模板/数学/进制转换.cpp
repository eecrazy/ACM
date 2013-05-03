string transform(int x,int y,string s)
{
	string res="";
	int sum=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='-')continue;
		if(s[i]>='0'&&s[i]<='9')
		{
			sum=sum*x+s[i]-'0';
		}
		else
		{
			sum=sum*x+s[i]-'A'+10;
		}
	}
	while(sum)
	{
		char tmp=sum%y;
		sum/=y;
		if(tmp<=9)
		{
			tmp+='0';
		}
		else
		{
			tmp=tmp-10+'A';
		}
		res=tmp+res;
	}
	if(res.length()==0)res='-'+res;
	return res;
}