/* Algoritmo de Kruskal
 - Devuelve la lista de aristas que pertenecen al MST.
 - _cost es el tipo de el costo asociado a cada arista.
 - Tested on: https://codeforces.com/contest/1184/problem/E1
 - Dependencias: struct ds;
**/
typedef int _cost;

struct edge{
    int a, b;
    _cost c;
};

struct kruskal{
    ds S;
    vector<edge> E;
    
    kruskal(int cn): S(cn){}
    
    void add_edge(int a, int b, _cost c){
        E.pb({a, b, c});
    }
    
    vector<edge> mst(){
        vector<edge> ans;
         
        sort(all(E), [](edge& a, edge& b){
            return a.c < b.c;
        });
        
        for(auto e: E) if( S.join(e.a, e.b) )
            ans.pb(e);
        return ans;
    }
};
