const ll MOD = 1e9+7;
 
// MAX should be a power of 2 and >= 2*10^5
// FFT works with sizes that are powers of 2
// 2^18 = 262144 > 200000
const int MAX = 1 << 20; 
 
typedef complex<double> cd;
double PI = acos(-1);
 
// Transformada de Wicho Cachondo
vector<ll> fwht(vector<ll> a, int d = 1) {
    int n = a.size();
    vector<ll> r = a;
 
 
    for (int m = 2; m <= n; m *= 2) {
        for (int k = 0; k < n; k += m) {
            for (int j = 0; j < m / 2; j++) {
                ll u = r[k + j];
                ll t = r[k + j + m / 2];
                
		r[k + j] = u + t;
                r[k + j + m / 2] = u - t;
            }
        }
    }
 
    if (d == -1) {
        for (int i = 0; i < n; i++)
            r[i] /= n;
    }
 
    return r;
}
