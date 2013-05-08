//上交计算几何算法
/****************************************
* COMPUTATIONAL GEOMETRY ROUTINES
* WRITTEN BY : LIU Yu (C) 2003
****************************************/
//    叉乘
//    两个点的距离
//    点到直线距离
//    返回直线 Ax + By + C =0  的系数
//    线段
//    圆
//    两个圆的公共面积
//    矩形
//    根据下标返回多边形的边
//    两个矩形的公共面积
//    多边形  ,逆时针或顺时针给出x,y
//    多边形顶点
//    多边形的边
//    多边形的周长
//    判断点是否在线段上
//    判断两条线断是否相交，端点重合算相交
//    判断两条线断是否平行
//    判断两条直线断是否相交
//    直线相交的交点
//    判断是否简单多边形
//    求多边形面积
//    判断是否在多边形上
//    判断是否在多边形内部
//    点阵的凸包，返回一个多边形
//   最近点对的距离
#include <cmath>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <iostream>
using namespace std;
typedef double TYPE;
#define Abs(x) (((x)>0)?(x):(-(x)))
#define Sgn(x) (((x)<0)?(-1):(1))
#define Max(a,b) (((a)>(b))?(a):(b))
#define Min(a,b) (((a)<(b))?(a):(b))
#define Epsilon 1e-10
#define Infinity 1e+10
#define Pi 3.14159265358979323846
TYPE Deg2Rad(TYPE deg)
{
    return (deg * Pi / 180.0);
}
TYPE Rad2Deg(TYPE rad)
{
    return (rad * 180.0 / Pi);
}
TYPE Sin(TYPE deg)
{
    return sin(Deg2Rad(deg));
}
TYPE Cos(TYPE deg)
{
    return cos(Deg2Rad(deg));
}
TYPE ArcSin(TYPE val)
{
    return Rad2Deg(asin(val));
}
TYPE ArcCos(TYPE val)
{
    return Rad2Deg(acos(val));
}
TYPE Sqrt(TYPE val)
{
    return sqrt(val);
}
struct POINT
{
    TYPE x;
    TYPE y;
    TYPE z;
    POINT() : x(0), y(0), z(0) {};
    POINT(TYPE _x_, TYPE _y_, TYPE _z_ = 0) : x(_x_), y(_y_), z(_z_) {};
};
// cross product of (o->a) and (o->b)// 叉乘
TYPE Cross(const POINT & a, const POINT & b, const POINT & o)
{
    return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
// planar points' distance//  两个点的距离
TYPE Distance(const POINT & a, const POINT & b)
{
    return Sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z
                - b.z));
}
struct LINE
{
    POINT a;
    POINT b;
    LINE() {};
    LINE(POINT _a_, POINT _b_) : a(_a_), b(_b_) {}};
//点到直线距离
double PointToLine(POINT p0 ,POINT p1 ,POINT p2 ,POINT &cp)
{
    double d = Distance(p1 ,p2);
    double s = Cross(p1 ,p2 ,p0) / d;
    cp.x = p0.x + s*( p2.y-p1.y) / d;
    cp.y = p0.y - s*( p2.x-p1.x) / d;
    return Abs(s);
}
// 返回直线 Ax + By + C =0  的系数
void Coefficient(const LINE & L, TYPE & A, TYPE & B, TYPE & C)
{
    A = L.b.y - L.a.y;
    B = L.a.x - L.b.x;
    C = L.b.x * L.a.y - L.a.x * L.b.y;
}
void Coefficient(const POINT & p,const TYPE a,TYPE & A,TYPE & B,TYPE & C)
{
    A = Cos(a);    // 线段
    B = Sin(a);
    C = - (p.y * B + p.x * A);
}
struct SEG
{
    POINT a;
    POINT b;
    SEG() {};
    SEG(POINT  _a_, POINT _b_):a(_a_),b(_b_) {};
};
// 圆
struct CIRCLE
{
    TYPE x;
    TYPE y;
    TYPE r;
    CIRCLE() {}
    CIRCLE(TYPE _x_, TYPE _y_, TYPE _r_) : x(_x_), y(_y_), r(_r_) {}};
