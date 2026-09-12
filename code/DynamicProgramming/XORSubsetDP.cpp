for(int dim=0;dim<MAXDIM;dim++)
{
    for(int i=0;i<n;i++)
    {
        if(i&(1<<dim)){
            F[i]^=F[i^(1<<dim)];
        }
    }
}
FO(i,n){
    cout<<F[i]<<" ";
}