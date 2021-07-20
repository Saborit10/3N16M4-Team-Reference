/* Kosaraju's Algorithm
 - Recibe la cantidad de nodos y el arreglo de vectores que 
   representa al grafo.
 - Devuelve un vertor de vectores en los que cada vector es una 
   componente fuertemente conexa. Las SCC estan en orden topologico.  
 - Tested on: cowngress USACO Enero 2011
**/

vector<vector<int>> kosaraju(int cn, vector<int> G[]){
    bool mk[MX];
    vector<int> T[MX];
    vector<vector<int>> scc;
    stack<int> K;
        
    function<void(int, int)> dfs = [&](int nod, int pass){
        mk[nod] = !pass;
        
        if( pass ) scc.back().pb(nod);
        
        vector<int> adj = !pass ? G[nod] : T[nod];
        
        for(auto nwn: adj) if( (!mk[nwn]) ^ pass )
            dfs(nwn, pass);
        
        if( !pass ) K.push(nod);        
    };
        
    for(int i=1; i<=cn; i++){
        mk[i] = 0;
        for(auto j: G[i]) T[j].pb(i);
    }
    
    for(int i=1; i<=cn; i++) if( !mk[i] )
        dfs(i, 0);
        
    for(; !K.empty(); K.pop()) if( mk[K.top()] ){
        scc.pb({});
        dfs(K.top(), 1);
    }
    return scc;    
}        
