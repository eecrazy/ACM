// 满足单调性用二分，满足凸性用三分法。
// 此题明显是满足凸性的，用三分法很简单解决了。
// 在圆上分成两个半圆，0-Pi,Pi-2Pi,做两次三分法就解决了。

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const double eps = 1e-6;
const double PI = acos(-1.0);
struct Point
{
    double x, y;
    Point(double xx = 0, double yy = 0): x(xx), y(yy) {}
    Point operator -(const Point p1)
    {
        return Point(x - p1.x, y - p1.y);
    }
    double operator ^(const Point p1)
    {
        return x * p1.x + y * p1.y;
    }
};
inline int sign(double d)
{
    if (d > eps)return 1;
    else if (d < -eps)return -1;
    else return 0;
}
double dis(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

double ptoline(Point tp, Point st, Point ed) //求点到线段的距离
{
    double t1 = dis(tp, st);
    double t2 = dis(tp, ed);
    double ans = min(t1, t2);
    if (sign((ed - st) ^ (tp - st)) >= 0 && sign((st - ed) ^ (tp - ed)) >= 0) //锐角
    {
        double h = fabs(cross(st - tp, ed - tp)) / dis(st, ed);
        ans = min(ans, h);
    }
    return ans;
}
double xx1, yy1, xx2, yy2;

double ptoRec(Point tp)
{
    Point p1(xx1, yy1);
    Point p2(xx1, yy2);
    Point p3(xx2, yy1);
    Point p4(xx2, yy2);
    double ans = ptoline(tp, p1, p2);
    ans = min(ans, ptoline(tp, p2, p4));
    ans = min(ans, ptoline(tp, p4, p3));
    ans = min(ans, ptoline(tp, p3, p1));
    return ans;
}
double x, y, R;
double xx0, yy0;
Point get_point(double A)
{
    return Point(x + R * cos(A), y + R * sin(A));
}
double solve()
{
    double l, r, mid, midmid;
    Point p0(xx0, yy0);
    Point p;
    l = 0; r = PI;
    while (r - l >= 1e-8)
    {
        mid = (r + l) / 2;
        midmid = (mid + r) / 2;
        Point p1 = get_point(mid);
        Point p2 = get_point(midmid);
        double t1 = ptoRec(p1) + dis(p1, p0);
        double t2 = ptoRec(p2) + dis(p2, p0);
        if (t1 > t2)l = mid;
        else r = midmid;
    }
    p = get_point(l);
    double ans1 = dis(p, p0) + ptoRec(p);
    l = PI; r = 2 * PI;
    while (r - l >= 1e-8)
    {
        mid = (r + l) / 2;
        midmid = (mid + r) / 2;
        Point p1 = get_point(mid);
        Point p2 = get_point(midmid);
        double t1 = ptoRec(p1) + dis(p1, p0);
        double t2 = ptoRec(p2) + dis(p2, p0);
        if (t1 > t2)l = mid;
        else r = midmid;
    }
    p = get_point(l);
    double ans2 = dis(p, p0) + ptoRec(p);
    return min(ans1, ans2);
}

int main()
{
    while (scanf("%lf%lf", &xx0, &yy0) == 2)
    {
        if (xx0 == 0 && yy0 == 0)break;
        scanf("%lf%lf%lf", &x, &y, &R);
        scanf("%lf%lf%lf%lf", &xx1, &yy1, &xx2, &yy2);
        printf("%.2lf\n", solve());
    }
    return 0;
}