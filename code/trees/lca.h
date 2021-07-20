/* Lowest Common Ancestor 
 - Tiempo: Prec: O(cn*log(cn)). Query: O(log(cn)) 
 - Tested on: maxflow USACO Dic 2015 Platinum    
**/
struct lca{
    int cn;
    vector<int>L;
    vector<vector<int>> P;
    
    lca(int cn): 
        cn(cn), L(cn+1), P(cn+1, vector<int>(20, 0))
    {
        L[1] = 1;
        dfs(1, -1);
        
        for(int j=1; j<=log2(cn); j++)
            for(int i=1; i<=cn; i++)
                P[i][j] = P[ P[i][j-1] ][j-1];
    }
    
    void dfs(int nod, int p){
        for(auto nwn: G[nod]) if( nwn != p ){
            P[nwn][0] = nod;
            L[nwn] = L[nod] + 1;    
            dfs(nwn, nod);
        }    
    }
    
    int query(int a, int b){
        if( L[a] < L[b] ) swap(a, b);
        
        for(int i=log2(L[a]); ~i; i--)
            if( P[a][i] && L[ P[a][i] ] >= L[b] )
                a = P[a][i];
        if( a==b ) 
            return a;
            
        for(int i=log2(L[a]); ~i; i--)
            if( P[a][i] && P[a][i] != P[b][i] )
                a = P[a][i], b = P[b][i];        
        return P[a][0];    
    }
};
