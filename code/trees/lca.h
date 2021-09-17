/* Lowest Common Ancestor 
 - Dado un arbol, crea una estructura que permite calcular el ancestro
   comun mas bajo de dos nodos de dicho arbol.
 - Segun el tipo edge cambiar las lineas que usan nwn dentro de la
   funcion dfs().
 - El contructor lca() pide la cantidad de nodos, una lista de
   adyacencia que represente al grafo, y el nodo raiz (puede faltar).
 - qry() devuelve el lca de a y b.
 - Tiempo: Prec: O(cn*log(cn)). Query: O(log(cn)) 
 - Tested on: https://www.spoj.com/problems/COT
**/
typedef int edge;

struct lca{
    int cn;
    vector<edge> *G;
    int L[MX], P[MX][20];
    
    lca(int cn, vector<edge> G[], int ni=1): cn(cn), G(G){
        L[ni] = 1, P[ni][0] = 0;
        dfs(ni, -1);
        
        for(int j=1, lg=log2(cn); j<=lg; j++)
            for(int i=1; i<=cn; i++)
                P[i][j] = P[ P[i][j-1] ][j-1];
    }
    
    void dfs(int nod, int p){
        for(auto nwn: G[nod]) if( nwn != p ){
            L[nwn] = L[nod] + 1;
            P[nwn][0] = nod;
            dfs(nwn, nod);
        }
    }
    
    int qry(int a, int b){
        if( L[a] < L[b] ) swap(a, b);
        
        for(int i=log2(L[a]); ~i; i--)
            if( L[ P[a][i] ] >= L[b] )
                a = P[a][i];
        if( a == b ) return a;
        
        for(int i=log2(L[a]); ~i; i--)
            if( P[a][i] && P[a][i] != P[b][i] )
                a = P[a][i], b = P[b][i];
        return P[a][0];
    }
};
