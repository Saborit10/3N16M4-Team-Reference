/* Mo's Algorithm
 - Ordena las queries, garantizando un tiempo de O(N * sqrt(N)) 
 - Solution for: (circlecroos) Why Did the Cow Cross the Road III
                 USACO 2017 February Contest, Gold  
**/
struct mo{
    struct query{
        int x, xend, id, ans;
    };
    
    struct bundle{
        int cant;
        bool C[MX];
        bundle(): cant(0){}
        
        void add(int x){
            if( C[x] ) cant--;
            else cant++;
            
            C[x] ^= 1;   
        }    
    };
    
    int N;
    int A[MX];
    vector<query> Q;
    
    void add_query(int a, int b, int id){
        Q.pb({a, b, id, -1});
    }
    
    vector<int> solve(){
        sort(all(Q), [this](query& a, query& b){
            int sq = sqrt(Q.size());   
            if( a.x/sq != b.x/sq ) return a.x/sq < b.x/sq;
            return a.xend/sq < b.xend/sq; 
        }); 
        
        int l = 1, r = 0;
        bundle B;
        
        for(auto& q: Q){
            while( r < q.xend )
                B.add(A[++r]);    
            while( l < q.x )
                B.add(A[l++]);
            while( r > q.xend )
                B.add(A[r--]);
            while( l > q.x ) 
                B.add(A[--l]); 
                
            q.ans = B.cant;              
        } 
        vector<int> ans(Q.size() + 1);
        for(auto q: Q)
            ans[q.id] = q.ans;
        
        return ans;          
    }    
};
