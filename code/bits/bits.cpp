/*
   Metodos Utiles con Bits
*/

/* ===============================================================
 - Retorna el siguiente entero con igual cantidad de bits 
   encendidos 
**/
    uint next_popcount(uint n){
        uint c = (n & -n);
        uint r = n + c;
        return (((r ^ n) >> 2) / c) | r;
    }
/* ===============================================================
 - Retorna el primer entero con n bits encendidos 
**/
    uint init_popcount(int n){
        return (1 << n) - 1;
    }
/* ===============================================================
 - Itera sobre todas las submascaras de m, en orden decreciente 
   excepto m misma y cero 
**/
    for(int i = m; i; ){ 
        --i &= m; 
        //aqui i tiene el valor requerido
    }
/* ============================================================ */

/* 
 Metodos de C++ (si se agrega ll al final se puede usar con 
 unsigned long long)
**/

/* ===============================================================  
 - Retorna la cantidad de leading zeros 
**/  
    int __builtin_clz(unsigned int x) 
/* ===============================================================
 - Retorna la cantidad de trailing ceros 
**/
    int __builtin_ctz(unsigned int x) 
/* ===============================================================
 - Retorna la cantidad de 1-bits 
**/
    int __builtin_popcount(unsigned int x) 
/* ===============================================================
 - Retorna la cantidad de 1-bits modulo 2 
**/
    int __builtin_parity(unsigned int x) 
/* ===============================================================
 - Retorna 1 + el 1-bit menos significativo de x. Si x == 0, 
   retorna 0 
**/
    int __builtin_ffs(int x)
/* ============================================================ */