/* Matrix Work
 - mult() multiplica dos matrices
 - pot() eleva la matriz al exponente e 
 - Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=2542 
**/

typedef vector< vector<int64> > matrix; 

/* Multiplica dos matrices */
matrix mult(matrix& a, matrix& b){
    matrix ans(a.size(), vector<int64>(b[0].size(), 0) );
    
    for(int i=0; i < (int)a.size(); i++) 
        for(int j=0; j < (int)b[0].size(); j++)
            for(int k=0; k < (int)b.size(); k++)
                ans[i][j] = (ans[i][j] + 
                    a[i][k] * b[k][j] % MOD ) % MOD;
    return ans;             
}

/* Eleva una matriz al exponente e */
matrix pot(matrix& base, int64 e){
     matrix ans(base.size(), vector<int64>(base.size(), 0));
     
     for(int i=0; i < (int)base.size(); i++) ans[i][i] = 1;
     
     while( e ){
        if( e & 1ll ) ans = mult(ans, base);
        base = mult(base, base);
        e >>= 1ll;     
     } 
     return ans;  
} 
