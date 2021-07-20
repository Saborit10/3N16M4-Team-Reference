/* Quadtree 
 - Maneja queries en dos dimensiones.
 - Cambiar el neutro, el tipo del valor y la funcion de mezcla 
   segun se requiera. 
 - Se define el rectangulo de la forma
   
   o--c--o
   |     |
   a     b
   |     |
   o--d--o
  
 - Un quadtree de valores enteros, cuya mayor dimension es n, tiene 
   profundidad de O(log n), O(n * log n) nodos,
   y se construye en O(n * log n).  
 - Tested on: cornfld USACO Green Marzo 2003. 
**/ 
#define midx ((c+d) >> 1)
#define midy ((a+b) >> 1)
#define NEUTRO -INF

struct qtree{
    int a, b, c, d, val;
    qtree* P[4]; 
    
    qtree(){}
    qtree(int a, int b, int c, int d): a(a), b(b), c(c), d(d){
        P[0] = P[1] = P[2] = P[3] = NULL;
        val = NEUTRO;
    }
    
    void split(){
        P[0] = new qtree(a, midy, c, midx);
        
        if( a < b ) P[1] = new qtree(midy+1, b, c, midx);
        if( c < d ) P[2] = new qtree(a, midy, midx+1, d);
        if( a< b && c < d )
            P[3] = new qtree(midy+1, b, midx+1, d);
    }
    
    void update(int aa, int bb, int cc, int dd, int x){
        if( aa<=a && b<=bb && cc<=c && d<=dd ){
            val = x; 
            return; 
        }
        if( bb < a || b < aa || dd < c || d < cc )
            return;
        
        if( !P[0] ) split();
        
        for(int i=0; i < 4; i++) if( P[i] ){
            P[i]->update(aa, bb, cc, dd, x);
            val = max(val, P[i]->val);
        }
    }
    
    int query(int aa, int bb, int cc, int dd){
        if( aa<=a && b<=bb && cc<=c && d<=dd )
            return val;     
        if( bb < a || b < aa || dd < c || d < cc )
            return NEUTRO;
        
        int ans = NEUTRO;
        for(int i=0; i < 4; i++) if( P[i] )
            ans = max(ans, P[i]->query(aa, bb, cc, dd));
        
        return ans;
    }
};
