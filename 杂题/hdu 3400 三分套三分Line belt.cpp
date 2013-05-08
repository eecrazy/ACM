// 典型的三分法,先三分第一条线段,找到一个点,然后根据这个点再三分
// 第二条线段即可,想出三分的思路基本就可以过了
// http://acm.hdu.edu.cn/showproblem.php?pid=3400
#include <stdio.h>
#include <math.h>
#define eps 1e-9

struct point
{
    double x;
    double y;
};
point A, B, C, D, M1, M2;
double P, Q, R;
double dis(point a, point b)//计算2点之间距离
{
    return sqrt(eps + (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double cal2(double len)
{
    double d1, d2, k, t1, t2;
    d1 = len, d2 = dis(C, D);
    k = d1 / d2;
    M2.x = (C.x - D.x) * k + D.x;
    M2.y = (C.y - D.y) * k + D.y;
    t1 = dis(M1, M2) / R;
    t2 = len / Q;
    return (t1 + t2);
}
double cal1(double len)
{
    int i;
    double d1, d2, k, t1, tx, ty;
    d1 = len, d2 = dis(A, B);
    k = d1 / d2;
    M1.x = (B.x - A.x) * k + A.x;
    M1.y = (B.y - A.y) * k + A.y;
    t1 = len / P;
    double left, right, mid1, mid2;
    left = 0, right = dis(C, D);
    for (i = 1; i <= 100; i++)
    {
        mid1 = (2 * left + right) / 3;
        mid2 = (left + 2 * right) / 3;
        tx = cal2(mid1);
        ty = cal2(mid2);
        if (tx > ty)
        {
            left = mid1;
        }
        else
        {
            right = mid2;
        }
    }
    return t1 + cal2(left);
}

void triple()
{
    int i;
    double mid1, mid2, left, right, t1, t2;
    left = 0, right = dis(A, B);
    for (i = 1; i <= 100; i++)
    {
        mid1 = (left * 2 + right) / 3;
        mid2 = (left + 2 * right) / 3;
        t1 = cal1(mid1);
        t2 = cal1(mid2);
        if (t1 > t2)
        {
            left = mid1;
        }
        else
        {
            right = mid2;
        }
    }
    printf("%.2lf\n", cal1(left));
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y);
        scanf("%lf%lf%lf%lf", &C.x, &C.y, &D.x, &D.y);
        scanf("%lf%Lf%lf", &P, &Q, &R);
        triple();
    }
    return 0;
}
