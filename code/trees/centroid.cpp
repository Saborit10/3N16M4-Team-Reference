/* Centroid Decomposition
 - up[i] guarda el padre del nodo i en el centroide
 - Inicializar los arreglos mk, up, sz. 
 - Tested on: http://codeforces.com/contest/342/problem/E
**/
struct graph{
    int cn;
    int up[MX], sz[MX]; 
    bool mk[MX];
    vector<int> G[MX];
       
    void add_edge(int a, int b){
        G[a].pb(b);    
        G[b].pb(a);    
    }
    
    int dfs0(int nod, int p){
       sz[nod] = 1;
       
        for(auto nwn: G[nod]) if( !mk[nwn] && nwn != p )
           sz[nod] += dfs0(nwn, nod);    
       return sz[nod];
    }
    
    int dfs1(int nod, int p, const int& tam){
        for(auto nwn: G[nod]){
            if( !mk[nwn] && nwn != p && sz[nwn] > tam )
                 return dfs1(nwn, nod, tam);    
        }
        return nod;
    }
    
    int centdec(int nod){
       int tam = dfs0(nod, -1);
       int cen = dfs1(nod, -1, tam>>1); 
       
       mk[cen] = true;
       
       for(auto nwn: G[cen]) if( !mk[nwn] ){
           int c = centdec(nwn);
           up[c] = cen;    
       }
       return cen;
    }
    
    void build(){
        // Here we build a LCA or something else...
        
        centdec(1);        
    }
};
