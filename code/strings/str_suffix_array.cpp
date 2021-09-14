/* Suffix Array
 - Las posiciones de cada sufijo i en el orden del suffix array 
   se guardan en la fila P[i][k-1].
 - Para usarlo, primero copiar en S la cadena a procesar.
 - Matchea el caracter c en la posicion pos, dado que el intervalo 
   [a, b] corresponde a los sufijos que tienen a S[0..pos-1]. La 
   primera vez se llama a la funcion con pos = 0 y 
   [a, b] = [1, SA.N-1]. Para usar esta funcion se debe agregar el
   caracter '$' al final de la cadena S.  
 - Tiempo: Prec: O(N * log^2(N)), lcp: O(log(N)), match: O(lg N) por
   caracter.
 - Memoria: O(N * lg(N))  
 - Tested on: hackerrank.com/challenges/string-similarity/problem
**/
struct suffix{
    int a, b, p;
    
    bool operator < (const suffix &p)const{
        return a==p.a ? b < p.b : a < p.a;    
    }
    bool operator == (const suffix &p)const{
        return a==p.a && b == p.b;    
    }     
};

struct suffix_array{
    int N, k, del;
    int P[MX][20], sa[MX];
    char S[MX];
    suffix L[MX];
    
    void build(){
        N = strlen(S);
        
        for(int i=0; i < N; i++)
            P[i][0] = S[i];
           
        for(k=del=1; (del>>1) < N; k++, del<<=1) {
            for(int i=0; i < N; i++){
                L[i].a = P[i][k-1];
                L[i].b = (i + del < N) ? P[i+del][k-1] : -1;
                L[i].p = i;
            }
            sort(L, L+N);
            
            for(int i=0; i < N; i++)
                P[ L[i].p ][k] = (i && L[i]==L[i-1]) ? 
                                                 P[ L[i-1].p ][k]: i;
        }

        for(int i=0; i < N; i++)
            sa[ P[i][k-1] ] = i;
    }
    
    int lcp(int x, int y){
        if( x==y ) return N-x;
        
        int ans = 0;
        
        for(int i=k-1; i>=0 && x < N && y < N; i--){
            if( P[x][i] == P[y][i] ) 
                x += (1<<i), y += (1<<i), ans+=(1<<i);    
        }   
        return ans; 
    }

    pair<int, int> match(int a, int b, int pos, int c){
        pair<int, int> ans;
        
        int p = a-1;
        for(int i=log2(b-a+1); ~i; i--){
            if( p+(1<<i)<=b && c > S[sa[p+(1<<i)] + pos] )
                p += (1<<i);
        }
        ans.fr = p + 1;
        
        p = b+1;
        for(int i=log2(b-a+1); ~i; i--) {
            if( p-(1<<i)>=a && c < S[sa[p-(1<<i)] + pos] )
                p -= (1<<i);
        }
        ans.sc = p - 1;
        return ans; 
    }
};
