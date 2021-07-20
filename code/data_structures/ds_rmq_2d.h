/* Range Min/Max Query en Dos Dimensiones
 - Esta es la version de maximo.
 - Recibe una matriz de N x M (1-indexed).
 - Parar la query se define un rectangulo cuya esquina superior
   izquierda es (a, b) y su esquina inferior derecha es (c, d).
   
   o--a--o
   |     |
   b     d
   |     |
   o--c--o

 - Tiempo: Build: O(N * M * lg N * lg M). Query: O(1).
 - Tested on: https://codeforces.com/contest/1301/problem/E
*/

#define lg(X) (31 - __builtin_clz(X))

struct rmq_2d{
    int A[MX][10][MX][10];
    
    rmq_2d(){}
    rmq_2d(int N, int M, int a[][MX]){
        for(int i=1; i<=N; i++)
            for(int ii=1; ii<=M; ii++)
                A[i][0][ii][0] = a[i][ii];
                
        for(int i=1; i<=N; i++)
            for(int jj=1; (1<<jj)<=M; jj++) 
                for(int ii=1; ii+(1<<jj)-1<=M; ii++)
                    A[i][0][ii][jj] = max(
                        A[i][0][ii][jj-1], 
                        A[i][0][ii+(1<<(jj-1))][jj-1]
                    );
        
        for(int j=1; (1<<j)<=N; j++) 
            for(int i=1; i+(1<<j)-1<=N; i++)
                for(int jj=0; (1<<jj)<=M; jj++) 
                    for(int ii=1; ii+(1<<jj)-1<=M; ii++)
                        A[i][j][ii][jj] = max(
                            A[i][j-1][ii][jj],
                            A[i+(1<<(j-1))][j-1][ii][jj]
                        );
    }
    
    int query(int a, int b, int c, int d){
        if( a > c || b > d )
            return -INF;
        int ln = lg(c-a+1), lm = lg(d-b+1);
        
        return max({
            A[a][ln][b][lm],
            A[c-(1<<ln)+1][ln][b][lm],
            A[a][ln][d-(1<<lm)+1][lm],
            A[c-(1<<ln)+1][ln][d-(1<<lm)+1][lm]
        });
    }
};
