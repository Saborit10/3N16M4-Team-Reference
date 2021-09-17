/* LCA con Pesos
 - Dado un arbol, con peso en las aristas (cost), responde queries
   relacionadas con el camino entre dos nodos, tales como minimo en
   el camino, maximo, suma, etc.
 - El constructor recibe la cantidad de nodos (es obligatorio
   comenzar por el nodo 1), la lista de adyacencia, y la raiz del
   arbol. El tipo de la plantilla debe ser una clase monoide.
 - Se deben implementar las clases monoide(tipo de la plantilla) y par
   (tipo de las aristas en la lista de adycencia). 
 - qry(): devuelve un monoide que representa la respuesta a la query.
 - La clase monoide debe implementar los siguientes metodos:
   * monoide(): constructor del elemento neutro de la operacion.
   * monoide(const monoide&, const monoide&): constructor de mezcla a
   partir de dos monoides.
   * monoide(tipo del costo): constructor a partir de un elemento del
   tipo del costo de la arista.
 - La clase par debe tener los campos nwn (nodo al que apunta la
   arista) y cost (costo de la arista).
 - Tested on: https://codeforces.com/contest/1184/problem/E2
**/
template<class T>
struct lca{
    int cn;
    vector<par> *G;
    int L[MX], P[MX][20];
    T C[MX][20];
    
    lca(int cn, vector<par> G[], int ni=1): cn(cn), G(G){
        L[ni] = 1;
        P[ni][0] = 0;
        dfs(ni, -1);
        
        for(int j=1, lg=log2(cn); j<=lg; j++)
            for(int i=1; i<=cn; i++){
                P[i][j] = P[ P[i][j-1] ][j-1];
                C[i][j] = T(C[i][j-1], C[ P[i][j-1] ][j-1]);
            }
    }
    
    void dfs(int nod, int p){
        for(auto i: G[nod]) if( i.nwn != p ){
            L[i.nwn] = L[nod] + 1;
            P[i.nwn][0] = nod;
            C[i.nwn][0] = T(i.cost);    // Esta linea se puede cambiar
            dfs(i.nwn, nod);
        }
    }
    
    T qry(int a, int b){
        if( L[a] < L[b] ) swap(a, b);
        
        T ans;
        for(int i=log2(L[a]); ~i; i--)
            if( L[ P[a][i] ] >= L[b] ){
                ans = T(ans, C[a][i]);
                a = P[a][i];
            }
        if( a == b ) return ans;
        
        for(int i=log2(L[a]); ~i; i--)
            if( P[a][i] && P[a][i] != P[b][i] ){
                ans = T(ans, C[a][i]);
                ans = T(ans, C[b][i]);
                a = P[a][i], b = P[b][i];
            }
        return T(ans, T(C[a][0], C[b][0]));
    }
};
