/* Fenwick Tree (Binary Indexed Tree) 
 - El rango de los indices debe ser 1-indexed.
 - Tested on: http://dmoj.uclv.cu/problem/oci19day2b
OJO: Si se crea un objeto fenwick_tree dentro de una funcion, hay que
   llenarlo limpiarlo (puede hacerse con un constructor).
**/
#define MN (int)1e5

struct fenwick_tree{
    int64 T[MN+5];
    
    int64 acc(int b){
        int64 ans = 0;
        for(; b; b-=(b&(-b))) ans += T[b];
        return ans;
    }
    
    int64 query(int a, int b){
        return acc(b) - (a == 1 ? 0 : acc(a-1));
    }
    
    void update(int p, int64 val){
        for(; p<=MN; p+=(p&(-p)))
            T[p] += val;
    }
};