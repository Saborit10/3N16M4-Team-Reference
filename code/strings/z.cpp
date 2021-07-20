/* Z-Algorithm
 - Recibe una cadena y devuelve un vector en el que cada posicion i 
   contiene el lcp entre el sufijo de indice cero y el de indice i.
 - Tiempo: O(n)
 - Not Tested Yet!!!
**/
vector<int> z_function(string& S){
    int N = S.size();    
    vector<int> z(N);
    
    z[0] = N;
    for(int i=1, l=0, r=0; i < N; i++){
        if( i <= r )
            z[i] = min(r-i+1, z[i-l]);
        while( i + z[i] < N && S[ z[i] ] == S[ i + z[i] ] )   
            ++z[i];
        if( i + z[i] - 1 > r )
            l = i, r = i + z[i] - 1;        
    }
    return z; 
}
