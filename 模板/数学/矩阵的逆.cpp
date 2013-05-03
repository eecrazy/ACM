/*goal:给一个矩阵，求它的逆
method：将原矩阵A和单位矩阵E做成一个大矩(A,E),用初等行变换，将大矩阵中的A变为E，则会得到(E，A-1的形式)；
A:原矩阵   C：逆矩阵    N:矩阵的阶数*   O(n^3)*/

inline vector<double> operator* (vector<double> a,double b)
{
	int N=a.size();
	vector<double> res(N,0);
	for(int i=0;i<N;i++)
	{
		res[i]=a[i]*b;
	}
	return res;
}

inline vector<double> operator- (vector<double> a,vector<double> b)
{
	int N=a.size();
	vector<double> res(N,0);
	for(int i=0;i<N;i++)
	{
		res[i]=a[i]-b[i];
	}
	return res;
}

inline void inversr(vector<double> A[],vector<double> C[],int N)
{
	for(int i=0;i<N;++i)
		C[i]=vector<double>(N,0);
	for(int i=0;i<N;++i)
		C[i][i]=1;
	for(int i=0;i<N;++i)
	{
		for(int j=i;j<N;++j)
		{
			if(fabs(a[j][i])>0)
			{
				swap(A[i],A[j]);
				swap(C[i],C[j]);
				break;
			}
		}
		C[i]=C[i]*(1/A[i][i]);
		A[i]=A[i]*(1/A[i][i]);
		for(int j=0;j<n;j++)
		{
			if(j!=i&&fabs(A[j][i])>0)
			{
				C[j]=C[j]-C[i]*A[j][i];
				A[j]=A[j]-A[i]*A[j][i];
			}
		}
	}
}