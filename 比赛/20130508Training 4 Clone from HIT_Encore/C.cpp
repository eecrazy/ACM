//姜慧文的没有AC的代码！
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

int len, l;
char num[5000], f[5000];
int as[500];

long long mod(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = (ans * a);
            b--;
        }
        b /= 2;
        a = a * a;
    }
    return ans;
}
int main()
{
    bool tag = 0;
    while (gets(f))
    {
        l = strlen(f);
        //printf("%s\n", f);
        if (l == 0)
        {
            scanf(" %s", num);
            for (int i = len - 1; i >= 0; i--)
                if (num[i] <= ' ') len--;
                else break;
            gets(f);
            len = strlen(num);
            for (int i = 0; i < len; i++)
                as[num[i]] = i;
            if (tag) printf("\n");
            tag = 1;
        }
        else
        {
            int x = 1, max = 0;
            long long ans = 0;
            for (int i = l - 1; i >= 0; i--)
                if (f[i] <= ' ') l--;
                else break;
            for (int j = l - 1; j >= 0; j--)
            {
                if (as[f[j]] > max) max = as[f[j]];
            }
            //printf("%d\n", max);
            for (int j = l - 1; j >= 0; j--)
            {
                for (int k = max + 1; k <= len; k++)
                {
                    ans += as[f[j]] * mod(k, l - j - 1);
                    //printf("%d^%d = %d\n", k, l-j-1, mod(k, l-j-1));
                }
            }
            printf("%lld\n", ans);
            tag = 1;
        }
    }
    return 0;
}
// timer的java-AC代码：
import java.util.*;
import java.math.*;

public class Main
{
    static int M = 256;
    static int MAXN = 625;
    static BigInteger[][] a = new BigInteger[M][MAXN];
    static int n;
    static int[] v = new int[M];
    static int mymax;

    public static void init()
    {
        int i, j;
        for (i = 2; i < M; i++)
        {
            a[i][0] = new BigInteger("1");
            a[i][1] = new BigInteger("" + i);
            for (j = 2; j < MAXN; j++)
                a[i][j] = a[i][j - 1].multiply(a[i][1]);
        }
        //   System.out.println(a[10][1].toString());
    }

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        BigInteger t;
        int i, l;
        String e;
        char r;
        boolean flag = false;
        init();
        while (cin.hasNext())
        {
            e = cin.nextLine();
            l = e.length();
            if (l == 0) continue;
            if (flag) System.out.println();
            else flag = true;
            n = 0;
            for (i = 0; i < l; i++)
            {
                r = e.charAt(i);
                if (r <= ' ') continue;
                v[r] = n++;
            }
            while (cin.hasNext())
            {
                e = cin.nextLine();
                //if (e.charAt(0)=='\n') break;
                if (e.length() == 0) break;
                l = e.length();
                mymax = -1;
                for (i = l - 1; i >= 0; i--)
                {
                    if (e.charAt(i) <= ' ') continue;
                    if (v[e.charAt(i)] > mymax) mymax = v[e.charAt(i)];
                }
                if (mymax == 0)
                {
                    System.out.println("0");
                    continue;
                }
                int k, j;
                BigInteger ans = new BigInteger("0");
                BigInteger t2;
                for (i = mymax + 1; i <= n; i++)
                {
                    k = 0;
                    t = new BigInteger("0");
                    for (j = l - 1; j >= 0; j--)
                    {
                        if (e.charAt(j) <= ' ') continue;
                        BigInteger temp = new BigInteger("" + v[e.charAt(j)]);
                        t2 = a[i][k].multiply(temp);
                        //System.out.println(t2.toString());
                        t = t.add(t2);
                        //System.out.println(t.toString());
                        k++;
                    }
                    ans = ans.add(t);
                }
                System.out.println(ans.toString());
            }
        }
    }
};