/* Tarjan's Bridge Algorithm
 - El metodo bridge_tree toma la cantidad de nodos y una lista de
   adyacencia y devuelve un arbol B que contiene todos los
   bridges del grafo. Las componentes que no contienen bridges
   estan condensadas en los nodos dle arbol.
 - Las aristas del arbol, aunque pueden cambiar los nodos entre los
   que se encuentran (pasando a estar ahora entre los dos
   identificadores de los nodos condensados correspondientes),
   conservan los demas campos de la clase edge.
 - Al finalizar el metodo, el arreglo SET contiene, para cada nodo
   en G, el vertice condensado al que pertenece en B.
 - La clase edge debe tener un atributo nwn.
 - Tiempo: O(V+E) . Memoria: O(E).
 - Tested: https://codeforces.com/problemset/problem/652/E
**/
struct tarjan_bridges{
    int cn, t;
    vector<edge>* G;
    vector<int> dt, low, SET;
    stack<int> K;
    
    tarjan_bridges(int cn, vector<edge> G[]) : cn(cn), t(0), G(G){
        dt = low = SET = vector<int>(cn + 1);
    }
    
    void tarjan(int nod, int p){
        dt[nod] = low[nod] = ++t;
        K.push(nod);
        
        for(auto i: G[nod]){
            if( !dt[i.nwn] ){
                tarjan(i.nwn, nod);
                chmin(low[nod], low[i.nwn]);
                
                if( dt[nod] < low[i.nwn] ){
                    while( true ){
                        int x = K.top(); K.pop();
                        SET[x] = i.nwn;
                        if( x == i.nwn ) break;
                    }
                }
            }
            else if( i.nwn != p )
                chmin(low[nod], dt[i.nwn]);
        }
    }
    
    vector<edge>* bridge_tree(){
        for(int i=1; i<=cn; i++) if( !dt[i] ){
            tarjan(i, -1);
            
            while( !K.empty() ){
                SET[K.top()] = i;
                K.pop();
            }
        }
        
        vector<edge> *ans = new vector<edge>[cn + 1];
        
        for(int nod=1; nod<=cn; nod++) for(auto i: G[nod]){
            if( SET[nod] != SET[i.nwn] ){
                ans[ SET[nod] ].pb(i);
                ans[ SET[nod] ].back().nwn = SET[i.nwn];
            }
        }
        
        return ans;
    }
};
