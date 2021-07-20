
#define REV(x, n)\
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1); \
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2); \
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4); \
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8); \
    x = ((x & 0xffff0000) >> 16) | ((x & 0x0000ffff) << 16); \
    x >>= (32-n);
    
inline int lg(int n){ return 31 - __builtin_clz(n); }

namespace ntt{
    unsigned int R[MX];
    int P[MX], fa[MX], fb[MX];
    const int GEN = 10;
    
    void build_reverse(int N){
        for(int i=0, l=lg(N); i < N; i++){
            R[i] = i;
            REV(R[i], l);
        }
    }

    void ntt(int N, int A[], bool inv){
        for(int i=0; i < N; i++) if( i < (int)R[i] )
            swap(A[i], A[ R[i] ]);
            
        for(int l=2, wlen; l<=N; l<<=1){
            wlen = pot(GEN, (MOD-1) / l);
            
            if( inv ) wlen = pot(wlen, MOD-2);
            
            for(int x=0, w; x < N; x+=l){
                w = 1;
                for(int i=0; i < (l>>1); i++){
                    int u = A[x+i], v = 1ll * A[x+i+(l>>1)] * w % MOD;
                    A[x+i] = u + v < MOD ? u + v : u + v - MOD;
                    A[x+i+(l>>1)] = u - v >= 0 ? u - v : u - v + MOD;
                    w = 1ll * w * wlen % MOD;
                }
            }
        }
        
        if( inv ){
            int v = pot(N, MOD-2);
            for(int i=0; i < N; i++)
                A[i] = 1ll * A[i] * v % MOD;
        }
    }
    
    int mult(int N, int A[], int M, int B[]){
        int ma = 1 << (lg(max(N, M) - 1) + 2);
        
        build_reverse(ma);
        
        for(int i=0; i < ma; i++){
            fa[i]=  i < N ? A[i] : 0;
            fb[i]=  i < M ? B[i] : 0;
        }
        
        ntt(ma, fa, false), ntt(ma, fb, false);
        
        for(int i=0; i < ma; i++)
            fa[i] = 1ll * fa[i] * fb[i] % MOD;
        
        ntt(ma, fa, true);
        
        while( !fa[ma-1] ) ma--;
        return ma;
    }
};
