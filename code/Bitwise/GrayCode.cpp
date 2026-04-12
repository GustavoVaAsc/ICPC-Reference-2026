vector<string> grayCode(int n){
    vector<string> arns;
    for(int i=0; i<(1<<n); i++){
	int g = i^(i>>1);
	bitset<32> r(g);
	string arnsito = r.to_string().substr(32-n, 32);
	arns.push_back(arnsito);
    }
    return arns;
}
