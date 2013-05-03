//最小点基，最小权点基
// HDOJ  1827  Summer  Holiday
void Gabow()
{
    int i,j,l;
    //dfs in original  graph
    memset(id,  0, sizeof(id));
    memset(vis,  0, sizeof(vis));
    scc = step =  1;
    order_pos = order2_pos = 0;
    for (i=1; i<=n  ; i++)
    {
        if (vis[i] ==  0)
        {
            dfs(i);
        }
    }
    scc --;
}
void top_sort()
{
    int i,j,k,l,m =  0;
    memset(out_degre,0,sizeof(out_degre));
    memset(sel,  0x7f,sizeof(sel));
    l = SQ.size();
    while (l --)
    {
        SQ.pop();
    }
    for (i=1; i<=n; i++)
    {
        int id1 = id[i];
        l = path[i].size();
        for (j=0; j<l; j++)
        {
            int id2 = id[ path[i][j] ];
            if (id1 != id2)
            {
                out_degre[id2]  ++;
                dag[id1].push_back(id2);
            }
        }
    }
    for (i=1; i<=scc; i++)
    {
        if (out_degre[i]  ==  0)
        {
            SQ.push(i);
        }
    }
    while (!SQ.empty())
    {
        int now = SQ.front();
        SQ.pop();
        l = dag[now].size();
        for (i=0; i<l; i++)
        {
            int next = dag[now][i];
            out_degre[next] --;
            if (out_degre[next] == 0)
            {
                SQ.push(next);
                m --;//find non-hightest scc
                sel[next] = -1;
            }
        }
    }
    for (i=1; i<=n; i++)
    {
        if (sel[ id[i] ] != -1)  //selection mininum  cost in the highest scc
        {
            sel[ id[i]  ] = sel[ id[i]  ] > cost[i] ? cost[i] : sel[ id[i] ];
        }
    }
    min_cost =  0;
    for (i=1; i<=scc; i++)
    {
        if (sel[i] != -1)
        {
            min_cost += sel[i];
        }
    }
    min_num  = scc+m;
}
int main()
{
    int i,x,y;
    path.resize(NMAX);
    dag.resize(NMAX);
    while (scanf("%d  %d",&n,  &m)==2)
    {
        for (i=0; i<=n; i++)
        {
            path[i].clear();
            dag[i].clear();
        }
        for (i=1; i<=n; i++)
        {
            scanf("%d", cost+i);
        }
        for (i=1; i<=m; i++)
        {
            scanf("%d  %d",  &x,&y);
            path[x].push_back(y);
        }
        Gabow();
        top_sort();
        //min_num  : mininum  vertex number
        //min_cost  : mininum  cost
        printf("%d  %d\n", min_num,  min_cost);
    }
}
