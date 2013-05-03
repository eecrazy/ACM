#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 128;
const int MAXM = 128;
const int MAXL = 4;

struct edgeType
{
    int v, w;
    edgeType ( int a, int b ) : v( a ), w( b ) {}
};

vector< edgeType > edge[ MAXN ];
int vNum[ MAXN ];
int dis[ MAXN ];
int n;

bool spfa()
{
    int time[ MAXN ];
    bool flag[ MAXN ];
    int inf = n + 1;
    queue< int > que;
    que.push( n );
    memset( time, 0, n * sizeof( int ) );
    time[ n ] = 1;
    memset( flag, false, n * sizeof( bool ) );
    flag[ n ] = true;
    while ( !que.empty() )
    {
        int u = que.front();
        flag[ u ] = false;
        que.pop();
        for ( int i = 0; i < vNum[ u ]; ++i )
        {
            if ( dis[ edge[ u ][ i ].v ] > dis[ u ] + edge[ u ][ i ].w )
            {
                dis[ edge[ u ][ i ].v ] = dis[ u ] + edge[ u ][ i ].w;
                ++time[ edge[ u ][ i ].v ];
                if ( time[ edge[ u ][ i ].v ] == inf )
                {
                    return false;
                }
                if ( !flag[ edge[ u ][ i ].v ] )
                {
                    que.push( edge[ u ][ i ].v );
                    flag[ edge[ u ][ i ].v ] = true;
                }
            }
        }
    }
    return true;
}

int main()
{
    int m;
    int a, b, c;
    char op[ MAXL ];
    while ( scanf( "%d", &n ) == 1 && n > 0 )
    {
        ++n;
        memset( dis, 1, n * sizeof( int ) );
        dis[ n ] = 0;
        edge[ n ].clear();
        for ( int i = 0; i < n; ++i )
        {
            edge[ n ].push_back( edgeType( i, 0 ) );
            edge[ i ].clear();
        }
        scanf( "%d", &m );
        for ( int i = 0; i < m; i++ )
        {
            scanf( "%d %d %s %d", &a, &b, op, &c );
            if ( op[ 0 ] == 'g' )
            {
                edge[ a + b ].push_back( edgeType( a - 1, -c - 1 ) );
            }
            else
            {
                edge[ a - 1 ].push_back( edgeType( a + b, c - 1 ) );
            }
        }
        for ( int i = 0; i <= n; ++i )
        {
            vNum[ i ] = edge[ i ].size();
        }
        if ( spfa() )
        {
            puts( "lamentable kingdom" );
        }
        else
        {
            puts( "successful conspiracy" );
        }
    }
    return 0;
}