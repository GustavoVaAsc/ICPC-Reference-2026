k = int(input())
S = [int(x) for x in input().split()]
subsets = [[S[j] for j in range(k) if (i >> j) & 1] for i in range(1 << k)]
print(subsets)