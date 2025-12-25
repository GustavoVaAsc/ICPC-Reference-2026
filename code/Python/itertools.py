import itertools

a = [1,2,3,4]
b = [5,6,7,8]

# All 2 digit numbers composed of digits 1,2,3
# Cartesian product
for a, b in itertools.product('123', repeat=2):
    print(a+b)

# All k-subsets (combinations)
for team in itertools.combinations(['A','B','C','D','E'],3):
    print(team)

# Subsets with repetitions (combinations_with_replacement)
# All ways to choose 3 balls from 2 colours where each colour can be used any number of times
for bag in itertools.combinations_with_replacement(['red','blue'],3):
    print(bag)

# All ways to order 3 letters O(n!)
for order in itertools.permutations('abc'):
    print(''.join(order))

# Prefix XOR
pref_xor = list(itertools.accumulate(a, func=lambda x,y : x^y))

# Group consecutive equal keys

s = "AAABBBCCDA"
for key, group in itertools.groupby(s):
    print(key, list(group))
# A ['A','A','A']
# B ['B','B','B']
# C ['C','C']
# D ['D']
# A ['A']

