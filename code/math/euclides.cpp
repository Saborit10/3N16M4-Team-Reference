/* Algoritmo de Euclides Extendido
 - Devuelve en un objeto de tipo tri, tres valores x, y, d tal que
   para los a y b dados, se cumple que ax + by = d, con d = gcd(a, b)
 - Para resolver la ecuacion diofantica ax + by = c, se debe tener en
   cuenta que si c no es multiplo de d, entonces no hay solucion.
 - Sino, una solucion es (x * c/d, y * c/d)
 - Sea (x, y) la solucion encontrada, la forma general de las 
   soluciones es (x + (b/d) * k, y - (a/d) * k) donde k es un entero.  
 - Tested on: https://open.kattis.com/problems/generalchineseremainder
**/
struct tri{ int64 x, y, d; };

tri ext_euclid(int64 a, int64 b){
    if( !b ) return {1, 0, a};
    tri d = ext_euclid(b, a%b);
    return {d.y, d.x - (a/b) * d.y, d.d};    
}
