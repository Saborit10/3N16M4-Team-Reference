/* Algoritmo de Dijkstra 
 - Dado un grafo con ARISTAS NO NEGATIVAS, retorna las distancias
   minimas desde el nodo inicial hasta todos los nodos.
 - Para grafos dirigidos arreglar el metodo add_edge
 - Tiempo: O(V + E * log(E) ).
 - Tested on: https://codeforces.com/contest/20/problem/C
**/
typedef int dtype;            // Tipo de datos que representa la distancia
typedef pair<dtype, int> edge; 
const dtype inf = INF;            // Infinito del tipo de datos dtype

struct dijkstra{
    int cn;
    dtype dist[MX];
    vector<edge> G[MX];
    priority_queue<edge, vector<edge>, greater<edge>> Q;
    
    dijkstra(int cn): cn(cn){
        for(int i=0; i<=cn; i++)
            G[i].clear();
    }
    
    void add_edge(int a, int b, dtype c){
        G[a].pb({c, b});
        G[b].pb({c, a}); // Comentar esta linea si el grafo es dirigido
    }
    
    /* Operador [] para acceder a la lista de adyacencia */
    vector<edge>& operator[] (int v){ return G[v]; }
    
    vector<dtype> solve(int ni){
        fill(dist, dist+cn+1, inf); dist[ni] = 0; // Limpiando dist
        
        for(Q.push({0, ni}); !Q.empty(); ){
            int nod = Q.top().sc;
             
            if( dist[nod] < Q.top().fr ){ // Si la distancia minima del
                Q.pop();                  // nodo ya fue calculada, no
                continue;                 // se analiza  nuevamente
            }
            Q.pop();
            
            for(auto i: G[nod]){
                if( dist[i.sc] > dist[nod] + i.fr ){
                    dist[i.sc] = dist[nod] + i.fr;
                    Q.push({dist[i.sc], i.sc});
                }
            }
        }
        return vector<dtype>(dist, dist+cn+1); 
    }
};
