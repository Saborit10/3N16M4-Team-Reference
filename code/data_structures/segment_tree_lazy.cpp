/* Segment Tree con Lazy Propagation
 - segment_tree(): construye el segment tree.
 - upt(): actualiza el rango [a, b] con la funcion f.
 - pnt(): hce una point update en a, con el monoide t.
 - qry(): devuelve la respuesta en el rango [a, b]. 
 - La query devuelve elementos de tipo monoide.
 - Las updates son modeladas como funciones que reciben un monoide y
   devuelven otro.
 - Los constructores reciben o un arreglo de monoides, o un monoide,
   el cual se convierte en el valor de las hojas.
 
 Un Monoid es una clase que implementa los siguientes metodos:
 - Monoid(): Constructor que crea el elemento identidad de los
   monoides.
 - Monoid(const Monoid&, const Monoid&): constructor a partir de
   combinar dos monoides.

 Una Function es una clase que implementa los siguientes metodos:
 - Function(): Constructor que crea la funcion identidad.
 - Function(const Function& f1, const Function& f2): constructor que
   crea una funcion a partir de la composicion de las funciones f1
   y f2.
 - bool ident() const: Devuelve true si la funcion es la funcion
   identidad.
 - Monoid operator()(const Monoid&): Es la definicion de la funcion.
 
 - Tested on: https://codeforces.com/contest/115/problem/E
*/

#define izq (nod<<1)
#define der (izq | 1)
#define self x, xend, nod
#define call_childs(X, Y...) X(x, mid, izq, Y), X(mid+1, xend, der, Y)
#define context int x, int xend, int nod
#define root 1, N, 1

template<class M, class F>
struct segment_tree{
    int N;
    vector<M> T;
    vector<F> mk;
    
    explicit segment_tree(int N, M t): N(N), T(4*N), mk(4*N){
        build(root, &t, NULL);
    }
    
    explicit segment_tree(int N, M* A): N(N), T(4*N), mk(4*N){
        build(root, NULL, A);
    }
    
    void build(context, M* t, M* A){
        mk[nod] = F();
            
        if( x==xend ){
            T[nod] = t ? *t : A[x];
            return;
        }
        call_childs(build, t, A);
        T[nod] = M(T[izq], T[der]);
    }
    
    void lazy(context){
        if( !mk[nod].ident() ){
            T[nod] = mk[nod](T[nod]);
            
            if( x < xend ){
                mk[izq] = F(mk[nod], mk[izq]);
                mk[der] = F(mk[nod], mk[der]);
            }
            mk[nod] = F();
        }
    }
    
    void upt(context, int a, int b, const F& f){
        if( b < x || xend < a )
            lazy(self);
        else if( a<=x && xend<=b ){
            mk[nod] = F(mk[nod], f);
            lazy(self);
        }
        else{
            lazy(self);
            call_childs(upt, a, b, f);
            T[nod] = M(T[izq], T[der]);
        }
    }
    
    void pnt(context, int a, M t){
        if( a < x || xend < a )
            lazy(self);
        else if( a<=x && xend<=a )
            T[nod] = t;
        else{
            lazy(self);
            call_childs(pnt, a, t);
            T[nod] = M(T[izq], T[der]);
        }
    }
    
    M qry(context, int a, int b){
        if( b < x || xend < a )
            return M();
        lazy(self);
            
        if( a<=x && xend<=b )
            return T[nod];
        return M(call_childs(qry, a, b));
    }
};
