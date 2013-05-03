// 给定一个环形字符串s,求字符串t，使得t是所有与s长度相同的字串里字典序最小的字符串；
string smallestRepresation(string s)
{
	int i,j,k,l;
	int N=s.length();
	s+=s;
	for(i=0,j=1;j<N;)
	{
		for(k=0;k<N&&s[i+k]==s[j+k];k++);
		if(k>=N)
			break;
		if(s[i+k]<s[j+k])
			j+=k+1;
		else
		{
			l=i+k;
			i=j;
			j=max(l,j)+1;
		}
	}
	return s.substr(i,N);
}