POINT Center(const CIRCLE & circle)
{
    return POINT(circle.x, circle.y);
}
TYPE Area(const CIRCLE & circle)
{
    return Pi * circle.r * circle.r;    //两个圆的公共面积
}
TYPE CommonArea(const  CIRCLE & A, const CIRCLE & B)
{
    TYPE area = 0.0;
    const CIRCLE & M = (A.r > B.r) ? A : B;
    const CIRCLE & N = (A.r > B.r) ? B : A;
    TYPE D = Distance(Center(M), Center(N));
    if ((D < M.r + N.r) && (D > M.r - N.r))
    {
        TYPE cosM = (M.r * M.r + D * D - N.r * N.r) / (2.0 * M.r * D);
        TYPE cosN = (N.r * N.r + D * D - M.r * M.r) / (2.0 * N.r * D);
        TYPE alpha = 2.0 * ArcCos(cosM);
        TYPE beta  = 2.0 * ArcCos(cosN);
        TYPE TM = 0.5*M.r*M.r*Sin(alpha);
        TYPE TN=0.5 * N.r * N.r * Sin(beta);
        TYPE FM = (alpha / 360.0) * Area(M);
        TYPE FN = (beta / 360.0) * Area(N);
        area = FM + FN - TM - TN;
    }
    else if (D <=  M.r - N.r)
    {
        area = Area(N);
    }
    return area;
}
//    矩形
//    矩形的线段
//        2
//      --------------- b
//      |               |
//    3 |               |  1
//    a ---------------
//         0
struct RECT
{
    POINT a; // 左下点  POINT b;  // 右上点
    RECT() {};
    RECT(const POINT & _a_, const POINT & _b_)
    {
        a = _a_;
        b = _b_;
    }
};
//根据下标返回多边形的边
SEG Edge(const RECT & rect, int idx)
{
    SEG edge;
    while (idx < 0) idx +=  4;
    switch (idx % 4)
    {
    case 0:
        edge.a = rect.a;
        edge.b = POINT(rect.b.x, rect.a.y);
        break;
    case 1:
        edge.a = POINT(rect.b.x, rect.a.y);
        edge.b = rect.b;
        break;
    case 2:
        edge.a = rect.b;
        edge.b = POINT(rect.a.x, rect.b.y);
        break;
    case 3:
        edge.a = POINT(rect.a.x, rect.b.y);
        edge.b = rect.a;
        break;
    default:
        break;
    }
    return edge;
}
TYPE Area(const RECT & rect)
{
    return (rect.b.x - rect.a.x) * (rect.b.y - rect.a.y);
}
//  两个矩形的公共面积
TYPE CommonArea(const  RECT & A, const RECT & B)
{
    TYPE area = 0.0;
    POINT LL(Max(A.a.x, B.a.x), Max(A.a.y, B.a.y));
    POINT UR(Min(A.b.x,  B.b.x), Min(A.b.y, B.b.y));
    if ((LL.x <=  UR.x) && (LL.y <= UR.y))
    {
        area = Area(RECT(LL, UR));
    }
    return area;
}// 多边形  ,逆时针或顺时针给出x,y
struct POLY
{
    int n; //n个点  TYPE * x;  //x,y为点的指针，首尾必须重合  TYPE * y;
    POLY() : n(0), x(NULL), y(NULL) {};
    POLY(int _n_, const TYPE * _x_, const TYPE * _y_)
    {
        n = _n_;
        x = new TYPE[n + 1];
        memcpy(x,  _x_, n*sizeof(TYPE));
        x[n] = _x_[0];
        y = new TYPE[n + 1];
        memcpy(y, _y_, n*sizeof(TYPE));
        y[n] = _y_[0];
    }
};//多边形顶点
POINT Vertex(const POLY & poly, int idx)
{
    idx %= poly.n;    //多边形的边
    return POINT(poly.x[idx],  poly.y[idx]);
}
SEG Edge(const POLY & poly, int idx)
{
    idx %= poly.n;
    return SEG(POINT(poly.x[idx],  poly.y[idx]),
               POINT(poly.x[idx  + 1], poly.y[idx + 1]));
} //多边形的周长
TYPE Perimeter(const POLY & poly)
{
    TYPE p = 0.0;
    for (int i = 0; i < poly.n; i++)
        p = p + Distance(Vertex(poly, i), Vertex(poly, i + 1));
    return p;
}
bool IsEqual(TYPE a, TYPE b)
{
    return (Abs(a - b) < Epsilon);
}
bool IsEqual(const POINT & a, const POINT & b)
{
    return (IsEqual(a.x, b.x) && IsEqual(a.y, b.y));
}
bool IsEqual(const LINE & A, const LINE & B)
{
    TYPE A1, B1, C1;
    TYPE A2, B2, C2;
    Coefficient(A, A1, B1, C1);
    Coefficient(B, A2, B2, C2);
    return IsEqual(A1 * B2, A2 * B1) &&
           IsEqual(A1 * C2, A2 * C1) &&  IsEqual(B1 * C2, B2 * C1);
}
// 判断点是否在线段上
bool IsOnSeg(const SEG & seg, const POINT & p)
{
    return (IsEqual(p, seg.a) || IsEqual(p, seg.b)) ||
           (((p.x - seg.a.x) * (p.x - seg.b.x) < 0 || (p.y - seg.a.y) * (p.y - seg.b.y) < 0) &&
            (IsEqual(Cross(seg.b, p, seg.a), 0)));
}
//判断两条线断是否相交，端点重合算相交
bool IsIntersect(const SEG & u, const SEG & v)
{
    return (Cross(v.a, u.b, u.a) * Cross(u.b, v.b, u.a) >=  0) &&
           (Cross(u.a, v.b, v.a) * Cross(v.b, u.b, v.a) >= 0) &&(Max(u.a.x, u.b.x)>=Min(v.
                   a.x, v.b.x))&&(Max(v.a.x, v.b.x)>= Min(u.a.x,u.b.x))&&(Max(u.a.y, u.b.y)>=Min(
                               v.a.y, v.b.y))&&(Max(v.a.y, v.b.y)>=Min(u.a.y,  u.b.y));
}
//判断两条线断是否平行
bool IsParallel(const LINE & A, const LINE & B)
{
    TYPE A1, B1, C1;
    TYPE A2, B2, C2;
    Coefficient(A, A1, B1, C1);
    Coefficient(B, A2, B2, C2);
    return (A1*B2==  A2*B1) &&((A1 * C2 != A2 * C1) || (B1 * C2 != B2 * C1));
}
//判断两条直线断是否相交
bool IsIntersect(const LINE & A, const LINE & B)
{
    return !IsParallel(A, B);    //直线相交的交点
}
POINT Intersection(const LINE & A, const LINE & B)
{
    TYPE A1, B1, C1;
    TYPE A2, B2, C2;
    Coefficient(A, A1, B1, C1);
    Coefficient(B, A2, B2, C2);
    POINT I(0, 0);
    I.x = - (B2 * C1 - B1 * C2) / (A1 * B2 - A2 * B1);
    I.y =   (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);
    return I;
}
bool IsInCircle(const CIRCLE & circle, const RECT & rect)
{
    return (circle.x - circle.r >=  rect.a.x) &&
           (circle.x + circle.r <= rect.b.x) &&(circle.y - circle.r >=  rect.a.y) &&
           (circle.y + circle.r <= rect.b.y);
}
//判断是否简单多边形
bool IsSimple(const POLY & poly)
{
    if (poly.n < 3) return false;
    SEG L1, L2;
    for (int i = 0; i < poly.n - 1; i++)
    {
        L1 = Edge(poly, i);
        for (int j = i + 1; j < poly.n; j++)
        {
            L2 = Edge(poly, j);
            if (j == i+1)
            {
                if  (IsOnSeg(L1, L2.b)||IsOnSeg(L2, L1.a))  return false;
            }
            else if (j == poly.n - i - 1)
            {
                if (IsOnSeg(L1, L2.a) || IsOnSeg(L2, L1.b))  return false;
            }
            else
            {
                if (IsIntersect(L1, L2))  return false;    // for i
            }
        } // for j
    }
    return true;
}
//求多边形面积
TYPE Area(const POLY & poly)
{
    if (poly.n < 3) return TYPE(0);
    double s = poly.y[0] * (poly.x[poly.n - 1] - poly.x[1]);
    for (int i = 1; i < poly.n; i++)
    {
        s += poly.y[i] * (poly.x[i - 1] - poly.x[(i + 1) % poly.n]);
    }
    return s/2;
}
//判断是否在多边形上
bool IsOnPoly(const POLY & poly, const POINT & p)
{
    for (int i = 0; i < poly.n; i++)
    {
        if (IsOnSeg(Edge(poly,  i), p))   return true;
    }
    return false;
}
//判断是否在多边形内部
bool IsInPoly(const POLY & poly, const POINT & p)
{
    SEG L(p, POINT(Infinity, p.y));
    int count = 0;
    for (int i = 0; i < poly.n; i++)
    {
        SEG S = Edge(poly, i);
        if (IsOnSeg(S, p))
        {
            return false; //如果想让 在poly上则返回 true,则改为true
        }
        if (!IsEqual(S.a.y, S.b.y))
        {
            POINT & q = (S.a.y > S.b.y)?(S.a):(S.b);
            if (IsOnSeg(L, q))
            {
                ++count;
            }
            else if(!IsOnSeg(L,S.a)&&!IsOnSeg(L,S.b)&&IsIntersect(S,L))
            {
                ++count;
            }
        }
    }
    return (count % 2 != 0);
}
// 点阵的凸包，返回一个多边形
POLY ConvexHull(const POINT * set, int n)            // 不适用于点少于三个的情况
{
    POINT * points = new POINT[n];
    memcpy(points, set, n * sizeof(POINT));
    TYPE * X = new TYPE[n];
    TYPE * Y = new TYPE[n];
    int i, j, k = 0, top = 2;
    for(i = 1; i < n; i++)
    {
        if((points[i].y<points[k].y)||((points[i].y==points[k].y)&&
                                       (points[i].x<points[k].x)))
        {
            k  = i;
        }
    }
    std::swap(points[0], points[k]);
    for (i = 1; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if ((Cross(points[j], points[k], points[0]) >0)||((Cross(points[j], points[k],
                    points[0]) == 0) && (Distance(points[0], points[j])<Distance(points[0], points[k]
                                                                                ))))
            {
                k = j;
            }
        }
        std::swap(points[i], points[k]);
    }
    X[0] = points[0].x;
    Y[0] = points[0].y;
    X[1] = points[1].x;
    Y[1] = points[1].y;
    X[2] = points[2].x;
    Y[2] = points[2].y;
    for (i = 3; i < n; i++)
    {
        while(Cross(points[i],POINT(X[top],Y[top]),POINT(X[top
                    -1],Y[top-1]))>=0)
        {
            top--;
        }
        ++top;
        X[top] = points[i].x;
        Y[top] = points[i].y;
    }
    delete [] points;
    POLY poly(++top, X, Y);
    delete [] X;
    delete [] Y;
    return poly;
}
//最近点对的距离, Written By PrincessSnow
#define MAXN 100000
POINT pt[MAXN];
bool cmp(POINT n1, POINT n2)
{
    return (n1.x<n2.x  || n1.x==n2.x  && n1.y<n2.y);
}
double Get(double dis, int mid, int start, int end)
{
    int s=mid,  e=mid,  i, j;
    double t;
    while(s > start && pt[mid].x - pt[s].x <= dis)     s--;
    while(e < end && pt[e].x - pt[mid].x <=  dis)     e++;
    for(i=s; i <= e; i++)
        for(j=i+1;  j <= e && j <=  i+7; j++)
        {
            t = Distance(pt[i], pt[j]);
            if(t < dis)     dis=t;
        }
    return dis;
}
double ClosestPairDistance(int start, int end)
{
    int m = end-start+1, mid, i;
    double t1, t2, dis=-1, t;
    if(m <= 3)
    {
        for(i=start; i < end; i++)
        {
            t = Distance(pt[i] , pt[i+1]);
            if(t < dis || dis ==  -1)     dis = t;
        }
        t = Distance(pt[start] , pt[end]);
        if(t < dis) dis=t;
        return dis;
    }
    if(m%2  == 0)     mid = start + m/2 - 1;
    else               mid = start + m/2;
    if(m%2  == 0)
    {
        t1 = ClosestPairDistance(start, mid);
        t2 = ClosestPairDistance(mid+1, end);
    }
    else
    {
        t1 =ClosestPairDistance(start,mid);
        t2=ClosestPairDistance(mid+1,end);
    }
    if(t1 < t2)     dis = t1;
    else          dis = t2;
    dis = Get(dis, mid, start, end);
    return dis;
}


