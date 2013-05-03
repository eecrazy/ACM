#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    int a1,a2,a3,a4,a5,a6;
    while(cin>>a1>>a2>>a3>>a4>>a5>>a6)
    {
        if(!a1&&!a2&&!a3&&!a4&&!a5&&!a6)
        {
            break;
        }
        //处理66的货物
        int min=a6;
        //处理55的货物
        min+=a5;
        a1-=a5*11;
        //处理44的货物
        min+=a4;

        if(a2>a4*5)
        {
            a2-=a4*5;
        }
        else
        {
            a1-=4*(a4*5-a2);
            a2=0;
        }
        //处理33的货物
        min+=a3/4;
        if(a3%=4)
        {
            min++;
            if(a3==3)
            {
                if(a2>0)
                {
                    a2--;
                    a1-=5;
                }
                else
                {
                    a1-=9;
                }
            }
            else if(a3==2)
            {
                if(a2>=3)
                {
                    a2-=3;
                    a1-=6;
                }
                else
                {
                    a1-=4*(3-a2)+6;
                    a2=0;
                }
            }
            else if(a3==1)
            {
                if(a2>=5)
                {
                    a2-=5;
                    a1-=7;
                }
                else
                {
                    a1-=4*(5-a2)+7;
                    a2=0;
                }
            }
        }
        //处理22的货物
        if(a2>0)
        {
            min+=a2/9;
            if(a2%=9)
            {
                a1-=(9-a2)*4;
                min++;
            }
        }
        //处理11的货物
        if(a1>0)
        {
            min+=a1/36;
            if(a1%=36)min++;
        }
        cout<<min<<endl;
    }
}
