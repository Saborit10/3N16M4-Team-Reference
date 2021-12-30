/* Diametro de un arbol 
 - max_dist guarda el resultado
**/
int diameter(int nod){
    mk[nod] = 1;
    int _max = 0;

    for(int i=0; i < G[nod].size(); i++){
        int nwn = G[nod][i].nod;
        if(mk[nwn])
           continue;
        int tmp = G[nod][i].cost + diameter(nwn);

        max_dist = max(max_dist, _max + tmp);
        _max = max(_max, tmp);
    }

    return _max;
}

