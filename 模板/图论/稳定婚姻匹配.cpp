/**** **** **** **** **** ****
*      Function Name  :  稳定婚姻匹配gale_shapley算法
*      Description  :          HDOJ  1522 Marriage  is Stable
**** **** **** **** **** ****/
//rmw[i][j]代表i男对女生的喜欢排名
//lwm[i][j]代表i女对j男的喜欢程度
const int MAX = 510;
int w,m,n;
int rmw[MAX][MAX];
int  lmw[MAX][MAX],  lwm[MAX][MAX];
int couple[MAX];
char sman[MAX][110],  swoman[MAX][110];
queue<int>  SQ;
void gale_shapley()
{
    int i,man,woman;
    while(!SQ.empty())
    {
        SQ.pop();
    }
    memset(couple,-1,sizeof(couple));
    for(i=1; i<=n; i++)
    {
        SQ.push(i);
    }
    while(!SQ.empty())
    {
        man  =  SQ.front();
        for(i=1; i<=n; i++)
        {
            if(rmw[man][i]  != -1)
            {
                //选择为被拒绝且最喜欢的女生
                woman  =  rmw[man][i];
                rmw[man][i]  = -1;
                int pre = couple[woman];
                if(pre == -1)
                {
                    couple[woman]  =  man;
                    SQ.pop();
                    break;
                }
                else
                {
                    if(lwm[woman][man]  > lwm[woman][pre])
                    {
                        SQ.pop();
                        SQ.push(pre);
                        couple[woman]  = man;
                        break;
                    }
                }
            }
        }
    }//while
  }
