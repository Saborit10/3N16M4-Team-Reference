/* Segment Tree con Persistencia
 - root guarda los indices de las raices de cada version.
 - en cada funcion se devuelven los indices de los nodos del subarbol
   correspondiente.
 - upt crea una nueva version del segment tree con el elemento b en 
   la posicion a.
 - qry responde el maximo en el rango [a, b] en la version ver. 
 - Tested on: https://codeforces.com/gym/101623/submission/62575565
**/
struct node{
    pair<int, int> val;
    int l, r;
};

const node null = {{0, 0}, 0, 0};

#define bck(X) (X).size()-1

struct segment_tree{
    vector<node> T;
    vector<int> root;
    
    segment_tree(){
        T.pb(null);
        root.pb(build());    
    }
    
    int build(int x=1, int xend=N){
        if( x==xend ){
            T.pb(null);
            return bck(T);    
        }
        int l = build(x, mid);    
        int r = build(mid+1, xend);    
        
        T.pb({max(T[l].val, T[r].val), l, r});
        return bck(T);
    }
    
    int update(int a, int b, int nod, int x=1, int xend=N){
        if( a<=x && xend<=a ){
            T.pb({{b, a}, 0, 0});
            return bck(T);
        }
        if( a < x || xend < a )
            return nod;
            
        int l = update(a, b, T[nod].l, x, mid);
        int r = update(a, b, T[nod].r, mid+1, xend);
        
        T.pb({max(T[l].val, T[r].val), l, r});
        return bck(T);
    }
    
    pair<int, int> query(int a, int b, int nod, int x=1, int xend=N){
        if( a<=x && xend<=b )
            return T[nod].val;
        if( b < x || xend < a )    
            return {-INF, 0};
            
        pair<int, int> l = query(a, b, T[nod].l, x, mid);
        pair<int, int> r = query(a, b, T[nod].r, mid+1, xend);
        
        return max(l, r);
    }
    
    void upt(int a, int b){
        root.pb(update(a, b, root.back()));    
    }
    
    pair<int, int> qry(int a, int b, int ver){
        return query(a, b, root[ver]);
    }
};

