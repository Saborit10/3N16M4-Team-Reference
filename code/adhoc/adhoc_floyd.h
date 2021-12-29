/* Algoritmo de Floyd Para la Deteccion de Ciclos
 - Dados una funcion f y un valor inicial (de indice 0) x. El metodo
   floyd() calcula el indice donde inicia el ciclo(mu) y el largo de
   este(lambda).
 - Tiempo: O(mu + lambda).
 - Memoria: O(1).
 - Tested on: UVA350 Pseudo-Random Numbers
**/
pair<int, int> floyd(int (*f)(int), int x){
    int mu = 0, lambda = 1;
    
    int t = f(x), h = f(f(x));
    
    while( h != t )
        t = f(t), h = f(f(h));
    
    h = x;
    while( h != t ){
        t = f(t), h = f(h);
        mu++;
    }

    h = f(t);
    while( h != t ){
        h = f(h);
        lambda++;
    }
    return {mu, lambda};
}
