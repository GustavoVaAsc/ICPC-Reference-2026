import random
n,m = [int(x) for x in input().split()]

class Edge:
    def __init__(self, u:int, v:int):
        self.u = u
        self.v = v

    def __eq__(self, o):
        return o.u == self.u and o.v == self.v

    def __hash__(self):
        return hash((self.u, self.v))


with open("in.txt",'w') as f:
    if m != n-1:
        f.write(str(n)+" "+str(m)+'\n')
    else:
        f.write(str(n)+'\n')
    edges = set()
    for i in range(m):
        u,v = [0,0]
        while u == v or Edge(u,v) in edges:
            u = random.randint(1,n)
            v = random.randint(1,n)
        edges.add(Edge(u,v))
        f.write(str(u)+" "+str(v)+"\n")
    print(edges)