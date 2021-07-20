/* Trie 
 - Implementacion simple con vectores
**/
#define SIGMA 26 

struct trie{
    bool end[MX];
    vector< vector<int> > T;
    
    trie(){
         T.pb(vector<int>(SIGMA, -1));   
    }
    
    void add(string S){
        int nod = 0;
         
        for(int i=0; i < (int)S.size(); i++){
            int c = S[i] - 'a';
            
            if( T[nod][c] == -1 ){
                T[nod][c] = T.size();
                T.pb(vector<int>(SIGMA, -1));    
            }
            nod = T[nod][c];
        }
        end[nod] = true; 
    }
    
    bool find(string S){
        int nod = 0;
        
        for(int i=0; i < (int)S.size(); i++){
            int c = S[i] - 'a';
            
            if( T[nod][c] == -1 )
                return 0;
            else nod = T[nod][c];         
        }
        return end[nod];    
    }
};
