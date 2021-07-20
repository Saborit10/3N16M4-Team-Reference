/* Tree into Array
 - Tiempo: O(E).
 - Tested on: promote USACO 2017 January Paltinum
**/
struct graph{
    int cn, N;
    int A[MX], T[2*MX], L[MX], R[MX];
    vector<int> G[MX];
    
    graph():{}
    
    void add_edge(int a, int b){
        G[a].pb(b);
        G[b].pb(a);
    }   
    
    void dfs(int nod, int p){
        T[++N] = A[nod];
        L[nod] = N;
        
        for(auto nwn: G[nod]) if( nwn != p )
            dfs(nwn, nod);    
        
        T[++N] = A[nod];
        R[nod] = N;
    }
    
    void build(){
        dfs(1, -1);
    }
};
