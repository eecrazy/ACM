#include <cstdio>
#include <iostream>
using namespace std;
#include <cmath>
#include <string.h>
/*求所在月份的天数*/
int daysMonth(int year,int month,int day)
{

    int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int i,sum=0;
    for(i=0;i<month;i++)
       sum+=days[i];
    if(month>2)  /*如果是闰年则2月加一天*/
        if((year%4==0)&&(year%100!=0)||(year%400==0))
            sum+=1;
       sum+=day;
       return sum;
}
/*交换位置，避免负值*/
void swap(int x1,int x2)
{
    int tmp=x1;
    x1=x2;
    x2=tmp;
}
long countDate(int y1,int m1,int d1,int y2,int m2,int d2)
{
    int daysyear1,daysyear2;
    long totalDays=0;
    int total_day1;
    int tmpYear;
    int tmpDays;
    //printf("The first Date is %ld-%ld-%ld/n",y1,m1,d1);
   // printf("The second Date is %ld-%ld-%ld/n",y2,m2,d2);
    if(y1>y2)
    {
       swap(y1,y2);
       swap(m1,m2);
       swap(d1,d2);
    }
    if(y1==y2)
    {
       daysyear1=daysMonth(y1,m1,d1);
       daysyear2=daysMonth(y2,m2,d2);
       totalDays=abs(daysyear1-daysyear2)+1;
       //printf("totalDays is %ld/n",totalDays-1);
    }
    else
    {
       daysyear1=daysMonth(y1,m1,d1);
       total_day1=365-daysyear1+1;
       if(m1<=2)
        if(y1%4==0&&(y1%100!=0)||(y1%400==0))
         total_day1+=1;
       totalDays+=total_day1;
       tmpYear=y1;
       while(++tmpYear<y2)
       {
            tmpDays=365;
            if((tmpYear%4==0)&&(tmpYear%100!=0)||(tmpYear%400==0))
             tmpDays+=1;
            totalDays+=tmpDays;
       }
       daysyear2=daysMonth(y2,m2,d2);
       totalDays+=daysyear2;
    }
   // return totalDays-1;
    printf("%ld\n",totalDays-1);
}
int main()
{
    int y1,m1,d1,y2,m2,d2;
    while(scanf("%ld:%ld:%ld%ld:%ld:%ld",&y1,&m1,&d1,&y2,&m2,&d2)!=EOF)
    {
        if(y1>y2)
        {
            countDate(y2,m2,d2,y1,m1,d1);
        }
        else if(y1==y2&&m1>m2)
        {
            countDate(y2,m2,d2,y1,m1,d1);
        }
        else if(y1==y2&&m1==m2&&d1>d2)
        countDate(y2,m2,d2,y1,m1,d1);
        else
        countDate(y1,m1,d1,y2,m2,d2);

    }

}
