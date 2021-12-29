/* Longest Increasing Subsequence
 - El metodo devuelve una subsecuencia incremental mas larga
   del arreglo A[1..N].
 - strict es true si se quiere hallar la subsecuencia mas larga
   estrictamente creciente. Si se quiere hallar la no decreciente,
   poner strict false.
 - Para calcular las subsecuencias decrementales y no crecientes 
   mas largas, invertir el arreglo A[1..N].
 - Tiempo: O(n lg k), donde k es el largo del LIS. 
 - Memoria: O(n). 
OJO: El arreglo L, NO es el LIS.
**/
vector<int> lis(int n, int* A, bool strict){
    vector<int> last(n+1);
    vector<pair<int, int>> L;
    
    for(int i=1, p; i<=n; i++){
        pii x = mp(A[i], strict ? -1 : INF);
        p = lower_bound(all(L), x) - L.begin();
        
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
