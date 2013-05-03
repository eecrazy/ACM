/*这个是求扩展离散对数问题。XY mod Z = K，给出X，Z，K，求Y。
当Z是素数的时候直接用baby-step算法即可了。但是，模数不是素数的情况
怎么办了。方程a^X = b % c，可以进行一系列的转化。假设d = gcd(a,c)，
由a^(x-1)*a = b % c，知道a^(x-1)要存在必须满足
gcd(a,c)|b，如果满足这个条件，那么我们可以在方程2边同时除以d，方程是不变的。
因为a^x = b + k * c，再除以公约数d，得到方程a^(x-1)*a/d = b / d + k * c / d。
根据以上推论，我们可以不断的除以d，直到gcd(a,c)=1。假设我们除了k次，那么
方程转化为a^(x-k) * a^k/d^k = b / d^k + k * c / d^k。令d = a^k/d^k，
b' = b / d^k，c' = c / d^k，x' = x - k，方程转化为a^x' * d = b' % c'，
得到a^x' = b' * d^-1 % c'。   现在直接用baby-step
解方程a^x' = b' * (d^-1) % c'即可。注意到x=x'+k，如果存在x小于k的解，
那么x'小于0，但是由baby-step是不会求负的次数的，所以需要先枚举一下
是否存在小于k的解，由于输入的数据不会超过10^9的，假设k不超过50
进行枚举即可了。
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long long INT;
#define MAX (1000000)
INT nData[MAX];
INT nKey[MAX];

INT HashPos(INT key)
{
    return ((unsigned)(key ^ 0xA5A5A5A5)) % MAX;
}

void HashAdd(INT key, INT data)
{
    INT nPos = HashPos(key);
    while (nData[nPos] != -1)
    {
        nPos = (nPos + 1) % MAX;
    }
    nData[nPos] = data;
    nKey[nPos] = key;
}

INT HashQuery(INT key)
{
    INT nPos = HashPos(key);
    while (nData[nPos] != -1)
    {
        if (nKey[nPos] == key)
        {
            return nData[nPos];
        }
        nPos = (nPos + 1) % MAX;
    }

    return -1;
}

INT MultMod(INT nA, INT nB, INT nC)
{
    INT nAns = 0;
    while (nB)
    {
        if (nB & 1)
        {
            nAns = (nAns + nA) % nC;
        }
        nA = (2 * nA) % nC;
        nB >>= 1;
    }
    return nAns;
}

INT PowerMod(INT nA, INT nX, INT nC)
{
    INT nAns = 1;
    nA %= nC;
    while (nX)
    {
        if (nX & 1)
        {
            nAns = MultMod(nAns, nA, nC);
        }
        nA = MultMod(nA, nA, nC);
        nX >>= 1;
    }
    return nAns;
}

INT gcd(INT nA, INT nB)
{
    if (nA < nB)swap(nA, nB);
    while (nB)
    {
        INT nT = nA;
        nA = nB;
        nB = nT % nB;
    }
    return nA;
}
//d = nA * nX + nB * nY(nA > nB, nA是模数)
INT egcd(INT nA, INT nB, INT& nX, INT& nY)
{
    if (nA < nB)swap(nA, nB);
    if (nB == 0)
    {
        nX = 1;
        nY = 0;
        return nA;
    }
    INT nRet = egcd(nB, nA % nB, nX, nY);
    INT nT = nX;
    nX = nY;
    nY = nT - (nA / nB) * nY;
    return nRet;
}

INT GetAns(INT nA, INT nB, INT nC)
{
    if (nC == 0)return -1;
    //先枚举0-50,扩展baby-step的过程可能会漏掉这些解
    INT nTemp = 1;
    nB %= nC;
    for (INT i = 0; i <= 50; ++i)
    {
        if (nTemp == nB)
        {
            return i;
        }
        nTemp = MultMod(nTemp, nA, nC);
    }

    //如果nC不是素数,那么方程nA^x = nB + k*nC
    //可以不到除以gcd(nC,nA)
    //如果gcd(nC,nA)|nB不成立,方程无解，
    //这个由a*x=b%c有解必须满足gcd(a,c)|b一样
    INT d;
    INT nD = 1;//nD最后是A^k次,k是nC中因子d的次数
    INT k = 0;
    while ((d = gcd(nC, nA)) != 1)
    {
        k++;
        nC /= d;
        if (nB % d)return -1;
        nB /= d;
        nD = MultMod(nD, nA / d, nC);
    }
    //现在方程转化为nA^(x-k) * nA^k/d^k = nB/d^k % nC/d^k
    //其实就是方程2侧除以d^k次而已,这样的做法与原方程是等价的
    //令nD = nA^k/d^k,则nA^x'*nD = nB' % nC',
    //解该方程,那么x=x'+k
    //注意,如果x<k,那么x'为负数,baby-step无法求出,故在函数开头进行枚举
    memset(nKey, -1, sizeof(nKey));
    memset(nData, -1, sizeof(nData));
    INT nM = ceil(sqrt(1.0 * nC));
    nTemp = 1;
    for (INT j = 0; j <= nM; ++j)
    {
        HashAdd(nTemp, j);
        nTemp = MultMod(nTemp, nA, nC);
    }
    INT nK = PowerMod(nA, nM, nC);
    for (int i = 0; i <= nM; ++i)
    {
        INT x, y;
        egcd(nC, nD, x, y);//y = nD^-1,nD = nD*(nA^m)^i
        y = (y + nC) % nC;//这句话是必须的,y很可能就是负数
        INT nR = MultMod(y, nB, nC);//nR=nB*nD^-1
        int j = HashQuery(nR);
        if (j != -1)
        {
            return nM * i + j + k;
        }

        nD = MultMod(nD, nK, nC);
    }
    return -1;
}

int main()
{
    INT nA, nB, nC;

    while (scanf("%I64d%I64d%I64d", &nA, &nC, &nB)!=EOF, nA + nB + nC)
    {
        INT nAns = GetAns(nA, nB, nC);
        if (nAns == -1)
        {
            printf("No Solution\n");
        }
        else
        {
            printf("%I64d\n", nAns);
        }
    }
    return 0;
}
