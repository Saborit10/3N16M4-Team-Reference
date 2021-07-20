/* Tarjan's Bridge Algorithm
 - Halla los bridges de un grafo no dirigido y los marca.
 - Tiempo: O(V+E) . Memoria: O(E).
 - Tested: USACO Jan-06 Gold rpaths 
**/

struct par{
    int nwn;
    bool bridge;
};

void tarjan_bridges(int nod, int p=-1){
    dt[nod] = low[nod] = ++t;
    
    for(auto& i: G[nod]){
        if( !dt[i.nwn] ){
            tarjan_bridges(i.nwn, nod);
            chmin(low[nod], low[i.nwn]);
            
            if( dt[nod] < low[i.nwn] )
                i.bridge = true;
        }
        else if( i.nwn != p )
            chmin(low[nod], dt[i.nwn]);
    }
}
