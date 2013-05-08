//三分法求函数波峰
const int MMAX = 11000;
const double EPS =  1e-4;
int x[MMAX], y[MMAX];
int n, m;
#define f(dt) k*(dt-x[p-1]) + y[p-1] +  1.0*n/dt/dt;
double triple_search(int p)
{
    double mmin  = 1e99;
    double k = 1.0 * (y[p]-y[p-1]) / (x[p]-x[p-1]);
    double xl = x[p-1], xr = x[p];
    double lm, rm, flm, frm;
    while (fabs(xr-xl)  > EPS)
    {
        lm = (2.0*xl + xr) / 3.0;
        rm =  (2.0*xr + xl) / 3.0;
        flm = f(lm);
        frm  = f(rm);
        if (frm > flm)xr = rm, mmin  = min(mmin, flm);
        elsexl = lm, mmin  = min(mmin,  frm);
    }
    return mmin;
}
double solve()
{
    int i, j, k;
    double mmin  =  1e99;
    for (i=1; i<m; i++)
    {
        double ret = triple_search(i);
        mmin  = min(mmin,  ret);
    }
    return mmin;
}
int main()
{
    int i, j;
    while (scanf("%d  %d",  &m,  &n) ==  2)
    {
        for (i=0; i<m; i++)scanf("%d %d", &x[i], &y[i]);
        printf("%.3lf\n", solve());
    }
}
