/* Lowest Common Ancestor 
 - Dado un arbol, crea una estructura que permite calcular el ancestro
   comun mas bajo de dos nodos de dicho arbol.
 - Segun el tipo edge cambiar las lineas que usan nwn dentro de la
   funcion dfs().
 - El contructor lca() pide la cantidad de nodos, una lista de
   adyacencia que represente al grafo, y el nodo raiz (puede faltar).
 - qry() devuelve el lca de a y b.
 - Tiempo: Prec: O(cn*log(cn)). Query: O(log(cn)) 
 - Tested on: https://codeforces.com/contest/555/problem/E
**/
typedef vector<int> vii;

struct lca{
    int cn;
    vector<edge> *G;
    vector<vii> P;
    vector<int> L;
    
    lca(int cn, vector<edge> G[]): cn(cn), G(G){
        int l = log2(cn) + 2;
        L = vector<int>(cn+1);
        P = vector<vii>(cn+1, vii(l));
         
        for(int i=1; i<=cn; i++) if( !L[i] ){
            L[i] = 1, P[i][0] = 0;
        
            dfs(i, -1);
        }
        
        for(int j=1, lg=log2(cn); j<=lg; j++)
            for(int i=1; i<=cn; i++)
                P[i][j] = P[ P[i][j-1] ][j-1];
    }
    
    void dfs(int nod, int p){
        for(auto i: G[nod]) if( i.nwn != p ){
            L[i.nwn] = L[nod] + 1;
            P[i.nwn][0] = nod;
            dfs(i.nwn, nod);
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
