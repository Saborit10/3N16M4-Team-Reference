/* Fenwick Tree (Binary Indexed Tree)
 - El rango de los indices es [0, n].
 - type es un tipo numerico.
 - Tested on: https://codeforces.com/contest/1616/problem/E
**/
typedef int64 type;

struct fenwick_tree{
    int n;
    vector<type> T;
    
    fenwick_tree(int n): n(n), T(n+2){}
    
    type acc(int b){
        type ans = 0; b++;
        for(; b; b-=(b&(-b))) ans += T[b];
        return ans;
    }
    
    type qry(int a, int b){
        a++, b++;
        return acc(b) - (a == 1 ? 0 : acc(a-1));
    }
    
    void upt(int p, type val){
        for(p++; p<=n; p+=(p&(-p)))
            T[p] += val;
    }
};
