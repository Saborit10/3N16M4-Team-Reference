/* Criba de Eratostenes y Funciones Usadas en Teoria de Numeros 
 - Se usan las variables globales mk[] y p para la criba y para 
   guardar los primos respectivamente.
 - init()       Construye el vector con los primos menores que MX
   Tested on: http://dmoj.uclv.cu/problem/oci19day1a  
 - euler_phi(N) Cuenta el numero de enteros positivos menores que N 
   que son coprimos con N 
   Tested on: http://dmoj.uclv.cu/problem/oci19day1a 
 - cant_pf(N)   Cuenta la cantidad de factores primos de N 
 - diff_pf(N)   Cuenta la cantidad de factores primos diferentes 
   de N
   Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=3274  
 - cant_div(N)  Cuenta la cantidad de divisores de N 
 - sum_div(N)   Devuelve la suma de los divisores de N
   Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=1132
**/

/* Criba de Eratostenes */
const int MN = 1'000'000;
bool mk[MN+5];
vector<int> p;

void init(){
    for(int64 i=2; i < MX; i++) if( !mk[i] ){
        p.pb(i);
        for(int64 j=i*i; j < MX; j+=i) mk[j] = true;    
    }    
}

/* Cantidad de Enteros Positivos Menores que N Coprimos con El */
int64 euler_phi(int64 N){
    int64 ans = N;
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        if( N % p[i] == 0 ) ans -= ans / p[i];
        while( N % p[i] == 0 ) N /= p[i];
    }    
    if( N > 1ll ) ans -= ans / N;
    
    return ans;
}

/* Cantidad de Factores Primos */
int cant_primos(int64 N){
    int ans = 0;
    
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        while( N % p[i] == 0 ){
            ans++;
            N /= p[i];   
        }     
    }
    if( N > 1ll ) ans++;
    
    return ans;
}

/* Cantidad de Factores Primos Diferentes */
int cant_primos_diff(int64 N){
    int ans = 0;
    
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        if( N % p[i] == 0 ) ans++;
        while( N % p[i] == 0 ) N /= p[i];    
    }
    if( N > 1ll )    
        ans++;
        
    return ans;    
}

/* Cantidad de Divisores */
int cant_div(int64 N){
    int ans = 1, power;
    
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        power = 0;
        
        while( N % p[i] == 0 ){
            N /= p[i];
            power++;    
        }
        ans *= power + 1;    
    }  
    if( N > 1ll ) ans *= 2;
    
    return ans;  
}

/* Suma de los Divisores */ 
int64 sum_div(int64 N){
    int64 ans = 1ll, power;
    
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        power = 0;
        
        while( N % p[i] == 0 ){
            N /= p[i];
            power++;    
        }
        ans *= ((int64)pow((double)p[i], power + 1.0)-1) / (p[i]-1);    
    }    
    if( N > 1ll )
        ans *= ((int64)pow((double)N, 2.0) - 1) / (N - 1);
        
    return ans;    
}
