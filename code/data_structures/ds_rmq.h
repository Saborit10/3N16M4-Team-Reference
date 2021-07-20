/* Range Min-Max Query
 - build(N, A): construye una sparse table para el arreglo A[1..N] en 
   O(n lg n).
 - query(a, b): responde el minimo en el subarreglo A[a..b] en O(lg n)
 - Memoria: O(n lg n).
 - Solution for: COCI 2013-2014 slasticar
**/
struct rmq{
    int T[MX][20];
    
    void build(int N, int* A){
        for(int i=1; i<=N; i++)
            T[i][0] = A[i];
            
        for(int j=0; j < log2(N); j++){
            N -= (1<<j);
            for(int i=1; i<=N; i++)
                T[i][j+1] = min(T[i][j], T[i + (1<<j)][j]);
        }
    }
    
    int query(int a, int b){
        int l = log2(b-a+1);
        return min(T[a][l], T[b - (1<<l) + 1][l]);
    }
};

