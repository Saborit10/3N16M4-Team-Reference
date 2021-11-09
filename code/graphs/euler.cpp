/* Euler Tour  
 - Un grafo conexo admite un ciclo euleriano ssi todos sus vertices 
   tienen grado par, especificamente un grafo dirigido debe tener en 
   cada nodo un grado de salida igual al grado de entrada.  
 - Un grafo conexo admite un camino euleriano ssi todos sus vertices 
   tienen grado par, excepto dos: el origen y el final del camino. 
   Especificamente, un grafo dirigido debe tener en cada nodo un
   grado de salida igual al grado de entrada, excepto el origen con
   el grado de salida mayor en uno, y el final con grado de entrada
   mayor en uno. 
 - El algoritmo se usa para hallar el ciclo euleriano. Si se desea
   hallar un camino euleriano, hay que colocar la arista faltante y
   luego borrarla del ciclo para obtener el camino.  
 - Complexity: O(E) 
 - Tested on: http://codeforces.com/contest/1511/problem/D
*/
struct edge{
    int nwn;
    bool mk;
};

vector<int> euler_tour(int ni, vector<edge> G[]){
    vector<int> sol;
    
    function<void(int)> dfs = [&](int nod){
        for(auto& i: G[nod]) if( !i.mk ){
            i.mk = true;
            dfs(i.nwn);
        }
        sol.pb(nod);
    };
    dfs(ni); return sol;
}
