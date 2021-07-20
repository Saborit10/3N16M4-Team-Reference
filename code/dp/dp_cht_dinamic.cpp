/* Convex Hull Trick Dinamico
 - Para C++14 o superior:
  - Para minimo, cambiar los signos '<' por '>' en las lineas:
    * return m < p.m;
    * x->l = x->b > y->b ? INF : -INF; 
 - Tested on: https://www.codechef.com/JAN16/problems/CYCLRACE
 
 - Para compilar en C++11 se una la clase line correspondiente y deben 
   cambiarse las sgtes lineas en la clase cht:
   - [adicionar] typedef multiset<line>::iterator iterator; 
   - struct cht : public multiset<line>
   - auto li = lower_bound({0, 0, (long double)x, 1}); 
 - Tiempo: add() y query(): O(lg n), con constantes elevadas.
 - Memoria: O(n)
 - Tested on: https://icpcarchive.ecs.baylor.edu/ (...) problem=3134  
**/
 
//C++11
struct line{
    mutable int64 m, b;
    mutable long double l;
    mutable bool cmp_by_limit;
    
    bool operator < (const line &p)const{
        return p.cmp_by_limit ? l < p.l : m < p.m;    
    }
      
    inline int64 eval(int64 x)const{ return m*x + b; } 
};

// C++14
struct line{
    mutable int64 m, b;
    mutable long double l;
    
    bool operator < (const line &p)const{ return m < p.m; }
    bool operator < (int64 x)const{ return l < x; }
    
    inline int64 eval(int64 x)const{ return m * x + b; } 
};

struct cht : public multiset<line, less<>>{
    bool sect(iterator x, iterator y){
        if( y == end() ) { x->l = INF; return false; } 
        
        if( x->m == y->m ) 
            x->l = x->b > y->b ? INF : -INF;
        else 
            x->l = (long double)(x->b - y->b) / (y->m - x->m);
        
        return x->l >= y->l; 
    }
    
    void add(int64 m, int64 b){
        auto r = insert({m, b, 0}), it = r++, l = it;
        
        while( sect(it, r) ) r = erase(r);
        
        if( l != begin() && sect(--l, it) )
            sect(l, it = erase(it));
            
        while( (it = l) != begin() && (--l)->l >= it->l )
            sect(l, erase(it));
    }
    
    int64 query(int64 x){ 
        auto li = *lower_bound(x);
        return li.eval(x); 
    }
}; 
