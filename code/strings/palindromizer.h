/* Palindromizer 
 - Devuelve si S[a, b] es un palindrome.
 - Tiempo: Preproc: O(n). Query: O(1).
 - Tested: http://coj.uci.cu/24h/problem.xhtml?pid=1624
**/
struct palindromizer{
    hasher A, R;
     
    palindromer(string S){
        A = hasher(S);
         
        for(int i=0, j=S.size()-1; i < j; i++, j--)
            swap(S[i], S[j]);
             
        R = hasher(S);    
    }
     
    bool is_palin(int a, int b){
         return A.query(a, b) == R.query(A.N - b - 1, A.N - a - 1);  
    } 
};
 
