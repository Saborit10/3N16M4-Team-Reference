/* Manachar's Algorithm
 - Recibe un cadena S de largo n. 
 - Devuelve un vector de largo 2*n-1, donde las posiciones 2*i 
   contienen el largo del mayor palindrome impar con centro en el 
   caracter i. Las posiciones 2*i-1 guardan el largo del mayor 
   palindrome par con centro entre los caracteres i, i+1.
 - En otras palabras, devuelve el vector relativo a "a#b#c#d#e" donde
   "abcde" es la cadena original.
 - Para recorrer todos los caracteres de un palindrome centrado en j 
   (relativo al vector resultante y correspondiente a la cadena 
   "a#b#c#d#e") se usa un ciclo que vaya de dos en dos, desde 
   (j - p[j] + 1) hasta (j + p[j] - 1) inclusive. Cada posicion real 
   en la cadena tiene indice j/2. 
 - Complejidad: O(n)
 - Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=1389 
**/
vector<int> manachar(string& S){
    int N = S.size();
    vector<int> ans(2 * N - 1);
    
    for(int i=0, j=0, k=0; i < 2*N-1; i+=k){
        while( i-j>=0 && i+j+1 < 2*N && S[(i-j)/2] == S[(i+j+1)/2] )
            j++;
        ans[i] = j;
        
        for(k=1; k<=ans[i] && ans[i-k] != ans[i] - k; k++)
            ans[i+k] = min(ans[i-k], ans[i] - k);    
        j = max(j-k, 0);        
    }
    return ans;
}
