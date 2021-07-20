/* Teorema Chino del Resto  
 - Programado en forma de estructura. Se le agregan una a una las 
   relaciones de congruencia. 
 - Retorna false si no hay solucion. Si la hay (retorna true) esta 
   en ans y esta tomada modulo lcm. 
 - Tiempo: O(n * log(lcm(m_1, m_2, ..., m_n)) ) 
 - Tested on: https://open.kattis.com/problems/generalchineseremainder       
**/

inline int64 norm(int64 a, int64 m){ return (a % m + m) % m; }

struct crt{
    int64 ans, lcm;
    
    crt(): ans(0), lcm(1){}
    
    bool add(int64 a, int m){
        auto d = ext_euclid(lcm, m);
        if( (a - ans) % d.d != 0 ) return false;
        
        ans = norm(ans + d.x * (a - ans) / d.d % 
                                (m / d.d) * lcm, lcm * m / d.d);
        lcm *= m / d.d;
        return true;
    }    
};
