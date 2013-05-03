//字符串和数值hash
// 整数hash
// 大素数104729,  224737,  611953,  1299709,  2015177
const int MOD =  20023;
bool bhash[MOD];
int vhash[MOD];
int cnt[MOD];
bool find_hash(int & pos)
{
    int val = pos;
    pos %= MOD;
    for (; bhash[pos]; pos=(pos+1)%MOD)
    {
        if (vhash[pos] == val)return true;
    }
    return false;
}
int make_hash(int  val)
{
    int pos = val;
    if (! find_hash(pos))
    {
        bhash[pos]  = true;
        vhash[pos] = val;
        cnt[pos] =  0;
    }
    cnt[pos] ++;
    return  pos;
}
//字符串hash
const int MOD =  20023;
bool bhash[MOD];
char vhash[MOD][45];
char  str[45];
int cal_str()
{
    int i, j, pos;
    for (i=pos=0,j=1; str[i]; i++,j=(j*27)&INT_MAX,pos&=INT_MAX)
    {
        int num = str[i] - 'a';
        if (str[i] == ' ')num = 26;
        pos += j*num;
    }
    return pos % MOD;
}
bool find_hash(int & pos)
{
    pos = cal_str();
    for (; bhash[pos]; pos=(pos+1)%MOD)
    {
        if (strcmp(vhash[pos], str) ==  0)return true;
    }
    return false;
}
int make_hash()
{
    int pos;
    if (! find_hash(pos))
    {
        bhash[pos]  = true;
        strcpy(vhash[pos], str);
    }
    return pos;
}
