/* Small to Large (ale's style)
 - vec es un arreglo de estructuras de datos que guardan la 
   informacion de cada subarbol. Estas estructuras deber poderse 
   mezclar en tiempo proporcional al tamanno de la mas pequenna.
 - Es preferido este estilo cuando no hace falta una estructura 
   auxiliar global para mantener la informacion. Tambien se prefiere 
   cuando hay que combinar informacion de nodos en subarboles 
   hermanos.
 - O(n log n) * [operacion en estructura auxiliar]
 - Tested on: https://codeforces.com/contest/600/porblem/E  
**/

vector<int> vec[MX];

// Une dos conjuntos y devuelve el id del mayor
int join(int a, int b){
    if( a == b ) return a;
    if( vec[a].size() < vec[b].size() ) swap(a, b);
    
    // Metemos los elementos del conjunto mas pequenno al mas grande
    // NOTA: Aqui podemos tambien calcular cierta propiedad del
    // conjunto resultante. 
    
    for(auto i: vec[b]) vec[a].pb(i);
    return a;    
}

void dfs(int nod, int p=-1){
    int big = nod;
    vec[nod].pb(nod);
    
    // Mezcla los conjuntos 
    for(auto nwn: G[nod]) if( nwn != p ){
        dfs(nwn, nod);
        big = join(big, nwn);
    }
    swap(vec[nod], vec[big]);
    
    // - Ahora se puede responder la query para el subarbol de nod
    // - Podemos hacer algo con vec[nod]. Este contiene toda la 
    //   informacion de los nodos del subarbol de nod. 
}
