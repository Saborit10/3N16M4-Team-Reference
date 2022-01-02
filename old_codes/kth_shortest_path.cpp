/* K-esimo Camino Minimo 
 - Imprime los K caminos mas cortos en un grafo con pesos positivos. 
 - O(K*E logE)
 - Tested on: cowjog USACO 2008 Marzo
**/
void kth_path(int ni, int nf){
    int k = 1;
    for(Q.push({ni, 0}); !Q.empty(); Q.pop()){
        int nod = Q.top().nwn;
        int64 cost = Q.top().cost;
        
        cant[nod]++;
        if( nod == nf ){
            printf("%lld\n", cost);
            k++;
            
            if( cant[nod] == K )
                break;
            else continue;    
        }
        
        for(auto i: G[nod]) if( cant[i.nwn] <= K )
            Q.push({i.nwn, cost + i.cost});
    }
    for(; k<=K; k++) printf("-1\n");
}
