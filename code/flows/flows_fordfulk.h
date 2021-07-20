/* Ford-Fulkerson Method with Scaling Algorithm
 - Inicializar cn, ca, ni, nf;
 - Tiempo: O(E^2 * log(max_edge))
 * [Escribir un constructor como el del Dinic]
 - Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=1695
**/
struct fordfulk{
    int cn, ca, ni, nf, max_edge, f;
    int P[MX];
    int G[MX][MX];
    bool mk[MX]; 
    
    void add_edge(int a, int b, int c){
        G[a][b] += c;  
        max_edge = max(max_edge, c);   
    }
    
    bool augment(int nod, int th){
        mk[nod] = true;
        
        if( nod==nf )
            return true;
        
        int ans = false;
        for(int nwn=1; nwn<=cn; nwn++){ 
            if( !mk[nwn] && G[nod][nwn] > th ){
                P[nwn] = nod;
                ans |= augment(nwn, th);    
            }    
        }
        
        return ans;
    }
    
    void resolve(int nod, int min_edge){
        if( nod==ni ){ f = min_edge; return; }
        else{
            resolve(P[nod], min(min_edge, G[ P[nod] ][nod]));
            G[ P[nod] ][nod] -= f, G[nod][ P[nod] ] += f;    
        } 
    }
    
    int throw_flow(){
        int mf = 0, th = max_edge;    
        
        while( true ){
            for(int i=0; i<=cn; i++) 
                mk[i] = false;
                
            if( augment(ni, th) ){
                resolve(nf, INF);
                mf += f;
            }
            else if( !th ) 
                break;
            else 
                th>>=1;
        }
        return mf;
    } 
};
