/*
 Cubo de Seis Caras
 - rotU, rotD, rotR, rotL rotan la cara dearriba del cubo (F) hacia 
   la direccion indicada. rotCW y rotCCW rotan dicha cara en el 
   sentido de las las manecillas del reloj, y en sentido contrario, 
   respectivamente. 
 - Todos los metodos hacen t rotaciones.
 - Tiempo: O(1) por rotacion. Memo: O(1).
**/

template<class T>
struct cube{
    T L, F, R, B, U, D;
    
    void rotU(int t=1){
        for(int i=0; i < t % 4; i++)
            swap(D, B), swap(B, U), swap(U, F);
    }
    void rotD(int t=1){
        for(int i=0; i < t % 4; i++)
            swap(U, B), swap(B, D),swap(D, F);
    }
    void rotR(int t=1){
        for(int i=0; i < t % 4; i++)
            swap(B, R), swap(R, F), swap(F, L);
    }
    void rotL(int t=1){
        for(int i=0; i < t % 4; i++)
            swap(L, F), swap(F, R), swap(R, B);
    }
    void rotCW(int t=1){
        for(int i=0; i < t % 4; i++)
            swap(L, D), swap(D, R), swap(R, U);
    }
    void rotCCW(int t=1){
        for(int i=0; i < t % 4; i++)
            swap(U, R), swap(R, D), swap(D, L);
    }
};
