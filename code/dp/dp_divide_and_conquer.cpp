/* Divide and Conquer Optimization
 - Se aplica a recurrencias de la forma:
   f(i, j) = max{k<=j | f(i-1, k) + C(k, j)}
 - Requisito: opt[i][j] <= opt[i][j+1]
 - La funcion C(i, j) es una funcion de costo arbitraria.
 - La funcion compute(i, l, r, lk, rk) calcula la fila i de la 
   tabla de la funcion, en un rango [l, r] y buscando los indices 
   optimos entre lk y rk.
 - Para el maximo, si inicializa best a {-INF, -1} y se sustituye 
   min por max.
 - Casi siempre debe calcularse manualmente la primera fila de la tabla.
 - Optimizacion: De O(n^3) a O(n^2 lg n)
 - Tested on: [pegar link a Ceil and Gondolas]  
**/

int64 C(int i, int j);
 
void compute(int i, int l, int r, int lk, int rk){
    if( l > r ) return;
 
    int m = (l + r) >> 1;
    pair<int64, int> best = {INF, -1};
 
    for(int k=lk; k<=min(m, rk); k++)
        best = min(best, {dp[i-1][k] + C(k, m), k});
 
    dp[i][m] = best.fr;
 
    compute(i, l, m-1, lk, best.sc);
    compute(i, m+1, r, best.sc, rk);
}