//1.  球面上两点最短距离
// 计算圆心角lat 表示纬度, -90 <= w <= 90, lng 表示经度
// 返回两点所在大圆劣弧对应圆心角,  0 <= angle <=  pi
double angle(double lng1, double lat1, double lng2, double lat2)
{
    double dlng = fabs(lng1 - lng2) * pi / 180;
    while(dlng >= pi+pi)      dlng -= pi+pi;
    if(dlng > pi)     dlng = pi + pi - dlng;
    lat1 *= pi / 180,     lat2 *= pi / 180;
    return acos( cos(lat1)*cos(lat2)*cos(dlng) + sin(lat1)*sin(lat2) );
}
// 计算距离, r为球半径
double line_dist(double  r, double lng1, double lat1, double lng2, double lat2)
{
    double dlng = fabs(lng1 - lng2) * pi / 180;
    while(dlng  >= pi+pi)      dlng -= pi+pi;
    if(dlng > pi)     dlng = pi + pi - dlng;
    lat1 *= pi / 180,     lat2 *= pi / 180;
    return r*sqrt(2-2*( cos(lat1)*cos(lat2)*cos(dlng)+ sin(lat1)*sin(lat2)) );
}
// 计算球面距离, r为球半径
double sphere_dist(double r, double lng1,double lat1,double lng2, double lat2)
{
    return r * angle(lng1, lat1, lng2, lat2);
}


