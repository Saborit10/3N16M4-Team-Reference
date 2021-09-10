/* Segment Tree
 - segment_tree(): construye el segment tree.
 - upt(): actualiza la posicion a con el monoide t.
 - qry(): devuelve la respuesta en el rango [a, b]. 
 - Los constructores reciben o un arreglo de monoides, o un monoide,
   el cual se convierte en el valor de las hojas.
 
 Un Monoid es una clase que implementa los siguientes metodos:
 - Monoid(): Constructor que crea el elemento identidad de los
   monoides.
 - Monoid(const Monoid&, const Monoid&): constructor a partir de
   combinar dos monoides.

 - Tested on: https://codeforces.com/contest/1567/problem/E
*/
#define izq (nod<<1)
#define der (izq | 1)
#define self x, xend, nod
#define context int x, int xend, int nod
#define call_childs(X, Y...) X(x, mid, izq, Y), X(mid+1, xend, der, Y)
#define root 1, N, 1

template<class M>
struct segment_tree{
    int N;
    vector<M> T;
    
    explicit segment_tree(int N, M t): N(N), T(4*N){
        build(root, &t, NULL);
    }
    
    explicit segment_tree(int N, M* A): N(N), T(4*N){
        build(root, NULL, A);
    }
    
    void build(context, M* t, M* A){
        if( x==xend ){
            T[nod] = t ? *t : A[x];
            return;
        }
        call_childs(build, t, A);
        T[nod] = M(T[izq], T[der]);
    }
    
    void upt(context, int a, M& t){
        if( a < x || xend < a )
            return;
        if( a<=x && xend<=a )
            T[nod] = t;
        else{
            call_childs(upt, a, t);
            T[nod] = M(T[izq], T[der]);
        }
    }
    
    M qry(context, int a, int b){
        if( b < x || xend < a )
            return M();
        if( a<=x && xend<=b )
            return T[nod];
        return M(call_childs(qry, a, b));
    }
};
