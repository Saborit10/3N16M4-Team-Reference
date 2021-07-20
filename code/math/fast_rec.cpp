/* Resuelve la ecuacion recursiva lineal: 
 - f(i) = c_k * f(i-K) + c_(k-1) * f(i-(k-1)) + ... + c_1 * f(i-1) + d 
 - El metodo toma un entero n y un vector de tamanho K+1, cuyos 
   indices [0...k-1] son los valores iniciales f(1), f(2), ..., f(K) 
   y en la posicion k esta la constante d.
 - Tambien toma el vector con los multiplicadores. En las posiciones 
   [0..k-1] estan c_k, c_(k-1), ..., c_1 
 - Devuelve un vector con los valores [f(n), f(n+1), ..., f(n+K-1)] 
 - Los resultados son modulo MOD y usa las funciones mult() y pot() 
   de trabajo con matrices.
 - Tiempo: n^3 * log k
 - Tested on: coj.uci.cu/24h/problem.xhtml?pid=1155
**/

typedef vector<vector<int64>> matrix;

vector<int64> fast_rec(int N, vector<int64>& f, vector<int64>& c){
    int K = f.size();
    
    matrix F(K);
    matrix T(K, vector<int64>(K, 0) );
    
    T[K-2] = c; T[K-2].pb(0);
    
    for(int i=0; i < K; i++){
        F[i] = {f[i]};
        if( i+1 < K ) T[i][i+1] = 1;    
    }    
    T[K-1][K-1] = 1;
    
    T = pot(T, N-1);
    F = mult(T, F);
    
    vector<int64> ans;
    for(auto i: F) ans.pb(i[0]); 
        
    return ans;     
}
