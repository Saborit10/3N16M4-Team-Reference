/* Algoritmo Bellman-Ford
 - Calcula los caminos minimos desde un nodo hacia otros, pudiendo 
   haber aristas de costo negativo. Detecta los ciclos de costo 
   negativo.
 - Tiempo: O(|V| * |E|)
 - Tested on: wormhole USACO Gold 2006 Dic
**/
for(int i=1; i<=cn; i++) 
    dist[i] = INF;     
dist[1] = 0;
     
for(int i=1; i < cn; i++)
    for(auto arc: G)
        if( dist[arc.nwn] > dist[arc.nod] + arc.cost )
            dist[arc.nwn] = dist[arc.nod] + arc.cost;
     
for(auto arc: G)
    if( dist[arc.nwn] > dist[arc.nod] + arc.cost )
        //HAY CICLOS NEGATIVOS
        
