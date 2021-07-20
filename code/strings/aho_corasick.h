/*  Aho-Corasick
 - Implementacion con arreglo de mapas. 
 - T es el Trie, ac[i] guarda los ids de las cadenas que terminan en
   el nodo i, y F es un arreglo de punteros enteros al nodo del
   sufijo propio mas largo que es tambien sufijo de un patron.
 - match(): genera todas las posiciones donde termina la ocurrencia
   del patron p (1-indexed segun el orden en que fueron agregados al 
   trie).
 - cn es la cantidad de nodos y sz es la cantidad de cadenas
   almacenadas.
 - Tested on: Croatia 2006 severina 
**/
#define MN 400000 //Cant. total de caracteres en los patrones 

struct aho_corasick{
    int cn, sz;                   //Cant. de nodos y cant. de cadenas
    int F[MX], L[MX]; //Fail y largo de la i-esima cadena (1-indexed)
    vector<int> ac[MX];
    map<char, int> T[MN];
    
    aho_corasick(): cn(1), sz(0){}
    
    void add(char* S){
        int nod = 0; sz++;              //No cambiar el orden de esto
        L[sz] = strlen(S);
    
        for(int i=0; i < L[sz]; i++){
            if( !T[nod].count(S[i]) )
                T[nod][ S[i] ] = cn++;
            nod = T[nod][ S[i] ];
        }
        ac[nod].pb(sz);
    }
    
    void build(){
        queue<int> Q;
        for(auto i: T[0]) Q.push(i.sc);
        
        for(; !Q.empty(); Q.pop()){
            int nod = Q.front();
            
            for(auto c: T[nod]){
                int st = F[nod];
                
                while( st > 0 && !T[st].count(c.fr) )
                    st = F[st];
                if( T[st].count(c.fr) )
                    st = T[st][c.fr];
                F[c.sc] = st;
                
                for(auto i: ac[st]) ac[c.sc].pb(i);
                Q.push(c.sc);
            }
        }
    }
    
    void match(char* S){
        int N = strlen(S);
        
        for(int i=0, st=0; i < N; i++){
            while( st > 0 && !T[st].count(S[i]) )
                st = F[st];
            if( T[st].count(S[i]) )
                st = T[st][ S[i] ];
            
            for(auto p: ac[st]){
                // Hay un match del patron p que termina en la 
                //posicion i
            }
        }   
    }
};
