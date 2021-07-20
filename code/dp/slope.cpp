/* Slope Optimizer
 - Dado un conjunto de puntos S, dados ordenados por las x, se
   responde la query: dado un punto p (con x menor que cualquiera de
   un punto del conjunto S) cual es el id del punto en S que define
   con p, la recta con menor(mayor) pendiente.
 - addb(int x, int y, int id): Agrega un punto al conjunto, con 
   identificador igual a id, que tenga mayor x que cualquiera en S.   
 - addf(int x, int y, int id): Agrega un punto al conjunto, con 
   identificador igual a id, que tenga menor x que cualquiera en S.   
 - Para minimo (codigo dado), se construye un lower hull. 
 - Para maximo se construye el upper hull. Cambiar las lineas 
   "orient(..) < EPS" por "orient > -EPS" y la linea 
   "slope(..) - slope(..) < EPS" por "slope(..) - slope(..) > -EPS".
 - Tested on: https://codeforces.com/contest/1300/problem/E
 - [Pend: Probar para puntos con coordenadas flotantes.] 
*/
typedef int64 type;
#define sec(X) (X)[1]
#define pen(X) (X)[(X).size()-2]

type orient(pt a, pt b, pt c){ return (b - a) ^ (c - a); }

struct convex{
    deque<pair<pt, int>> hull;
    
    long double slope(type x, type y, int p){
        return (long double)(y - hull[p].fr.y) / (x - hull[p].fr.x);
    }
    
    void addf(type x, type y, int id){
        pt p = {x, y};
        while( hull.size() > 1 &&  
            orient(p, hull[0].fr, sec(hull).fr) < EPS )
            hull.pop_front();
        hull.push_front({p, id});    
    }
    
    void addb(type x, type y, int id){
        pt p = {x, y};
        while( hull.size() > 1 && 
            orient(pen(hull).fr, hull.back().fr, p) < EPS )
            hull.pop_back();
        hull.pb({p, id});    
    }

    int query(type x, type y){
        int p = 0;
        for(int n=hull.size(), i=log2(n); ~i; i--){
            if( p+(1<<i) < n && 
                slope(x, y, p+(1<<i))-slope(x, y, p+(1<<i)-1) < EPS )
                p += (1<<i);    
        }
        return hull[p].sc;
    }
};
