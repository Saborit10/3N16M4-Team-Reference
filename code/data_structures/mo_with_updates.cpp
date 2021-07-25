/* Algoritmo de Mo con Updates
 - Se necesita una estructura interval con los siguientes metodos:
    * interval(): inicializa la estructura
    * add(): agrega un elemento al intervalo.
    * era(): elimina un elemento del intervalo.
    * query(): la respuesta actual para el intervalo.
 - El arreglo A es el de los elementos dados en el problema.
 - Tiempo: O().
**/

struct mo{
    struct queri{
        int l, r, t, id;
    };
    struct updati{
        int pos, val, old;
    };
    
    int N;
    int A[MX];
    vector<updati> upt;
    vector<queri> qry;
    interval S;
    
    // Agrega una query a la estructura, en el rango [a, b] y con el
    // indice id.
    void add_qry(int a, int b, int id){
        qry.pb({a, b, (int)upt.size() - 1, id});
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
            
            ans[q.id - 1] = S.query();
        }
        return ans;
    }
};
