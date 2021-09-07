/* Segment Tree con Lazy Propagation 
 TIPOS:
 - type: es el tipo de los elementos del arreglo pasado al constructor
   del segment_tree.
 - mkt: es el tipo de la marca del segment tree.

 ESTRUCTURA NODE:
 - un constructor que reciba un elemento type y construya un node que
   represente un rango de largo uno.
 - act(): retorna true si el nodo tiene marca activa.
 - comb(): dado el nodo padre p, mezcla la marca del nodo actual con
   la de p.
 - off(): desactiva la marca del nodo.
 - apply(): Calcula el nuevo valor del nodo a partir de la marca v.
 - posee el operador + sobrecrgado para combinar dos nodos.

 * Los parametros x, xend y nod se pueden agregar a los argumentos de
   estas funciones, de ser necesarios para los calculos. 
 
 NODO NULL: 
 - Es un nodo que es neutro con respecto a la operacion + definida en
   la propia estructura.
**/

#define fun(T, X) function<T(int, int, int)> X = [&](int x, int xend, int nod)
#define self x, xend, nod
#define izq x, mid, nod*2
#define der mid+1, xend, nod*2 + 1

typedef int type;  // Cambiar estos tipos segun se requiera.
typedef int mkt;

struct node{
    node(type x) 
    
    node operator + (node p){
    
    }
    
    inline bool act()
    inline void comb(node& p)
    inline void off()
    inline void apply(int x, int xend, int nod, mkt v)
};

const node null(  );  // Neutro de la operacion mezcla

struct segment_tree{
    int N;
    node T[4*MX];
    
    segment_tree(int N, type* A): N(N){
        fun(node, build){
            if( x==xend )
                return T[nod] = node(A[x]);
            return T[nod] = build(izq) + build(der);
        };
        build(1, N, 1);
    }
    
    fun(void, lazy){
        int l = nod*2, r = 2*nod+1;
        
        T[l].apply(izq, T[nod].mk);
        T[r].apply(der, T[nod].mk);
        T[l].comb(T[nod]);
        T[r].comb(T[nod]);
        T[nod].off();
    };
    
    void upt(int a, int b, mkt c){
        fun(node, upt){
            if( x < xend && T[nod].act() )
                lazy(self);
            if( a<=x && xend<=b ){
                T[nod].mk = c;
                T[nod].apply(self, c);
                return T[nod];
            }
            if( b < x || xend < a )
                return T[nod];
            return T[nod] = upt(izq) + upt(der);
        };
        upt(1, N, 1);
    }
    
    node qry(int a, int b){
        fun(node, qry){
            if( x < xend && T[nod].act() )
                lazy(self);
            if( a<=x && xend<=b )
                return T[nod];
            if( b < x || xend < a )
                return null;
            return qry(izq) + qry(der);
        };
        return qry(1, N, 1);
    }
};
