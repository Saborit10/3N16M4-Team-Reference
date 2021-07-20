/* Treap
 - Treap simple que calcula el minimo en un intervalo con
   actualizaciones en rangos (lazy propagation).
 - type es el tipo de datos de la funcion objetivo.
 - Dentro del main llamar a srand(time(NULL)).
 - Al declarar el puntero al treap, este deber ser puesto a NULL.
 - Para obtener la version sin lazy, eliminar todas las declaraciones
   y usos de mk, asi como las llamadas a lazy(t) y su declaracion. 
 - Tiempo Esperado: O(lg n) para cada operacion, Memoria: O(n).
 - Tested on: 
*/
typedef int type;

struct node{
    int p, sz;
    type val, mi;
    node *l, *r;
    
    type mk;
    
    node(type v): 
        p(rand()), sz(1), mk(0), l(NULL), r(NULL)
    {
        val = mi = v;
        // OJO: Inicializar TODOS los campos, por ejemplo maximo, 
        // minimo, size, marcas para el lazy, etc.    
    }
};

typedef node* pnod;

namespace treap{
    /* Wrappers para funciones objetivo */
    inline int sz(pnod t){ return t ? t->sz : 0; }
    inline type mi(pnod t){ return t ? t->mi : INF; }
    
    /* Actualiza los datos de un nodo a partir de los de sus hijos */
    void upt(pnod t){
        if( !t ) return;
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->mi = min({t->val, mi(t->l), mi(t->r)});
    }
    
    /* Propaga las operaciones pendientes 
     * Se efectua la operacion pendiente en cada hijo SI EXISTE (se 
     * actualiza el valor del nodo y la funcion objetivo) y se mezcla
     * la marca del padre con la del hijo. Luego se desmarca al padre. 
    **/
    void lazy(pnod t){
        if( !t || t->mk == 0 ) return;
        
        if( t->l ){
            t->l->val += t->mk;  
            t->l->mi += t->mk;
            t->l->mk += t->mk;
        }
        if( t->r ){
            t->r->val += t->mk;
            t->r->mi += t->mk;
            t->r->mk += t->mk;
        }
        t->mk = 0;
    }
    
    /* Divide a t en dos treaps L = t[1..p] y  R = t[p+1..N] */
    void split(pnod t, pnod& L, pnod& R, int p, int x=1){
        if( !t ) return void(L = R = NULL);
        lazy(t);
        
        int m = x + sz(t->l);
        if( m<=p ) split(t->r, t->r, R, p, m+1), L = t;
        else split(t->l, L, t->l, p, x), R = t;
        upt(t);
    }
    
    /* Mezcla dos treap L y R en un treap t = LR (concatenados) */
    void merge(pnod& t, pnod L, pnod R){
        lazy(L), lazy(R);
        if( !L || !R ) return void(t = L ? L : R);
        
        if( L->p > R->p ) merge(L->r, L->r, R), t = L;
        else merge(R->l, L, R->l), t = R;
        upt(t);
    }
    
    /* Inserta un elemento v entre las posiciones p-1 y p */
    void insert(pnod& t, type v, int p){
        pnod L, M, R;
        split(t, L, R, p-1);
        M = new node(v);
        merge(M, M, R);
        merge(t, L, M);
    }
    
    /* Actualiza el rango [a, b] */
    void update(pnod t, int a, int b, type c){
        pnod L, M, R;
        split(t, L, M, a-1);
        split(M, M, R, b-a+1);
        
        M->mk += c;        // Se mezclan las marcas y se actualizan 
        M->val += c;       // la funcion objetivo y el valor del nodo
        M->mi += c;
        
        merge(M, M, R);
        merge(t, L, M);
    }
    
    /* Calcula la respuesta para el rango [a, b] */
    type query(pnod t, int a, int b){
        pnod L, M, R;
        split(t, L, M, a-1);
        split(M, M, R, b-a+1);
        
        type ans = M->mi;
        
        merge(M, M, R);
        merge(t, L, M);
        return ans;
    }
    
    /* ~~Util para DEBUG: Convierte el treap a un vector */
    void to_vector(pnod t, vector<type>& vec){
        if( !t ) return;
        lazy(t);
        
        to_vector(t->l, vec);
        vec.pb(t->val);
        to_vector(t->r, vec);
    }
    
    /* ~~Util para DEBUG: Imprime el treap en estructura de arbol */
    void print(pnod t){
        if( !t ) return;
        lazy(t);
        
        printf("%d[%d][%d], ", t->val, t->mi, t->mk);
        if( t->l )
            printf("L = %d, ", t->l->val);
        if( t->r )
            printf("R = %d", t->r->val); 
        printf("\n");
        
        print(t->l);
        print(t->r);
    }
};
