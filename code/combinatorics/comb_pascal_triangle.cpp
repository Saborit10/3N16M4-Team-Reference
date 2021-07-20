/* Triangulo de Pascal
 - Precalcula las combinaciones con n y k hasta N en O(N^2)
 - O(1) para responder las queries 
 - Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=3335
**/
int C[MX][MX];

void build_pascal(){
    for(int i=0; i<=1000; i++)
        C[i][0] = C[i][i] = 1;
        
    for(int n=1; n<=1000; n++) for(int k=1; k<=1000; k++)     
        C[n][k] = ( C[n-1][k] + C[n-1][k-1]) % MOD;
}
