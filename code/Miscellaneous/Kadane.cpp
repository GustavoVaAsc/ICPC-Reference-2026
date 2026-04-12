ll kadane(vector<int> &a, int n){
    ll arns = a[0], zum = 0;
 
    for (int i = 0; i < n; i++){
        zum += a[i];
        arns = max(arns, zum);
        zum = max(zum, 0LL);
    }
 
    return arns;
}
