/* Algoritmo de Kruskal
**/
  
struct edge{
    int nod, nwn, cost;
    
    bool operator < (const edge &p)const{
        return cost < p.cost;    
    }
};

/* Encuentra el conjunto de nod */
int fset(int nod){
    if( nod != SET[nod] )
        return SET[nod] = fset(SET[nod]);
    return nod;    
}

/* Retorna verdadero si hubo que unir los conjuntos */
bool join(int nod, int nwn){
    nod = fset(nod), nwn = fset(nwn);
    
    if( nod == nwn ) return false;
    if( nod < nwn ) swap(nod, nwn);
    
    SET[nod] = nwn;    
    return true;
}

/* Inside the main */
for(int i=1; i<=cn; i++)
    SET[i] = i;
