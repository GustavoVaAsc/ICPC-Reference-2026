int prime[MAX_PRIMES];
int SPF[MAX_SIZE];
int et[MAX_SIZE];
int idx=0;


ll bin_pow(ll x,ll k){
    ll res=1;
    while(k){
        if(k&1){
            res=(res*x)%MOD;
        }
        x=(x*x%MOD);
        k/=2;
    }
    return res;
}

ll inv(ll x){ return bin_pow(x,MOD-2);}

void manipulated_seive(int N)
{
   
    for (int i=2; i<N ; i++)
    {
        
        if (SPF[i]==0)
        {
            prime[idx++]=i;
            SPF[i] = i;
            et[i]=i-1;
        }
        else{
            //et[i]=(SPF[i]-1)*et[i/SPF[i]];
        }
        for (int j=0;
             j < idx &&
             i*prime[j] < N && prime[j] <= SPF[i];
             j++)
        {
            

            if(prime[j]==SPF[i]){
                et[i*prime[j]]=prime[j]*et[i];
            }
            else{
                et[i*prime[j]]=(prime[j]-1)*et[i];
            }
            SPF[i*prime[j]] = prime[j] ;
        }
    }
}

// driver  program to test above function
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N,q; cin>>N>>q;
    //memset(isprime,1,sizeof(isprime));
    manipulated_seive(N+1);

    ll Q=inv(N-1);
    for(int i=0;i<q;i++){
        int x; cin>>x;
        ll P=(N-x)+et[x]-1;
        //cout<<et[x]<<endl;
        cout<<(P*Q)%MOD<<"\n";
    }
    return 0;
}