/* Tarjan's Articulation Points Algorithm
 - Dado un grafo dirigido, encuentra sus puntos de articulacion.
 - La respuesta esta en el vector art_points, el cual puede contener
   elementos repetidos, por tanto hay que hacerle unique().
 - Tiempo: O(V+E). Memoria: O(V+E).
 - Tested on: CIIC 2002 Camino
**/

void tarjan_artpoints(int nod, int p=-1){
    dt[nod] = low[nod] = ++t;
    
    for(auto nwn: G[nod]){
        if( !dt[nwn] ){
            tarjan_artpoints(nwn, nod);
            chmin(low[nod], low[nwn]);
            
            if( (dt[nod] == 1 && dt[nwn] > 2) || 
                    (dt[nod] > 1 && dt[nod] <= low[nwn]) )
                art_points.pb(nod);
        }
        else if( nwn != p )
            chmin(low[nod], dt[nwn]);
    }
}
