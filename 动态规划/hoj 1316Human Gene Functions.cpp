#include <iostream>
#include <string>
#include <vector>
using namespace std;

int nValue[5][5]=
{
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, -100}
};

int Translate(char ch)
{
    switch(ch)
    {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    default:
        return 4;
    }
}

int main()
{
    int nTest;
    string strSeqX, strSeqY;
    cin>>nTest;
    while(nTest--)
    {
        int m, n, nCost[101][101];
        cin>>m>>strSeqX>>n>>strSeqY;
        nCost[0][0]=0;
        for (int i=0; i<m; i++) nCost[i+1][0]=nCost[i][0]+nValue[Translate(strSeqX[i])][Translate('-')];
        for (int j=0; j<n; j++) nCost[0][j+1]=nCost[0][j]+nValue[Translate('-')][Translate(strSeqY[j])];
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<n; j++)
            {
                int nTmp;
                nCost[i+1][j+1]=nCost[i][j]+nValue[Translate(strSeqX[i])][Translate(strSeqY[j])];
                if ((nTmp=nCost[i][j+1]+nValue[Translate(strSeqX[i])][Translate('-')])>nCost[i+1][j+1]) nCost[i+1][j+1]=nTmp;
                if ((nTmp=nCost[i+1][j]+nValue[Translate('-')][Translate(strSeqY[j])])>nCost[i+1][j+1]) nCost[i+1][j+1]=nTmp;
            }
        }
        cout<<nCost[m][n]<<endl;
    }
    return 0;
}