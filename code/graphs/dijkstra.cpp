/* Algoritmo de Dijkstra 
 - Dado un grafo con ARISTAS NO NEGATIVAS, retorna un vector con las
   distancias minimas desde el nodo inicial hasta todos los nodos.
 - MIEMBROS DE EDGE: nwn, cost, comparador greater.
 - Tiempo: O(V + E * log(E) ).
 - Tested on: https://codeforces.com/contest/20/problem/C
**/
typedef int64 dtype;      // Tipo de datos de la distancia
const dtype inf = INF64;   // Infinito del tipo dtype

struct edge{
    int nwn;
    dtype cost;
    
    bool operator < (const edge& p)const{
        return cost > p.cost;
    }
};

vector<dtype> dijkstra(int cn, int ni, vector<edge> G[]){
    priority_queue<edge> Q;
    vector<dtype> dist(cn + 1, inf);
    dist[ni] = 0;
    
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
    return dist;
}
