/* Tabla Acumulativa
 - Se define el rectangulo dentro de una matriz, 
   de la forma:
  
   o--c--o
   |     |
   a     b
   |     |
   o--d--o  
**/
 
struct accumulative{
    int N;
    int A[MX][MX], dp[MX][MX];
    
    void build(){
        for(int i=1; i<=N; i++) for(int j=1; j<=N; j++){
            dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
            dp[i][j] += A[i][j] > 0;
        }
    }
    
    int query(int a, int b, int c, int d){
        return dp[d][b] - dp[c-1][b] - dp[d][a-1] + dp[c-1][a-1];   
    }    
};
