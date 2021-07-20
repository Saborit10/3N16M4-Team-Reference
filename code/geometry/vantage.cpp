/* Vantage-PointTree 
 - Arbol metrico para encontrar los puntos mas ceranos a uno dado.
 - El ejemplo usa distancia euclidiana, pero (en teoria) funciona con
   todas las metricas.
 - Tiempo Esperado: Build: O(n lg n). Query: O(lg n). 
*/
typedef double type;

struct pt{
    type x, y;
    
    bool operator < (const pt& p)const{
        return x != p.x ? x < p.x : y < p.y;    
    }
};

struct node{
    pt p;
    type th;
    node *l, *r;
};

typedef node* pnod;

struct vantage{
    pnod root;
    vector<pair<type, pt>> v;
    
    /* Solo se usa con kthnn() */
    priority_queue<pair<type, pnod>> Q;
    
    /* Solo se usa con nearest(). Inicializar best.fr a INF. Al 
       final, en best.sc esta el punto mas cercano a p, y en best.fr
       la distancia minima al cuadrado.                            */
    pair<type, pt> best;
    
    vantage(vector<pt>& points){
        for(auto i: points)
            v.pb({0, i});
        root = build(0, v.size());
    }
    
    pnod build(int x, int xend){
        if( x==xend ) return NULL;
        
        swap(v[x], v[ x + rand() % (xend-x) ]);
        pt p = v[x++].sc;
        
        if( x==xend ) return new node({p});
        
        for(int i=x; i < xend; i++)
            v[i].fr = dist2(p, v[i].sc);
        nth_element(v.begin() + x, v.begin() + mid, v.begin() +xend);
        return new node({p, sqrt(v[mid].fr), build(x, mid), 
                                                  build(mid, xend)});
    }
    
    void kthnn(pnod t, pt p, int k){
        if( !t ) return;
        
        type d = sqrt(dist2(p, t->p));
        
        if( (int)Q.size() < k ) Q.push({d, t});
        else if( Q.top().fr > d ){
            Q.pop();
            Q.push({d, t});    
        }
        
        if( !t->l && !t->r ) return;
        
        if( d < t->th ){
            kthnn(t->l, p, k);
            if( (int)Q.size() < k || t->th - d <= Q.top().fr )
                kthnn(t->r, p, k);
        }
        else{
            kthnn(t->r, p, k);
            if( (int)Q.size() < k || d - t->th <= Q.top().fr )
                kthnn(t->l, p, k);
        }
    }
    
    /* Encuentra los k puntos mas cercanos a p dentro del conjunto */
    vector<pt> kthnn(pt p, int k){
        vector<pt> ans;
        kthnn(root, p, k);
        
        for(; !Q.empty(); Q.pop())
            ans.pb(Q.top().sc->p);
        reverse(all(ans));
        return ans;
    }
    
    /* Encuentra el punto mas cercano a p dentro del conjunto */
    void nearest(pnod t, pt p){
        if( !t ) return;
        
        type d = sqrt(dist2(p, t->p));
        
        if( best.fr > d )
            best = {d, t->p};
        
        if( !t->l && !t->r ) return;
        
        if( d < t->th ){
            nearest(t->l, p);
            if( t->th - d <= best.fr )
                nearest(t->r, p);
        }
        else{
            nearest(t->r, p);
            if( d - t->th <= best.fr )
                nearest(t->l, p);
        }
    }
    
    /* Funcion Debug */
    void print(pnod p){
        if( !p ) return;
        
        printf("p = (%.2lf, %.2lf), th = %.2lf",
            p->p.x, p->p.y, p->th
        );
        
        if( p->l )
            printf(", l = (%.2lf, %.2lf)", p->l->p.x, p->l->p.y);
        if( p->r )
            printf(", r = (%.2lf, %.2lf)", p->r->p.x, p->r->p.y);
        printf("\n");
        print(p->l); print(p->r);
    } 
};
