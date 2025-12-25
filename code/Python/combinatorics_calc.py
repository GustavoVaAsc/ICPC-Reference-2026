a,b = [int(x) for x in input.split()]

MAX = 1000001
MOD = 1000000007

fact = [0] * MAX
i_fact = [0] * MAX

def inv(x : int):
    return pow(x, MOD-2,MOD)

def factorial():
    fact[0] = fact[1] = 1
    for i in range(2,MAX):
        fact[i] = (fact[i-1] * i) % MOD
    i_fact[MAX-1] = inv(fact[MAX-1])
    for i in range(MAX-2, 0, -1):
        i_fact[i] = (i_fact[i+1]*(i+1))%MOD

def comb(n : int, k: int):
    return fact[n] * i_fact[n-k]%MOD * i_fact[k] % MOD

factorial()
print(comb(a,b))