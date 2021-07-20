/* 
 Versiones propias de funciones matematicas
**/

/* =============================================================
 - Calcula el ceil de a / b, sin importar el signo de estos.
**/
    inline int ceil(int a, int b){
        return a / b + ((a > 0) ^ (b > 0) ? 0 : a % b != 0); 
    }
/* ========================================================== */
