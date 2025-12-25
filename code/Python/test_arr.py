import random

with open("in.txt", 'w') as f:
    n = random.randint(1,100000)
    f.write(str(n)+'\n')
    for i in range(n):
        f.write(str(random.randint(1,100))+' ')