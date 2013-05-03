const double eps=1e-8;
int cmp(double x)
{
	if(fab(x)<eps)
	{
		return 0;
	}
	if(x>0)return 1;
	return -1;
}