/* Algoritmo de Kosaraju
 - Preferible cuando hacen falta las componentes fuertemente conexas
   en orden topologico, o cuando se necesita el grafo traspuesto para
   otra cosa.
 - Encuentra todos los ciclos de largo 2 o mas.
 - Se necesita cinstruir el grafo traspuesto T.
 - El metodo kosaraju() devuelve un vector con los nodos 
   identificadores de cada componente, en orden topologico. El 
   arreglo SET guarda, para cada nodo, el nodo identificador de su
   componente.
 - Tiempo: O(V+E). Memo: O(E).
 - Tested on: COCI 2006-2007 Contest 3: BICIKLI
OJO: si se usa el nodo cero como dummy, hay que inicializar el arreglo 
   SET[1..cn] a -1.
**/

int SET[MX];
bool mk[MX];
vector<int> T[MX];
stack<int> K;

void tsort(int nod){
    mk[nod] = true;
    for(auto nwn: G[nod]) if( !mk[nwn] )
        tsort(nwn);
    K.push(nod);
}

void flood(int nod, int x){
    SET[nod] = x;
    for(auto nwn: T[nod]) if( !SET[nwn] )
        flood(nwn, x);
}

vector<int> kosaraju(){
    vector<int> ans;
    
    for(int i=1; i<=cn; i++) if( !mk[i] )
        tsort(i);
    
    for(; !K.empty(); K.pop()) if( !SET[K.top()] ){
        ans.pb(K.top());
        flood(K.top(), K.top());
    }
    return ans;
}
