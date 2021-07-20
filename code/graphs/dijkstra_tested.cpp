/* Algoritmo de Dijkstra:
 - Calcula el camino mas corto desde un nodo a todos los otros 
 - Guarda los resultados en dist 
 - Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=1659
**/
void dijkstra(int ni, int* dist){
    for(Q.push({ni, 0}); !Q.empty(); ){
        int nod = Q.top().nwn;
         
        if( dist[nod] < Q.top().cost ){ 
            Q.pop();
            continue;
        }
        Q.pop();
        
        for(auto i: G[nod]){
            if( dist[i.nwn] > dist[nod] + i.cost ){
                dist[i.nwn] = dist[nod] + i.cost;
                Q.push({i.nwn, dist[i.nwn]});
            }
        }
    }
}
