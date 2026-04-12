def kahnTopoSort(self,adj: List[List[int]]) -> List[int]:
        #print(adj)
        in_deg = [0] * len(adj)
        for i in range(len(adj)):
            for u in adj[i]:
                in_deg[u]+=1
        
        q = []
        for i in range(len(in_deg)):
            if in_deg[i] == 0:
                q.append(i)

        arns = []
        while len(q)>0:
            u = q[0]
            q.pop(0)
            arns.append(u)

            for v in adj[u]:
                in_deg[v]-=1
                if in_deg[v] == 0:
                    q.append(v)

        print(str(len(arns))+" "+str(len(adj)))
        if(len(arns) != len(adj)): 
            return []

        return arns