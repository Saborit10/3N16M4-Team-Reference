/* Diametro del Arbol Construido
 - Halla el diametro de un arbol y construye un vector (path) con 
   los nodos. 
 - El metodo farther() halla el nodo mas alejado de un nodo y 
   devuelve la respuesta como un par {nodo, distancia}.
 - El metodo build_path(), dados los dos nodos del diametro, almacena
   los nodos del diametro en el vector path Usa el booleano flag que 
   es falso antes de la llamada.
 - Tested: http://codeforces.com/contest/1068/problem/E 
**/
pair<int, int> farther(int nod, int deep=0){
    mk[nod] = true;

    pair<int, int> fnod = {nod, deep};

    for(auto nwn: G[nod]){
        if( !mk[nwn] ){
            auto fnwn = farther(nwn, deep+1);

            if( fnod.second < fnwn.second )
                fnod = fnwn;
        }
    }
    return fnod;
}
 
void build_path(int nod, int nf, vector<int>& path){
    mk[nod] = true;

    path.push_back(nod);

    if( nod==nf ){
        flag = true;
        return;
    }

    for(auto nwn: G[nod]){
        if( !flag && !mk[nwn] ){
            build_path(nwn, nf, path);
        }
    }

    if( !flag )path.pop_back();
}
