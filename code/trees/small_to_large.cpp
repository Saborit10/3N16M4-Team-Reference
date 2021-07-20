/*  Small to Large
 - vec[nod] es un arreglo de vectores que contiene todos los nodos del
   subarbol de nod CUANDO EL DFS ESTA VISITANDO SU SUBARBOL. 
 - sz[nod] es la cantidad de nodos en el subarbol de nod.
 - Las funciones inc() y dec() representan cambios a la estructura 
   auxiliar que mantiene valores necesarios para calcular la propiedad
   que se pide, cuando el dfs esta en un nodo especifico.
 - big es el indice del hijo de nod, con subarbol mas grande (hijo 
   heavy). msz es el sz de ese hijo.
 - keep es true si estamos en el subarbol de un hijo heavy. De no ser 
   asi, se borra el contenido correspondiente al nodo, de nuestra 
   estructura auxiliar.
 - Tiempo: O(n log n) * [operacion en estructura auxiliar]
 - Tested on: https://codeforces.com/contest/600/porblem/E   
**/
void dfs(int nod, int p, int keep){
    int big = -1, msz = -1;
    
    for(auto nwn: G[nod]) if( nwn != p ){
        if( msz < sz[nwn] ){
            msz = sz[nwn];
            big = nwn;
        }    
    }
    
    for(auto nwn: G[nod]) if( nwn != p && nwn != big )
        dfs(nwn, nod, 0);
    if( ~big ){
        dfs(big, nod, 1);
        swap(vec[big], vec[nod]);
    }
    
    vec[nod].pb(nod);
    inc(nod);
    
    for(auto nwn: G[nod]) if( nwn != p && nwn != big ){
        for(auto i: vec[nwn]){
            vec[nod].pb(i);
            inc(i);    
        }
    }
    
    //aqui la estructura contiene la respuesta para el vertice nod. 
    
    if( !keep ){
        for(auto i: vec[nod])
            dec(i);
    }
}
