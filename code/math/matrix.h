/* Matrix Work
 - pd(): multiplica dos matrices de numeros enteros.
 - min(): dadas dos matrices de adyacencia de caminos de largo k,
   Devuelve la matriz de los caminos optimos para caminos de largo
   2k. Para ello hay que modificar la funcion pot para que empiece
   con la matriz llena de ceros.
 - Tested on: https://codeforces.com/gym/102644/problem/C
 - Tested on: https://codeforces.com/gym/102644/problem/F
**/
typedef int type;
typedef vector<vector<type>> matrix;
const int64 BIG_MOD = 8ll * MOD * MOD;

matrix pd(matrix& a, matrix& b){
    int n = len(a), m = len(b[0]), l = len(b);
    matrix ans(len(a), vector<type>(m, 0));
    
    for(int i=0; i < n; i++) for(int j=0; j < m; j++){
        int64 tmp = 0;
        for(int k=0; k < l; k++){
            tmp += 1ll * a[i][k] * b[k][j];
            
            if( tmp >= BIG_MOD ) tmp -= BIG_MOD;
        }
        ans[i][j] = tmp % MOD;
    }
    return ans;
}

matrix pot(matrix& base, int64 e){
    matrix ans(len(base), vector<type>(len(base), 0));
    for(int i=0; i < len(base); i++) ans[i][i] = 1;
    
    while( e ){
        if( e & 1ll ) ans = pd(ans, base);
        base = pd(base, base);
        e >>= 1ll;
    }
    return ans;
}

matrix min(matrix& a, matrix& b){
    int n = len(a), m = len(b[0]), l = len(b);
    matrix ans(len(a), vector<type>(m, INF64));
    
    for(int i=0; i < n; i++) for(int j=0; j < m; j++){
        for(int k=0; k < l; k++)
            chmin(ans[i][j], a[i][k] + b[k][j]);
    }
    return ans;
}
