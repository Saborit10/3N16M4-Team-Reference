/* Convex Hull Trick
 - Responde cual funcion, de entre un conjunto de funciones lineales, 
   produce un valor minimo, dado un valor para la variable 
   independiente.
 - La clase line contiene la pendiente de la recta(m) y el intersecto
   con el eje y (b); ademas contine el valor de x mas a la derecha 
   para el cual la funcion todavia da el valor minimo (limit). El 
   limite de la ultima linea en la pila es INF.    
 - El operador & de la clase line retorna el valor de x del punto de
   interseccion entre dos rectas.
 - La funcion prune devuelve verdadero si la recta del medio debe ser 
   removida del conjunto.
 - La funcion addf inserta una recta al frente de la lista. 
 - La funcion addb inserta una recta al final de la lista.
 - Usese addf y addb segun si se quiere maximo o minimo; y el orden 
   de procesamiento de las rectas:
         
           DECRECIENTE     CRECIENTE
   MAXIMO     addf            addb               
   MINIMO     addb            addf
  
 - La funcion query, dado un valor de x, devuelve el maximo valor de
   y que puede dar una funcion dentro del conjunto.
 - Modifiquese la funcion query dependiendo de si se usa addf o addb
 - Tiempo: add(): O(1) amortizado, query() O(lg n).
 - Memoria: O(n)
 - Tested on: acquire USACO Gold 2008 Marzo
**/
struct line{
    int64 m, b;
    long double limit;

    long double operator & (line &p){
        return (long double)(p.b - b) / (m - p.m);
    }
    int64 eval(int64 x){ return m * x + b; }
};

inline bool prune(line a, line b, line c){ 
    if( b.m == c.m )
        return c.b < b.b; // para max cambiar el simbolo por >
    return (b & c) < (a & c); 
}

struct cht{
    deque<line> hull;

    void addf(int64 m, int64 b){
        line l = {m, b, -INF};

        while( hull.size() > 1 && prune(l, hull[0], hull[1]))
            hull.pop_front();

        if( hull.size() )
            hull.front().limit = (l & hull.front());
        hull.push_front(l);
    }
    
    void addb(int64 m, int64 b){
        line l = {m, b, INF};
        
        while( hull.size() > 1 && 
                          prune(hull[hull.size()-2], hull.back(), l))
            hull.pop_back();

        if( hull.size() )
            hull.back().limit = (l & hull.back());
        hull.push_back(l);
    }

    int64 query(int64 x){
        int p = hull.size();

        for(int i=log2(hull.size()); ~i; i--)
            if( p-(1<<i)>=0 && hull[p-(1<<i)].limit > x )
                p -= (1<<i);

        //Working at front
        return hull[p-1].eval(x);

        //Working at back
        return hull[p].eval(x);
    }
};
