/* Dictionary Of Basic Substrings 
 - Dada una subcadena, proporciona un par ordenado (factor) que sirve
   para compararla con otra subcadena de igual largo, 
   lexicograficamente.
 - Tiempo: Preproc: O(n * log^2(n)). Query: O(1).
 - Tested on: https://coj.uci.cu/24h/problems.xhtml?pid=3540  
**/
struct factor{
    int a, b, p;
    
    bool operator < (const factor& p)const{
        return a == p.a ? b < p.b : a < p.a; 
    }
    bool operator == (const factor& p)const{
        return a == p.a && b == p.b; 
    }
};

struct fact_dict{
    int N;
    vector<factor> L;
    vector<vector<int>> P;
    
    fact_dict(string& S):
        N(S.size()),
        P(N, vector<int>(log2(N) + 1, -1))
    {
        for(int i=0; i < N; i++)
            L.pb({S[i] - 'a', 0, i});
        
        sort(all(L)); 
        
        for(int i=0; i < N; i++)
            P[ L[i].p ][0] = i && L[i]==L[i-1] ? P[ L[i-1].p ][0] :i; 
            
        for(int j=1, l = log2(N); j<=l; j++){
            N -= (1<<(j-1));
            L.clear();
            
            for(int i=0; i < N; i++)
                L.pb({P[i][j-1], P[i + (1<<(j-1))][j-1], i});    
                
            sort(all(L));
            
            for(int i=0; i < N; i++)
                P[ L[i].p ][j] = i && L[i]==L[i-1] ? 
                                                P[ L[i-1].p ][j] : i;   
        }    
    } 
    
    factor fact(int a, int b){
        int k = log2(b - a + 1);
        return {P[a][k], P[b - (1<<k) + 1][k], -1};    
    }
};    
