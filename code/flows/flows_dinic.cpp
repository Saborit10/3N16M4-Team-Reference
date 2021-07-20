/* Algoritmo de Dinic
 - Uso: Crear un objeto dinic proporcionando cantidad de nodos, fuente
   y sumidero. Agregar las aristas correspondientes. La respuesta al 
   flujo maximo la devuelve el metodo throw_folw()
 - Tiempo: O(V^2*E) para grafos generales y para redes de capacidad 
   unitaria es O( min(V^(2/3), sqrt(E)) * E).    
 - Memoria: O(V + E).
 - Para esquivar casos de prueba que pueden dar TLE, se debe barajar 
   las aristas antes de agregarlas al grafo. Para esto, si el vector 
   de aristas se llama E, usar random_shufle(all(E)).
 OJO: la funcion add_edge agrega solo aristas dirigidas.   
 - Tested on: USACO 2007 Open Dining
**/
#define nn G[i].nwn
#define ct G[i].cost

struct par{
    int nwn, cost;
};

struct dinic{
    int cn, ca, ni, nf;
    int64 f, mf;
    int L[MX], F[MX], T[2 * MX];
    par G[2 * MX];
    queue<int> Q;
    
    dinic(int cn, int ni, int nf): cn(cn), ca(0), ni(ni), nf(nf){
        for(int i=0; i<=cn; i++)
            F[i] = -1;
        mf = 0;
    }
    
    void add_edge(int a, int b, int c=1){
        G[ca] = {b, c};
        T[ca] = F[a], F[a] = ca++;
        
        G[ca] = {a, 0};
        T[ca] = F[b], F[b] = ca++;
    }
    
    bool bfs(){
        fill(L, L+cn+1, -1); L[ni] = 0;
        
        for(Q.push(ni); !Q.empty(); Q.pop()){
            int nod = Q.front();
            
            for(int i=F[nod]; ~i; i=T[i]){
                if( ct > 0 && L[nn] < 0 ){
                    L[nn] = L[nod] + 1;
                    Q.push(nn);
                }
            }
        }
        return ~L[nf];
    }
    
    int dfs(int nod, int flow){
        if( nod == nf ) return flow;
        
        for(int i=F[nod]; ~i; i=T[i]){
            if( ct > 0 && L[nn] > L[nod] ){
                int ans = dfs(nn, min(flow, ct));
                
                if( ans > 0 ){
                    G[i].cost -= ans, G[i^1].cost += ans;
                    return ans;
                }
            }
        }
        return 0;
    }
    
    int64 throw_flow(){
        while( bfs() )
            while( (f = dfs(ni, INF)) )
                mf += f;
        return mf;
    }
};
