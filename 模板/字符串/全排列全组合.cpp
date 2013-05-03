//全排列,全组合
/**** **** **** **** **** ****
*    Function Name :        全排列,全组合
**** **** **** **** **** ****/
void createper(int n) //全排列
{
    int total,i,j,k,t,*a=new int[n],top;
    total=1;
    for(i=1; i<=n; i++)
    {
        a[i]=i;
        total*=i;
    }
    for(i=1; i<n; i++)      printf("%d  ",a[i]);
    printf("%d\n",a[n]);
    for(i=1; i<total; i++)
    {
        j=n;
        while(a[j]<a[j-1])  j--;
        k=n;
        while(a[j-1]>a[k])  k--;
        t=a[j-1];
        a[j-1]=a[k];
        a[k]=t;
        top=(j+n-1)/2;
        for(k=j; k<=top; k++)
        {
            t=a[k];
            a[k]=a[n-k+j];
            a[n-k+j]=t;
        }
        for(j=1; j<n; j++)  printf("%d ",a[j]);
        printf("%d\n",a[n]);
    }
}
void createfab(int m,int n) //全组合
{
    int i,j,lcount,*a=new int[n+2];
    for(i=1; i<=n; i++)      a[i]=i;
    a[n+1]=m+1;
    for(j=1; j<n; j++)      printf("%d  ",a[j]);
    printf("%d\n",a[n]);
    lcount=1;
    while(a[1]<m-n+1)
    {
        for(i=n; i>0; i--)
        {
            if(a[i]<a[i+1]-1)
            {
                a[i]++;
                for(j=i; j<n; j++)      a[j+1]=a[j]+1;
                for(j=1; j<n; j++)      printf("%d  ",a[j]);
                printf("%d\n",a[n]);
                lcount++;
                break;
            }
        }
    }
}
