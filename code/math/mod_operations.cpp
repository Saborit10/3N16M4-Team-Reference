/* Operaciones con Modulo
 - su (suma), sb(sustraccion), pd(producto), di(division).
 - Tested on: https://codeforces.com/contest/1511/problem/E
**/
int64 pot(int64 base, int64 e){
    int64 ans = 1ll;

    while( e ){
        if( e & 1ll ) ans = ans * base % MOD;
        base = base * base % MOD;
        e>>=1ll;
    }
    return ans;
}

inline int su(int a, int b){
    if( a + b >= MOD ) return a + b - MOD;
    return a + b;
}

inline int sb(int a, int b){
    if( a < b ) return a - b + MOD;
    return a - b;
}

inline int pd(int a, int b){
    return 1ll * a * b % MOD;
}

inline int di(int a, int b){
    return 1ll * a * pot(b, MOD-2) % MOD;
}
