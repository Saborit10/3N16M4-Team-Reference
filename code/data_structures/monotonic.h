/* Cola Monotona
 - Se comporta como una cola normal, pero devuelve el minimo de
   los elementos de tipo type que contiene (metodo top()).
 - El metodo pop(x) remueve el elemento del final de la cola, siempre
   que este tenga el indice x.  
 - Esta es la version para minimo. Para que top() devuelva el 
   maximo solo hay que cambiar el signo <= del ciclo while a >=.
 - Tiempo: O(n) amortizado. Memo: O(n).  
 - Tested on: expense USACO Silver Marzo 2007
OJO: Si la cola esta vacia, los metodos top() y pop() tendran un 
   UNDEFINED BEHAVIOR.
**/
typedef int type;

struct monotonic : deque<pair<type, int>>{
    void add(type val, int x){
        while( !empty() && val <= back().fr )
            pop_back();
        push_back({val, x});
    }

    type top(){ return front().fr; }

    void pop(int x){ if( front().sc == x ) pop_front(); }
};
