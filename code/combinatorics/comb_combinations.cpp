/* Combinciones segun la formula.
 OJO: Llamar a init() en el main().
 - Se usa para calcular C(n, k) para n < MX, k < MX.
 - Tested on: https://codeforces.com/contest/1420/problem/D
 - Dependencias: pot(), mod_inv
**/
int64 fact[MX];

void init(){
    fact[0] = 1;
    for(int i=1; i < MX; i++)
        fact[i] = fact[i-1] * i % MOD;
}

int64 C(int n, int k){
    if( n < 0 || k < 0 || k > n ) return 0;
    return mod_inv(fact[n], fact[k] * fact[n-k] % MOD);
}
