/* Longest Increasing Subsequence
 - El metodo devuelve una subsecuencia incremental mas larga
   del arreglo A[1..N].
 - Para hallar una subsecuencia no decreciente mas larga, cambiar
   mp(A[i], -1) por mp(A[i], INF) en la linea del lower_bound.
 - Para calcular las subsecuencias decrementales y no crecientes 
   mas largas, invertir el arreglo A[1..N].
 - Tiempo: O(n lg k), donde k es el largo del LIS. 
 - Memoria: O(n). 
OJO: El arreglo L, NO es el LIS.
**/
vector<int> lis(int N, int* A){
    int last[MX];
    vector<pair<int, int>> L;
    
     for(int i=1, p; i<=N; i++){
        p = lower_bound(all(L), mp(A[i], -1)) - L.begin();
        
        if( p == (int)L.size() )
            L.pb({A[i], i});
        else 
            L[p] = {A[i], i};
        last[i] = (p == 0) ? -1 : L[p-1].sc;
    }

    vector<int> ans;
    for(int i=L.back().sc; ~i; i=last[i])
        ans.pb(A[i]);
    reverse(all(ans));
    
    return ans;
}
