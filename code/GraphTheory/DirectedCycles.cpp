int n; // number of vertices
vector<vector<int>> adj(MAX);
stack<int> st;
vector<bool> visited(MAX);
vector<bool> stFlg(MAX);
vector<int> arns;
int depth = 0;
 
bool dfs(int v) {
    visited[v] = true;
    st.push(v);
    stFlg[v] = true;
    for(auto &z : adj[v]){
        if(!visited[z])
            if(dfs(z)) return true;
        
        if(stFlg[z]){
            st.push(z);
            return true;
        }
    }
 
    st.pop();
    stFlg[v] = false;
    return false;
}
 
void printCycle(){
	int tmp = st.top();
	while(!st.empty()){
		arns.push_back(st.top());
		st.pop();
		if(arns.back() == tmp and arns.size() != 1) break;
	}
	reverse(arns.begin(), arns.end());
 
	cout<<arns.size()<<endl;
	for(auto v: arns) cout<<v<<" ";
	cout<<endl;
}
