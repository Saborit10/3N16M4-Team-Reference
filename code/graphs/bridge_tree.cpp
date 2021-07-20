/* Bridge Tree
 - Dado un grafo no dirigido cuyos bridges estan marcados (i.bridge
   es verdadero ssi la arista i es un bridge), contruye el bridge
   tree de dicho grafo. 
 - Antes de llamar a este metodo, hay que llamar a tarjan_bridges()
   en cada componente conexa. 
 - bfs() retorna los nodos a los que esta conectada la componente del
   nodo ni a traves de bridges.
 - dfs() construye el arbol llamando a bfs() para encontrar a los
   "vecinos" del nodo actual.
 - Tiempo: O(V+E) . Memoria: O(V+E).
 - Tested: USACO Jan-06 Gold rpaths 
OJO: En cada componente conexa de debe llamar al metodo dfs() EN EL
   MISMO NODO DONDE LLAMAMOS AL METODO TARJAN_BRIDGES.
**/
vector<int> bfs(int ni){
    vector<int> ans;
    while( !Q.empty() ) Q.pop();
    
    for(Q.push(ni); !Q.empty(); Q.pop()){
        int nod = Q.front();
        
        for(auto i: G[nod]) if( !mk[i.nwn] ){
            if( i.bridge )
                ans.pb(i.nwn);
            else{ 
                mk[i.nwn] = true;
                Q.push(i.nwn);
            }
        }
    }
    return ans;
}

void dfs(int nod){
    mk[nod] = true;
    is_node[nod] = true;
    // nod es el id de la componente en el nuevo arbol
    
    auto vec = bfs(nod);
    
    for(auto nwn: vec) if( !mk[nwn] ){
        //Agregar la arista (nod, nwn) al bridge tree.
        dfs(nwn);
    }
}