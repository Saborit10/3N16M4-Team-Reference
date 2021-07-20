/* Algoritmo de Prim
**/
struct par{
    int nwn, cost;
    
    bool operator < (const par &p)const{
        return cost > p.cost;    
    }
};
    
/* Inside the main */
int64 sol = 0;
    
for(Q.push({1, 0}); !Q.empty(); ){
    int nod = Q.top().nwn;
        
    if( mk[nod] ){ 
        Q.pop();
        continue;    
    }
    
    mk[nod] = true;
    sol += Q.top().cost;
    Q.pop();
    
    for(auto i: G[nod])
        Q.push({i.nwn, i.cost});    
}
