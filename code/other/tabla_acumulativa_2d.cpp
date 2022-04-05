struct tabla_2d{
    int n,m;

    int A[maxn][maxm];
    int T[maxn][maxm];

    void build (){
        for ( int i = 1; i <= n; i++ ){
            for ( int j = 1; j <= m; j++ ){
                if ( i == 1 || j == 1 )
                    T[i][j] = A[i][j] + T[i-1][j] + T[i][j-1];
                else
                    T[i][j] = T[i][j-1] + 
                        T[i-1][j] - T[i-1][j-1] + A[i][j];
          }
        }
    }

    int query ( int x1, int y1, int x2, int y2 ){
        return T[x2][y2] - T[x2][y1-1]
            - T[x1-1][y2] + T[x1-1][y1-1];
    }
};
