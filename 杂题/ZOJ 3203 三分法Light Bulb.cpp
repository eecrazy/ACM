#include <cstdio>
double H,h,D;
//x是人到墙的距离
double Calc(double x)
{
    return (h * D - H * x) / (D - x) + x;
      //  return H-D*(H-h)/x+D-x;
}
double Solve()
{
    double Left, Right;
    double mid, midmid;
    double mid_value, midmid_value;
    Left = 0; Right = D*h/H;
    int size=30;
    while (size--)
    {
        mid = (Left + Right) / 2;
        midmid = (mid + Right) / 2;
        mid_value = Calc(mid);
        midmid_value = Calc(midmid);
        // 假设求解最大极值.
        if (mid_value >= midmid_value)
         Right = midmid;
        else Left = mid;
    }
    return Calc(Left);

}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lf%lf%lf", &H, &h, &D);
        printf("%.3lf\n",Solve());
    }
}
