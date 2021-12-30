/* Shortest Path Faster Algorithm + Small-Label-First Optimization
 - Simple SPFA, excepto que al meter un nodo en la cola, 
   si la distancia del frente de la cola es mayor que la 
   de este nodo, en lugar de meterlo detras lo colocamos de primero  
 - dist guarda la distancia minima, in cuenta la cantidad de veces 
   que un nodo ha entrado o salido de la deque Q. Si un nodo no es
   insertado en la cola, pq ya estaba  dentro, se cuenta como si 
   hubiese entrado y salido.
 - La funcion spfa devuelve un vector vacio si desde el nodo (ni)
   se puede llegar a un ciclo negativo.
 - Expected Time: O(E)  
 - Tested on: {Testear} USACO 2010-2011 Enero roadplane
**/
typedef int64 dtype;
const dtype inf = INF64;

struct edge{
    int nwn;
    dtype cost;
    
    bool operator < (const edge& p)const{
        return cost < p.cost;
    }
};

struct spfa{
    int cn;
    vector<int> in;
    vector<dtype> dist;
    deque<int> Q;
    
    spfa(int cn): cn(cn){}
    
    void push(int nod){
        if( in[nod] & 1 ) in[nod] += 2;
        else{
            if( dist[nod] < dist[Q.front()] )
                Q.push_front(nod);
            else 
                Q.push_back(nod);
            in[nod]++;
        }   
    }
    
    bool pop(){
        int nod = Q.front();
        in[nod]++; Q.pop_front();
        return in[nod] > 2 * cn;
    }
    
    vector<dtype> apply(int ni, vector<edge> G[]){
        dist = vector<dtype>(cn + 1, inf);
        in = vector<int>(cn + 1);
    
        dist[ni] = 0;
        for(push(ni); !Q.empty(); ){
            int nod = Q.front();
            
            if( pop() ) return {};
            
            for(auto i: G[nod]){
                if( dist[i.nwn] > dist[nod] + i.cost ){
                    dist[i.nwn] = dist[nod] + i.cost;
                    push(i.nwn);
                }
            }
        }
        return dist;   
    }
};
