/* Algoritmo de Mo con Updates
 - Se necesita completar la estructura interval;
 - Valores que debe tener la esturctura mo:
    * El numero N: El largo del arreglo.
	* El arreglo A: los elementos dados en el problema.
 - Tiempo: O(Q * N^(2/3)).
**/

struct interval{
	// Inicializa la estructura. Complejidad Maxima: O(Q * N^(2/3)).
	interval();
	
	// Agrega un elemento al intervalo. Complejidad Maxima: O(1).
	void add(int x);
	
	// Elimina un elemento del intervalo. Complejidad Maxima: O(1).
	void era(int x);
	
	// La respuesta para el intervalo. Complejidad Maxima: O(N^(2/3)).
	int query(); 		
};

struct mo{
    struct queri{
        int l, r, t, id;
    };
    struct updati{
        int pos, val, old;
    };
    
    int N, t = 0;
    int A[MX];
    vector<updati> upt;
    vector<queri> qry;
    interval S;
    
    // Agrega una query a la estructura, en el rango [a, b].
    void add_qry(int a, int b){
        qry.pb({a, b, (int)upt.size() - 1, t++});
    }
    
    // Agrega un update a la estructura, en la posicion pos, se cambial
    // al elemento old por el elemento val. Ambos de pasan al metodo.
    void add_upt(int pos, int val, int old){
        upt.pb({pos, val, old});
    }
    
    // Resuelve el problema. Retorna un vector con las respuestas a las
    // queries, en el orden correcto.
    vector<int> solve(){
        int sq = cbrt(2ll * N * N);
        vector<int> ans(len(qry));

        sort(all(qry), [this, sq](queri& a, queri& b){
            if( a.l / sq != b.l / sq ) return a.l / sq < b.l / sq;
            if( a.r / sq != b.r / sq ) return a.r / sq < b.r / sq;
            return a.t / sq < b.t / sq;
        });
        
        int l = 1, r = 0, t = -1;
        for(auto q: qry){
            while( t < q.t ){
                int p = upt[++t].pos;
                
                if( l<=p && p<=r ) S.era(A[p]);
                A[p] = upt[t].val;
                if( l<=p && p<=r ) S.add(A[p]);
            }
            while( t > q.t ){
                int p = upt[t].pos;
                
                if( l<=p && p<=r ) S.era(A[p]);
                A[ upt[t].pos ] = upt[t].old;
                if( l<=p && p<=r ) S.add(A[p]);
                
                t--;
            }
            
            while( l < q.l ) S.era(A[l++]);
            while( l > q.l ) S.add(A[--l]);
            while( r < q.r ) S.add(A[++r]);
            while( r > q.r ) S.era(A[r--]);
            
            ans[q.id] = S.query();
        }
        return ans;
    }
};
