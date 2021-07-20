/* Bit Trie
 - Responde varias queries relacionadas con bits sobre un conjunto 
   de enteros con signo
 - Tested on: https://icpcarchive.ecs.baylor.edu/index.php?Itemid=
   8&category=345&option=com_onlinejudge&page=show_problem&problem=
   2683
**/
 
struct bit_trie{
    vector<int> end;   
    vector< vector<int> > T;
    
    bit_trie(){
       end = vector<int>(32 * MX, -1); 
       T.pb(vector<int>(2, -1));    
    } 
    /* Inserta un entero al conjunto */
    void add(uint N){
        int nod = 0;
        for(int i=31; ~i; i--){
            bool c = N & (1<<i);
            
            if( T[nod][c] == -1 ){
                T[nod][c] = T.size();
                T.pb(vector<int>(2, -1));    
            }
            nod = T[nod][c];
        }
        end[nod] = N;    
    }
    
    /* Retorna el maximo xor de N con un numero dentro del trie */
    uint max_xor(uint N){
        int nod = 0;
        for(int i=31; ~i; i--){
            bool c = N & (1<<i);
            
            if( ~T[nod][c^1] )
                nod = T[nod][c^1];
            else if( ~T[nod][c] )
                nod = T[nod][c];
            else break;            
        }
        if( ~end[nod] )
            return end[nod] ^ N;
        return -1;    
    }
};
