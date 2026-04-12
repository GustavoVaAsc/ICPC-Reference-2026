const ll mod=1e9+7;
ll dp[20][10][2][2];
//ascii https://elcodigoascii.com.ar/

ll mem(int idx,int tight,int prev,int ld,string s)
{
    if(idx==0)
    {
        return 1;
    }
    if(dp[idx][prev][ld][tight]!=-1){
        return dp[idx][prev][ld][tight];
    }
    int k=9;
    if(tight) k=s[s.size()-idx]-'0';
    ll sum=0;
    for(int i=0;i<=k;i++)
    {
        if(ld || prev!=i)
        {
            int new_ld,new_tight;
            if(i==0 && ld) new_ld=1;
            else new_ld=0;
            if(tight && k==i) new_tight=1;
            else new_tight=0;
            sum+=mem(idx-1,new_tight,i,new_ld,s);
        }
    }
    dp[idx][prev][ld][tight]=sum;
    return sum;
}