//二分图最小点权覆盖
// 3308 PKU  Paratroopers
// 2874 ZJU
double R[MAX], C[MAX];
// 二分图最小点权覆盖-> 网络最大流
void make_net()
{
    int i, j;
    memset(net,  0, sizeof(net));
    // C(S,x) = W[x]
    for (i=0; i<n; i++)net[0][i+1]  = log(R[i]);
    // C(y,T) = W[y]
    for (i=0; i<m; i++)net[n+i+1][n+m+1]  = log(C[i]);
    // C(x,y) = inf
    for (i=0; i<l; i++)
    {
        int x, y;
        scanf("%d %d",  &x, &y);
        net[x][y+n]  =  1e99;
    }
    n = n + m +  1;
}
double solve()
{
    int i, j;
    double ret;
    make_net();
    ret = Edmonds_Karp();
    return  exp(ret);
}
