/* Criba Lineal (Mobius Function)
 - La implementacion calcula lo valores de la funcion de Mobius para
   el rango [1, n].
 - Para Mobius: Time: O(n), Memory: O(n).
             /  1,      si n = 1
 - mu[n] =  {   0,      si n contiene un factor primo cuadrado. 
             \  (-1)^k, si n esta formado por k primos diferentes.

 - La criba lineal puede ser usada para encontrar todos lo valores de
   una funcion multiplicativa f(x) en un rango dado [1, n]. Cada
   entero x sera selecionado solo una vez, y cumplira una de las
   siguientes propiedades:
    * x es primo: se determina el valor de f(x) directamente.
    * x = i*p y p no divide a i: En este caso f(x) = f(i) * f(p), ya
      que f es multiplicativa.
    * x = i*p y p divide a i: Tenemos que buscar una relacion entre
      f(i) y f(i * p), pero en la mayoria de las situaciones, existe
      una relacion simple.
 - El codigo se puede modificar para calcular otras funciones
   multiplicativas, diferentes de f(n) = 0. Para ello se deben
   modificar los metodos siguentes:
    * prime_value(int p): debe devolver el valor f(p).
    * not_coprime_value(int i, int p): debe devolver el valor
      f(i * p) si p divide a i.
 - Un objeto de esta clase se puede tratar como un arreglo, por
   ejemplo, si el nombre de la instancia es mu, mu[i] es el valor de
   la funcion para i.
**/
typedef int type;
 
struct linear_sieve{
    type f[MX];
    bool mk[MX];
    vector<int> p;
    
    linear_sieve(int N){
        f[1] = 1;
        for(int64 i=2; i<=N; i++){
            if( !mk[i] ){
                p.pb(i);
                f[i] = prime_value(i);
            }
            for(int j=0; j < len(p) && i * p[j]<=N; j++){
                mk[i * p[j]] = true;
                if( i % p[j] == 0 ){
                    f[ i * p[j] ] = not_coprime_value(i, p[j]);
                    break;
                }
                else
                    f[ i * p[j] ] = f[i] * f[ p[j] ];
            }
        }
    }
    
    type prime_value(int p){ return -1; }
    type not_coprime_value(int i, int p){ return 0; }
    
    type operator[](int x){ return f[x]; }
};
