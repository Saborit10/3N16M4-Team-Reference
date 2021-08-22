/* Segment Tree Persistente
 - Esta implementacion hace point update y responde la suma en un
   intervalo.
 - El vector root contiene los ids de las raices de cada version del
   segment tree. La version 0 es la version del build y cada llamada a
   upt agrega una version nueva al segment tree.
 - Cada funcion que construye una nueva version (build, upt) retorna
   el id del nodo creado o del nodo correspondiente, de la version
   existente.
 - Tested on: https://www.spoj.com/problems/PSEGTREE/
 - Tiempo: build: O(N), upt: O(lg N), qry: O(lg N).
 - Memoria: O(N + Q * lg N).
**/
typedef int type;
#define fun(T, X) function< T (int, int, int)> (X) = [&](int x, int xend, int nod)
#define IZQ x, mid, T[nod].l
#define DER mid+1, xend, T[nod].r

struct node{
    type val;
    int l, r;
};

const node null = {0, -1, -1}; // Nodo con el val neutro de la op.

struct segment_tree{
    int N;
    vector<node> T;
    vector<int> root;
    
    segment_tree(int N, type* A): N(N){
        T.pb(null); 
        root.pb(build(A));
    }
    
    /* Agrega un nodo al arbol y retorna su id */
    int add(node x){ T.pb(x); return len(T) - 1; }
    
    int build(type* A){
        fun(int, build){
            if( x==xend )
                return add({A[x], -1, -1});
            
            int l = build(x, mid, -1);
            int r = build(mid+1, xend, -1);
            
            return add({T[l].val + T[r].val, l, r}); //Segun la op.
        };
        return build(1, N, -1);
    }
    
    void upt(int v, int a, int b){
        fun(int, upt){
            if( a<=x && xend<=a )
                return add({b, -1, -1}); // Depende del tipo de update
            if( a < x || xend < a )
                return nod;
                
            int l = upt(IZQ), r = upt(DER);
            return add({T[l].val + T[r].val, l, r}); // Segun la op.
        };
        root.pb(upt(1, N, root[v]));
    }
    
    type qry(int v, int a, int b){
        fun(type, qry){
            if( a<=x && xend<=b )
                return T[nod].val;
            if( b < x || xend < a )
                return null.val;
            
            return qry(IZQ) + qry(DER);  // Cambiar segun la operacion
        };
        return qry(1, N, root[v]);
    }
};
