/* Fast Fourier Transform
 - Multiplica dos polinomios A y B.
 - El metodo mult() recibe dos arreglos A y B, de largo N y M
   respectivamente, donde cada posicion i guarda el coeficiente de la
   variable de exponente i, o sea LOS ARREGLOS SON 0-INDEXED.
 - Los arreglos A y B, deben tener tantas posiciones como P, la menor 
   potencia de dos que es mayor que 2* max(N, M).
 - El arreglo que representa el polinomio resultante (de largo a lo
   mas P) se guarda en A. P es retornado. Potencialmente habra ceros 
   es las posiciones mas significativas del arreglo. 
 - type es el tipo de datos con el cual se calcula internamente en el
   fft. Si hay problemas de presicion, cambiar a long double; pero es
   mas lento.   
 - T es el tipo de numero usado para representar los coeficientes de
   los polinimios.
 - Al convertir nuevamente a T los valores flotantes en la linea
        A[i] = (T)llround(fa[i].real());
   deben tenerse en cuenta posibles erroes de presicion. Si todos los
   coeficientes son positivos, se puede usar
        A[i] = (T)(fa[i].real() + 0.5);
 - El metodo build_reverse() calcula la 'bit-reversal permutation', 
   que es el orden de las hojas, para comenzar el calculo iterativo
   desde ellas hasta la raiz.
 - El metodo fft() convierte el polinomio de forma canonica a forma de 
   puntos de datos y viceversa.
 - REV(x, n) invierte el orden de los n bits menos significativos de 
   x. Los demas bits son puestos a cero.
 - Tiempo: O(n lg n) con constantes altas. Memoria: O(n)
 - Tested: [Stress Tested]
**/
#define REV(x, n)\
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);\
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);\
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);\
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);\
    x = ((x & 0xffff0000) >> 16) | ((x & 0x0000ffff) << 16);\
    x >>=(32-n);

typedef double type;
typedef complex<type> cpx;
typedef int T;
inline int lg(int n){ return 31 - __builtin_clz(n); }

namespace fft{
    unsigned int R[MX];
    cpx fa[MX], fb[MX], P[MX];
    
    void build_reverse(int N){
        for(int i=0, l=lg(N); i < N; i++){
            R[i] = i; 
            REV(R[i], l);
        }
    }
    
    void fft(int N, cpx A[], bool inv){
        for(int i=0; i < N; i++)
            if( i < (int)R[i] )
                swap(A[i], A[ R[i] ]);
        
        for(int n=2; n<=N; n<<=1){
            type ang = 2 * M_PI / n * (inv ? -1 : 1);
            cpx w = cpx(cos(ang), sin(ang));
            
            P[0] = cpx(1, 0);
            for(int i=1; i < (n>>1); i++)
                P[i] = P[i-1] * w;
            
            cpx t, *pu, *pv, *pp, *pm;
            for(int i=0; i < N; i+=n){
                pu = A + i, pv = A + i + (n>>1), pm = pv, pp = P;
                
                for(; pu != pm; pu++, pv++, pp++){
                    t = *pv * *pp;
                    *pv = *pu - t;
                    *pu += t;
                }
            }
        }
        if( inv ) for(int i=0; i < N; i++)
            A[i] /= N;
    }
    
    int mult(int N, T A[], int M, T B[]){
        int ma = 1<<(lg(max(N, M) - 1) + 2);
         
        build_reverse(ma);
         
        for(int i=0; i < ma; i++){
            fa[i] = i < N ? cpx(A[i], 0) : cpx(0, 0);    
            fb[i] = i < M ? cpx(B[i], 0) : cpx(0, 0);    
        }
        
        fft(ma, fa, false); fft(ma, fb, false);
        
        for(int i=0; i < ma; i++)
            fa[i] = fa[i] * fb[i];
            
        fft(ma, fa, true);
        
        for(int i=0; i < ma; i++)
            A[i] = (T)llround(fa[i].real());
        return ma;
    }
};
