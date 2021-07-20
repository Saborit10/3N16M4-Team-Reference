/* Wavelet Tree
 - v[i] representa la cantidad de elementos que van en el subarbol
   izquierdo. Los i - v[i] restantes van en el subarbol derecho.
 - kth(): Devuelve el k-esimo elemento en el rango
 - lte(): Devuelve la cantidad de elementos menores o iguales a k 
 - great(): Devuelve la cantidad de elementos mayores que k
 - count(): Devuelve la cantidad de elementos iguales k en el rango
 - Tiempo: Prep: O(n*log(Max)), Queries: log(Max)
 - Memoria: O(n*log(Max))
 - Tested on: promote (USACO 2017 January Contest, Platinum) 
 OJO: Destruye el intervalo que se le pasa. Los numeros en el arreglo
 pueden ser negativos.
**/

struct wavelet_tree{
    int lo, hi;
    vector<int> v;
    wavelet_tree *L, *R;
    
    wavelet_tree(){}
    wavelet_tree(int* x, int* xend, int a, int b){
        lo = a, hi = b;
        
        if( lo == hi || x >= xend ) return;
        
        int m = (lo + hi)/2;
        auto f = [m](int p){ return p <= m; };
        v.reserve(xend - x + 1); v.pb(0);
        
        for(auto it=x; it != xend; it++)
            v.pb(v.back() + f(*it));
            
        auto pivot = stable_partition(x, xend, f);
        L = new wavelet_tree(x, pivot, lo, m);
        R = new wavelet_tree(pivot, xend, m+1, hi);
    }
    
    int lte(int a, int b, int k){
        if( a > b || k < lo ) return 0;
        if( hi<=k ) return b - a + 1;
        return L->lte(v[a-1]+1, v[b], k)+R->lte(a-v[a-1], b-v[b], k);
    }
    
    int kth(int a, int b, int k){
        if( a > b ) return 0;
        if( lo==hi ) return lo;
    
        int in_left = v[b] - v[a-1];
        if( k<=in_left )
            return L->kth(v[a-1] + 1, v[b], k);
        else
            return R->kth(a - v[a-1], b - v[b], k - in_left);
    }
    
    int count(int a, int b, int k){
        if( a > b || k < lo || k > hi ) return 0;
        if( lo==hi ) return b - a + 1;
        
        int m = (lo+hi)/2;
        if( k<=m ) return L->count(v[a-1] + 1, v[b], k);
        else return R->count(a - v[a-1], b - v[b], k);
    }
    
    ~wavelet_tree(){
        delete L;
        delete R;
    }
};
