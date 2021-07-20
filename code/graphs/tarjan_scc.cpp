/* Tarjan's SCC Algorithm
 - Halla los ciclos de tamanno 3 o mayor en un DAG.
 - mk guarda si el nodo esta actualmente en la componente 
   fuertemente conexa. El dt de un nodo solo actualiza a otro si 
   esta dentro de la pila.  
 - Tiempo: O(V+E). Memoria: O(E).
**/ 

void tarjan_scc(int nod){
    dt[nod] = low[nod] = ++t;
    K.push(nod);
    mk[nod] = true;
    
    for(auto nwn: G[nod]){
        if( !dt[nwn] ){
            tarjan_scc(nwn);
            low[nod] = min(low[nod], low[nwn]); 
        }   
        else if( mk[nwn] )
            low[nod] = min(low[nod], dt[nwn]);
    }
    if( dt[nod] == low[nod] ){
        while( K.top() != nod ){
            SET[K.top()] = nod;
            mk[K.top()] = false;
            K.pop();
        }
        SET[K.top()] = nod;
        mk[K.top()] = false;
        K.pop();
    }
}
