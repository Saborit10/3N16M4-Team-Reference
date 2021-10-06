/* Algoritmo de Mo con Updates
 - Se necesita completar la estructura interval;
 - T es el tipo de datos del arreglo y R el de la respuesta de las
   qrys de la estructura mo.
 - El tipo de retorno del metodo query en la estructura interval debe
   ser R.
 - El constructor del mo recibe la cantidad de elementos en el arreglo
   (1-indexed) y un puntero al arreglo.
 - El metodo solve solo puede ser llamado una vez por instancia.
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

template<class T, class R>
struct mo{
    struct queri{
        int l, r, t, id;
    };
    struct updati{
        int pos;
        T val, old;
    };
    
    int N, t;
    vector<T> A;
    vector<updati> upt;
    vector<queri> qry;
    interval S;
    
    mo(int N, T* aa): N(N), t(0), A(1){
		for(int i=1; i<=N; i++)
			A.pb(aa[i]);
	}
    
    // Agrega una query a la estructura, en el rango [a, b].
    void add_qry(int a, int b){
        qry.pb({a, b, len(upt) - 1, t++});
    }
    
    // Agrega un update a la estructura, en la posicion pos, se cambial
    // al elemento old por el elemento val. Ambos de pasan al metodo.
    void add_upt(int pos, T val){
        upt.pb({pos, val, A[pos]});
        A[pos] = val;
    }
    
    // Resuelve el problema. Retorna un vector con las respuestas a las
    // queries, en el orden correcto.
    vector<R> solve(){
        int sq = cbrt(2ll * N * N);
        vector<R> ans(len(qry));

        sort(all(qry), [this, sq](queri& a, queri& b){
            if( a.l / sq != b.l / sq ) return a.l / sq < b.l / sq;
            if( a.r / sq != b.r / sq ) return a.r / sq < b.r / sq;
            return a.t / sq < b.t / sq;
        });
        
        for(int i=len(upt)-1; ~i; i--)
			A[ upt[i].pos ] = upt[i].old;
        
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
