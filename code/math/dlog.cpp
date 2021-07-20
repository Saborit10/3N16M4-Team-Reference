/* Logaritmo Discreto
 - Dados tres numeros enteros a, b y m, se busca un entero x tal que 
    a^x = b (mod m). En esta version gcd(a, m) = 1.
 - Este codigo busca el menor x posible. 
 - O(sqrt(n) * lg(n))
 - Tested on: LIGHTOJ 1325 
**/

int64 dlog(int64 a, int64 b, int64 m=MOD){
    vector<pair<int64, int64>> v;
    int64 k = (int64)sqrt(m + 0.) + 1, ans = INF;
    
    int64 aa = pot(a, k, m), p = aa;
    for(int i=1; i<=k; i++)
        v.pb({p, i}), p = p * aa % m;    
    
    sort(all(v));
    for(int i=0; i<=k; i++){
        auto it = lower_bound(all(v), make_pair(b, 0ll));
        
        if( it != v.end() && it->fr == b )
            ans = min(ans, it->sc * k - i);
        b = b * a % m;
    }
    return ans;
}
