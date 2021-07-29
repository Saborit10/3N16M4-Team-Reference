/* 
 Versiones propias de funciones matematicas
**/

/* =============================================================
 - Calcula el ceil de a / b, sin importar el signo de estos.
**/
    inline int ceil(int a, int b){
        return a / b + ((a > 0) ^ (b > 0) ? 0 : a % b != 0); 
    }
/* =============================================================
 - Devuelve el ceil del logaritmo base 2 de n, para n > 0. Es
   igual a la cantidad de cifras binarias significativas menos 1
**/
    inline int lg(int n){ return 31 - __builtin_clz(n); }
/* =============================================================
 - Devuelve el ceil del logaritmo base 2 de n, para n > 0. Es
   la version para enteros de 64 bits.
**/
    inline int lg(int64 n){ return 63 - __builtin_clzll(n); }
/* ===========================================================*/
