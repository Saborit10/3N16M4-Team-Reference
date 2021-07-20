/* 2-SAT
 - Dadas las variables a1, a2, ..., a_n (N variables), y 
   proposiciones de la forma (xi v yi) donde cada xi, yi pertenece 
   al conjunto de las N variables o sus negaciones. Todas deben ser 
   cumplidas.
 - add(b1, a1, b2, a2) : agrega una proposicion, donde a1 y a2 son 
   indices de las variables [1, N] y las b1 y b2 son falsas si las 
   variables estan negadas, y verdaderas si no.
 - solve(): devuelve verdadero si la formula se puede satisfacer. En 
   el arreglo sol[i] se guarda 'T' si el valor de la variable i DEBE 
   ser true, se guarda 'F' si debe ser false, y '?' si puede ser 
   cualquiera. O(n^2).
 - El nodo 2*i-1 representa a ai, mientras que 2*i representa a la 
   negacion de ai.
 - Tested on: cowngress USACO Enero 2011
**/

struct two_sat{
    int N, M;
    bool mk[MX];
    char sol[MX];
    vector<int> G[2*MX];
    
    void add(bool b1, int a1, bool b2, int a2){
        G[2 * a1 - (!b1)].pb(2 * a2 - b2);    
        G[2 * a2 - (!b2)].pb(2 * a1 - b1);    
    }
    
    bool solve(){
        vector<vector<int>> scc = kosaraju(2*N, G);
        
        function<void(int)> dfs = [&](int nod){
            mk[nod] = true;
            
            for(auto nwn: G[nod]) if( !mk[nwn] )
                dfs(nwn);
        };
        
        for(auto& vec: scc){
            sort(all(vec));    
            
            for(int i=1; i < (int)vec.size(); i++)
                if( (vec[i-1] & 1) && vec[i] == vec[i-1] + 1 )
                    return false;        
        }
        
        for(int i=1; i<=N; i++)
            sol[i] = '?';
        
        for(int i=1; i<=2*N; i++){
            for(int j=1; j<=2*N; j++) 
                mk[j] = false;
                
            dfs(i);
            
            if( (i&1) && mk[i+1] ) sol[(i+1)/2] = 'F';
            if( !(i&1) && mk[i-1] ) sol[i/2] = 'T';
        }
        return true;
    }
};
