/* Kahn's Algorithm
 - delta guarda el grado de entrada de los nodos. Llenarlo en la 
   entrada.
 - Si el grafo contiene un ciclo devuelve un vector vacio. En caso
   contrario devuelve un orden topologico del grafo.
 - Si se usa una cola de prioridad el orden de los nodos es el 
   menor lexicograficamente. Para ello hacer
       queue_type = priority_queue<int, vector<int>, greater<int>>
       TOP(Q)     = (Q).top() 
 - Tiempo: O(V+E), Memoria: O(E).
 - Tested on: {Testear}.
*/
typedef queue<int> queue_type;
#define TOP(Q) (Q).front()

struct edge{ int nwn; };

vector<int> kahn(int cn, vector<edge> G[]){
    vector<int> ans, delta(cn + 1);
    vector<bool> off(cn + 1);
    queue_type Q;
    
    for(int i=1; i<=cn; i++) for(auto j: G[i])
        delta[ j.nwn ]++;
    
    for(int i=1; i<=cn; i++) if( !delta[i] )
        Q.push(i);

    while( !Q.empty() ){
        int nod = TOP(Q);
        Q.pop();
        ans.pb(nod);
        
        off[nod] = true;
        for(auto i: G[nod]){
            delta[i.nwn]--;
            
            if( !delta[i.nwn] && !off[i.nwn] )
                Q.push(i.nwn);    
        }
    }
    return len(ans) == cn ? ans : vector<int>();
}
