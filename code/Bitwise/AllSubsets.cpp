void minSumSubset(vector<int> &a, ll total_zum){
        int n = (int)a.size();
	ll min_diff = LLONG_MAX;
 
        for(int i=1; i<(1<< n); i++){
                ll zum = 0;
                for(int j=0; j<n; j++){
                        if((i & (1<<j)) != 0){
                                zum+=a[j];
                        }
                }
		ll diff = abs(total_zum - 2LL * zum);
                min_diff = min(diff,min_diff);
        }
 
}