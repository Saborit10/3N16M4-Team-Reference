/* Segment Tree
 - ST sencillo, con point update y query en rango.
 - Al constructor se le pasa el indice del ultimo elemento y el
   arreglo. El tipo de este arreglo puede cambiar.
 - Para nodos de tipos primitivos, comentar la estruct node y hacer
   typedef int node;
 - Para tipos no primitivos dejar declarada la estructura node.
 - Cambiar las lineas donde se asigna a T[nod] un node, segun convenga.
 - Para indexar desde cero, cambiar (1, N, 1) por (0, N, 1).
 - Tested on: https://codeforces.com/contest/1567/problem/e
**/

struct node{
    
    node operator + (node p){
        node ans;
        
        //Merge
        return node;
    }
};

node null(  ); // Elemento neutro del merge de dos nodos.

#define fun(T, X) function<T(int, int, int)> X = [&](int x, int xend, int nod)
#define izq x, mid, nod*2
#define der mid+1, xend, nod*2+1

struct segment_tree{
    int N;
    node T[4*MX];
    
    segment_tree(){}
    segment_tree(int N, int *A): N(N){
        fun(node, build){
            if( x==xend )
                return T[nod] = node(A[x]); // Cambiar segun convenga.
            return T[nod] = build(izq) + build(der);
        };
        build(1, N, 1);
    }
    
    void upt(int a, int b){
        fun(node, upt){
            if( a<=x && xend<=a )
                return T[nod] = node(b);   // Cambiar segun convenga.
            if( a < x || xend < a )
                return T[nod];
            return T[nod] = upt(izq) + upt(der);
        };
        upt(1, N, 1);
    }
    
    node qry(int a, int b){
        fun(node, qry){
            if( a<=x && xend<=b ){
                return T[nod];
            }
            if( b < x || xend < a )
                return null;
            return qry(izq) + qry(der);
        };
        return qry(1, N, 1);
    }
};
