# 1 to N 
nums = [i for i in range(1, N+1)] 

# Filter values
evens = [x for x in arr if x%2 == 0]

# Filter primes
primes = [x for x in arr if all(x%d for d in range(2,int(x**0.5)+1))]

# Square every element
sqr = [x*x for x in arr]

# Convert string digits to int
digits = [int(c) for c in s]

# Nested loops
pairs = [(i,j) for i in range(N) for j in range(M)]

# Generate NxM matrix
matrix = [[i*j for j in range(M)] for i in range(N)]

# Generate all combinations of two lists
combs = [(a,b) for a in list1 for b in list2]

# Prefix Zum
from itertools import accumulate
pref = list(accumulate(arr))

# Count occurences of a value (without count)
cnt = sum(1 for x in arr if x == target)