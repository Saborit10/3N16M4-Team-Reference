/* Optimizacion de Knuth
 - opt[i][j] guarda el indide de k optimo para el estado (i, j)  
 - Debe cumplirse que opt[i][j-1] <= opt[i][j] <= opt[i+1][j]
 - Optimizacion: De O(n^3) a O(n^2) 
 - Tested on: https://uva.onlinejudge.org/external/100/10003.pdf
**/
 
for(int l=1; l<=N; l++){
    for(int i=1; i<=N-l+1; i++){
        int j = i + l -1;
        
        if( l <= 2 ){
            // Caso Base. Cambiar segun sea necesario.
            dp[i][j] = 0, opt[i][j] = i;
            continue;    
        }
        dp[i][j] = INF;
        
        pair<int, int> best = {INF, -1};
        for(int k=opt[i][j-1]; k<=opt[i+1][j]; k++)
            best = min(best, {dp[i][k] + dp[k][j], k});
            
        dp[i][j] = best.fr + cost(i, j);
        opt[i][j] = best.sc;        
    }    
}    
