/* Algoritmo de Kosaraju
 - Preferible cuando hacen falta las componentes fuertemente conexas
   en orden topologico, o cuando se necesita el grafo traspuesto para
   otra cosa.
 - Encuentra todos los ciclos de largo 2 o mas.
 - El metodo scc_order() devuelve un vector con los nodos
   identificadores de cada componente, en orden topologico. El
   arreglo SET guarda, para cada nodo, el nodo identificador de su
   componente.
 - Tiempo: O(V+E). Memo: O(E).
 - Tested on: http://codeforces/contest/1608/problem/C
**/
struct kosaraju{
    int cn;
    vector<int> SET, K, *G;
    vector<bool> mk;
    vector<vector<int>> T;

    kosaraju(int cn, vector<int> G[]): cn(cn), G(G){
        SET = vector<int>(cn+1);
        mk = vector<bool>(cn+1);
        T = vector<vector<int>>(cn+1);

        for(int u=0; u<=cn; u++) for(auto v: G[u])
            T[v].pb(u);
    }

    void tsort(int nod){
        mk[nod] = true;
        for(auto nwn: G[nod]) if( !mk[nwn] )
            tsort(nwn);
        K.pb(nod);
    }

    void flood(int nod, int x){
        SET[nod] = x;
        for(auto nwn: T[nod]) if( !SET[nwn] )
            flood(nwn, x);
    }

    vector<int> scc_order(){
        vector<int> ans;

        for(int i=1; i<=cn; i++) if( !mk[i] )
            tsort(i);

        for(; !K.empty(); K.pop_back()) if( !SET[K.back()] ){
            ans.pb(K.back());
            flood(K.back(), K.back());
        }
        return ans;
    }
};
