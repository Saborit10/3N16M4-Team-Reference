/* Rectangulo de Mayor Area Bajo el Histograma
 - Dado un arreglo (1-indexed) de N elementos que representa la 
   altura de N columnas, se calcula el area del mayor rectangulo 
   dentro de la figura formada por dichas columnas.
 - La clase col guarda en h la altura de la columna y en l la 
   posicion mas a la izquierda hasta donde se puede extender un 
   rectangulo de altura h. 
 - Time: O(n). Memo: O(n).
**/
struct col{ int h, l; };

int64 max_rect(int N, int* A){
    vector<col> S;
    S.pb({-1, 0});
    
    int64 ans = 0;
    for(int i=1, l; i<=N; i++){
        l = i;
        while( S.back().h >= A[i] ){
            ans = max(ans, (int64)S.back().h * (i-S.back().l));
            l = S.back().l;
            S.pop_back();
        }
        S.pb({A[i], l});
    }
    while( S.size() > 1 ){
        ans = max(ans, (int64)S.back().h * (N+1-S.back().l));
        S.pop_back();
    }
    return ans;        
}
