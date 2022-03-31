/* Fenwick Tree (Binary Indexed Tree)
 - El rango de los indices es [1, n].
 - type debe ser un tipo numerico con el que se pueda hacer resta
   de prefijos.
 - Tested on: https://dmoj.uclv.edu.cu/problem/oci19day2b
**/
template<class type>
struct fenwick_tree{
    int n;
    vector<type> T;
    
    fenwick_tree(int n): n(n), T(n+1){}
    
    type acc(int b){
        type ans = 0;
        for(; b; b-=(b&(-b))) ans += T[b];
        return ans;
    }
    
    type qry(int a, int b){
        return acc(b) - (a == 1 ? 0 : acc(a-1));
    }
    
    void upt(int p, type val){
        for(; p<=n; p+=(p&(-p)))
            T[p] += val;
    }
};
