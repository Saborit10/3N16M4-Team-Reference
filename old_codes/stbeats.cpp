/* Segment Tree Beats
 - Maneja operaciones de la forma
 - update(a, b, c) -> Para i=[a, b] hacer A[i] = min(A[i], c).
 - query(a, b)     -> Calcular la suma de A[i] para i=[a, b]. 
 - Para cada nodo del segment tree se guarda la suma del intervalo, 
   el maximo, la cantidad de veces que este aparece, y el segundo 
   maximo estricto.
 - Se actualiza un rango solamente si second_max < c < max.
 - Tiempo: O(n log n). 
**/
struct node{
    int64 val;
    int m, m2, cnt;
    
    node operator & (const node &p){
        node ans;
        
        ans.val = val + p.val;
        ans.m2 = max(m2, p.m2);
        
        if( m > p.m ){ 
            ans.m = m, ans.cnt = cnt; 
            ans.m2 = max(ans.m2, p.m);
        }    
        else if( m < p.m ){ 
            ans.m = p.m, ans.cnt = p.cnt; 
            ans.m2 = max(ans.m2, m);
        }    
        else
            ans.m = m, ans.cnt = cnt + p.cnt; 
        
        return ans;
    }
    
    void update(int x){
        if( m > x ){
            val -= (int64)cnt * (m - x);
            m = x;
        }    
    }
};

struct stbeats{
    vector<node> T;
    vector<int> mk;
    
    stbeats(): T(4*MX), mk(4*MX, INF){}
    
    node build(int x=1, int xend=N, int nod=1){
        if( x == xend )
            return T[nod] = {A[x], A[x], -INF, 1};
        return T[nod] = build(x, mid, izq) & build(mid+1, xend, der);
    }
    
    void lazy(int x, int xend, int nod){
        T[izq].update(mk[nod]);    
        T[der].update(mk[nod]);
        
        mk[izq] = min(mk[izq], mk[nod]);    
        mk[der] = min(mk[der], mk[nod]);
        mk[nod] = INF;
    }
    
    node update(int a, int b, int c, int x=1, int xend=N, int nod=1){
        if( x < xend && mk[nod] < INF )
            lazy(x, xend, nod);
            
        if( T[nod].m <= c || b < x || xend < a )
            return T[nod];
        if( T[nod].m2 < c && a<=x && xend<=b ){
            mk[nod] = c;
            T[nod].update(c);
            return T[nod];    
        }
        
        return T[nod] = update(a, b, c, x, mid, izq) & 
                        update(a, b, c, mid+1, xend, der);    
    }
    
    node query(int a, int b, int x=1, int xend=N, int nod=1){
        if( x < xend && mk[nod] < INF )
            lazy(x, xend, nod);
            
        if( a<=x && xend<=b )
            return T[nod];
        if( b < x || xend < a )
            return {0, -INF, -INF, 0};
            
        return query(a, b, x, mid, izq) & 
               query(a, b, mid+1, xend, der);    
    }
};
