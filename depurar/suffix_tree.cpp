/*
 * Implicit DFS on Suffix Tree with Suffix Array
 * 
 * - Hay que implementar la funcion next y dfs dentro del suffix array.
 *   next devuelve la ultima posicion menor que xend en el arreglo de 
 *   sufijos que posee mas de p caracteres comunes con la posicion x.
 * - Cada tripla (x, xend, p) para la que se llama a la funcion dfs 
 *   representa un nodo del suffix tree implicito.     
 * 
 * */

int next(int x, int xend, int p){
    if( sa[x] + p >= N ) return x; 

    int ans = x;
    for(int i=log2(xend-x+1); ~i; i--)
        if( ans + (1<<i) <= xend && sa[ans + (1<<i)] + p < N &&
            lcp(sa[ans + (1<<i)] + p, sa[x] + p) )
            ans += (1<<i);
    return ans;
}

void dfs(int x, int xend, int p){
    printf("%d %d %d\n", x, xend, p);
    
    if( x==xend && sa[x] + p >= N ) // Es un nodo final
        return; 
       
    for(int ii=x, jj; ii<=xend; ii=jj+1){
       jj = next(ii, xend, p);

       dfs(ii, jj, lcp(sa[ii], sa[jj]));
    }
}