//2.  三点求圆心坐标
double GetRadiusBy3Points(double  x1, double y1,
                          double x2, double y2,  double x3, double y3, double &x, double &y)
{
    // 由 ( x - x1 )^2 + ( y - y1 )^2 = ( x - x2 )^2 + ( y - y2 )^2 得
    // 2*( x2 - x1 )*x + 2*( y2 - y1 )*y = x2^2 - x1^2 + y2^2 - y1^2
    // 同理得
    // 2*( x3 - x2 )*x + 2*( y3 - y2 )*y = x3^2 - x2^2 + y3^2 - y2^2
    // 由行列式解方程得 x , y
    double a11, a12, a21, a22, b1, b2;
    double d, d1, d2 ;
    a11 = 2 * ( x3 - x2 );
    a12 = 2 * ( y3 - y2 );
    a21 = 2 * ( x2 - x1 );
    a22 = 2 * ( y2 - y1 );
    b1 = x3*x3 - x2*x2 + y3*y3 - y2*y2;
    b2 = x2*x2 - x1*x1 + y2*y2 - y1*y1;
    d = a11*a22 - a12*a21;
    d1 = b1*a22 - a12*b2;
    d2 = a11*b2 - b1*a21;
    // x , y 是圆心坐标
    x = d1 / d;
    y = d2 / d;
    return  (x1 - x)*(x1 - x) + (y1 - y)*(y1 - y);
}
//
//
//3.  三角形几个重要的点
//设三角形的三条边为a,  b, c，且不妨假设a <=  b <=  c
//三角形的面积可以根据海伦公式算得，如下：
//s = sqrt(p * (p - a) * (p - b) * (p - c)), p = (a +  b + c) / 2
//1. 费马点(该点到三角形三个顶点的距离之和最小)
//有个有趣的结论：若三角形的三个内角均小于120度，
//那么该点连接三个顶点形成的三个角均为120度；若三角形存在一个内角
//大于120度，则该顶点就是费马点)
//计算公式如下:
//若有一个内角大于120度（这里假设为角C)，则距离为a  +  b
//若三个内角均小于120度，则距离为
//sqrt((a * a +  b * b + c * c + 4 * sqrt(3.0) * s) / 2),其中
//2.内心----角平分线的交点
//令x =  (a + b - c) / 2, y =  (a - b +  c) / 2, z =  (-a +  b + c) / 2, h =  s / p
// 计算公式为 sqrt(x * x + h * h) + sqrt(y * y +  h * h) +  sqrt(z * z +  h * h)
//3.重心----中线的交点
//ACM算法模板集
//  - 46 -
//计算公式如下：
//2.0 / 3 * (sqrt((2 * (a * a +  b * b) - c * c) / 4)
//             +  sqrt((2 * (a * a +  c * c) - b * b) / 4)
//             +  sqrt((2 * (b * b + c * c) - a * a) / 4))
//4.垂心----垂线的交点
//计算公式如下：
//3 * (c / 2 / sqrt(1 - cosC * cosC))
