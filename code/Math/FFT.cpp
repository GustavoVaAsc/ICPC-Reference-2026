// MAX should be a power of 2 and >= 2*10^5
// FFT works with sizes that are powers of 2
// 2^18 = 262144 > 200000
const int MAX = pow(2,18); 
 
typedef complex<double> cd;
double PI = acos(-1);
 
// My favorite black box <3
vector<cd> fft(vector<cd> a, int d = 1) {
    int n = a.size();
    vector<cd> r(n);
 
    for (int k = 0; k < n; k++) {
        int b = 0;
        for (int z = 1; z < n; z *= 2) {
            b *= 2;
            if (k & z)
                b++;
        }
        r[b] = a[k];
    }
 
    for (int m = 2; m <= n; m *= 2) {
        cd wm = exp(cd{0, d * 2 * PI / m});
 
        for (int k = 0; k < n; k += m) {
            cd w = 1;
            for (int j = 0; j < m / 2; j++) {
                cd u = r[k + j];
                cd t = w * r[k + j + m / 2];
                r[k + j] = u + t;
                r[k + j + m / 2] = u - t;
                w = w * wm;
            }
        }
    }
 
    if (d == -1) {
        for (int i = 0; i < n; i++)
            r[i] /= n;
    }
 
    return r;
}
 
void solve() {
    int n, m;
    cin>>n>>m;
 
    vector<int> s(n), msk(m);
 
    for(int i = 0; i < n; i++){
        cin >> s[i];
    }
    for(int i = 0; i < m; i++){
        cin >> msk[i];
    }
 
    reverse(msk.begin(), msk.end());
 
    vector<cd> a(2*MAX,cd(0,0)), b(2*MAX,cd(0,0));
    
    for(int i=0; i<n; i++){
        a[i]+=cd(s[i],0);
    }
    
    
    for(int i=0; i<m; i++){
        b[i]+=cd(msk[i],0);
    }
    
    auto A = fft(a);
    auto B = fft(b);
    vector<cd> C(2*MAX);
 
    for(int i = 0; i < 2*MAX; i++){
        C[i] = A[i] * B[i];
    }
 
    auto conv = fft(C, -1);
    
    for(int i = 0; i < n+m-1; i++){
        cout << (ll)round(conv[i].real()) << " ";
    }
    cout << endl;
}
