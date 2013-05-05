#include<stdio.h>
#include<string.h>
#include<queue>
int map[210][210];
bool isprime[40400];
bool visited[210][210];
struct node
{
    int x, y;
} site[40400];
int drive[4][2] = {{ -1, 0}, {1, 0}, {0, -1}, {0, 1}};
using namespace std;
queue<int>Q;
void find_prime()
{
    int i, j;
    memset(isprime, true, sizeof(isprime));
    isprime[1] = false;
    for (i = 2; i <= 10009; i++)
        if (isprime[i])
            for (j = 2 * i; j <= 10009; j += i)
                isprime[j] = false;
}
void build_map(int p, int q, int s, int c)
{
    if (s == 0) return;
    int i;
    for (i = q; i < q + c; i++)   
      map[p][i] = s--;
    for (i = p + 1; i < p + c; i++) 
      map[i][q + c - 1] = s--;
    for (i = q + c - 2; i > q; i--)
     map[p + c - 1][i] = s--;
    for (i = p + c - 1; i > p; i--)
     map[i][q] = s--;
    build_map(p + 1, q + 1, s, c - 2);
}
int main()
{
    int i, j, n, m, x, y, step, k;
    find_prime();
    build_map(1, 1, 40000, 200);
    for (i = 1; i <= 200; i++)
        for (j = 1; j <= 200; j++)
        {
            site[map[i][j]].x = i;
            site[map[i][j]].y = j;
        }
    k = 1;
    while (scanf("%d%d", &n, &m))
    {
        step = 0;
        x = site[n].x; y = site[n].y;
        while (!Q.empty()) Q.pop();
        memset(visited, 0, sizeof(visited));
        Q.push(x); Q.push(y); Q.push(step);
        visited[x][y] = true;
        while (Q.size())
        {
            x = Q.front(); Q.pop();
            y = Q.front(); Q.pop();
            step = Q.front(); Q.pop();
            if (map[x][y] == m)
                break ;
            for (i = 0; i < 4; i++)
            {
                int xx = x + drive[i][0];
                int yy = y + drive[i][1];
                if (xx >= 1 && xx <= 200 && yy >= 1 && yy <= 200 && !visited[xx][yy] && !isprime[map[xx][yy]])
                {
                    Q.push(xx);
                    Q.push(yy);
                    Q.push(step + 1);
                    visited[xx][yy] = true;
                }
            }
        }
        if (map[x][y] == m)
            printf("Case %d: %d\n", k++, step);
        else
            printf("Case %d: impossible\n", k++);
    }
}