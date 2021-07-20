/* Exponeciacion Modular Iterativa e 
 * Inverso Modular
 * 
 * Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=2259
 **/

int64 pot(int64 base, int64 e){
    int64 ans = 1ll;
    
    while( e ){
        if( e & 1ll ) ans = (ans * base) % MOD;
        base = (base * base) % MOD;
        e>>=1ll;    
    } 
    
    return ans;  
}

inline int64 mod_inv(int64 a, int64 b){
    return (a * pot(b, MOD-2ll)) % MOD;    
}
