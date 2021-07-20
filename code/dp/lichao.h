/* Li-Chao Tree
 - Son dados un conjunto de funciones tales que cada par puede 
   intersectarse a lo mas una vez. Dados valores de la variable 
   independiente, se responde rapidamente cual funcion del conjunto 
   se evalua de forma optima para tales valores.
 - Se mantine un segment tree, en el cual en cada vertice se guarda 
   una funcion, de tal forma que se garantiza que en el camino desde 
   la raiz hasta la hoja correspondiente al intervalo [a, a], hay un
   nodo con la funcion que es optima al ser evaluada con el valor a. 
 - Tiempo: O(lg n). Memoria: O(n).
 - Tested on: acquire USACO Gold 2008 Marzo
**/
struct line{
    int64 m, b;
    
    int64 eval(int64 x){
        return m*x + b;    
    }    
};

struct lichao{
    vector<line> T;
    
    lichao(): T(4*MX, {0, INF}){}
    
    /* Not Fully Tested */
    void update(int a, int b, line p, int x=0, int xend=N,int nod=1){
        if( a<=x && xend<=b ){
            bool l = p.eval(x) < T[nod].eval(x);    
            bool m = p.eval(mid+1) < T[nod].eval(mid+1);
            
            if( m ) swap(T[nod], p);
            
            if( x==xend ) return;
            
            if( l != m ) update(a, b, p, x, mid, izq);
            else update(a, b, p, mid+1, xend, der);
            return;
        }
        if( b < x || xend < a )
            return;
        update(a, b, p, x, mid, izq);
        update(a, b, p, mid+1, xend, der);
    }

    void add(line p, int x=1, int xend=M, int nod=1){
        bool l = p.eval(x) < T[nod].eval(x);    
        bool m = p.eval(mid+1) < T[nod].eval(mid+1);    
        
        if( m ) swap(T[nod], p);
        
        if( x==xend )
            return;
        if( l != m )
            add(p, x, mid, izq);
        else 
            add(p, mid+1, xend, der);    
    }
    
    int64 query(int a, int x=1, int xend=M, int nod=1){
        if( x==xend ) 
            return T[nod].eval(a);
        if( a<=mid )
            return min(T[nod].eval(a), query(a, x, mid, izq));
        else 
            return min(T[nod].eval(a), query(a, mid+1, xend, der));        
    }
}; 
