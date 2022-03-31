/* Suffix Array
 - OJO: La cadena debe terminar en '$'.
 - SA.A guarda el suffix array.
 - SA.R guarda para cada sufijo, la posicion en la que esta en
   el suffix array.
 - Luego de llamar a computeLCP(), el arreglo LCP guarda, para cada
   sufijo, el prefijo comun mas largo con el anterior sufijo, en el
   orden del suffix array. En particular LCP[0] = 0.
 - Tiempo: O(n * lg n), Memoria: O(n). 
 - Tested on: https://codeforces.com/gym/103176/problem/C
**/
struct suffix_array{
    int n;
    vector<int> A, R, aa, rr, C, P, PLCP, LCP;
    string S;
    
    suffix_array(char* ss){
        n = strlen(ss);
        R = rr = P = PLCP = LCP = vector<int>(n+1);
        A = aa = C = vector<int>(max(300, n) + 1);
        
        for(int i=0; i < n; i++){
            R[i] = ss[i];
            A[i] = i;
            S += ss[i];
        }
        
        for (int k = 1; k < n; k <<= 1){
            countingSort(k);
            countingSort(0);
        
            int r = rr[ A[0] ] = 0;
            for (int i = 1; i < n; i++)
                rr[ A[i] ] =    
                (R[A[i]] == R[A[i-1]] && R[A[i]+k] == R[A[i-1]+k]) ? 
                    r : ++r;
            for (int i = 0; i < n; i++)
                R[i] = rr[i];
            
            if (R[ A[n-1] ] == n-1) break;
        }
    }
    
    void countingSort(int k){
        int sum, ma = max(300, n);
        
        for(auto& x: C) x = 0;
    
        for (int i=0; i < n; i++)       
            C[i + k < n ? R[i + k] : 0]++;
        
        for (int i=sum=0; i < ma; i++){
            int t = C[i]; C[i] = sum; sum += t;
        }
        
        for (int i=0; i < n; i++)       
            aa[ C[ A[i] + k < n ? R[ A[i] + k ] : 0 ]++ ] = A[i];
        
        for (int i=0; i < n; i++)   
            A[i] = aa[i];
    }
    
    void computeLCP(){
        P[ A[0] ] = -1;
        for(int i=1; i < n; i++)
            P[ A[i] ] = A[i-1];
        
        for(int i=0, l=0; i < n; i++){
            if( P[i] == -1 ){
                PLCP[i] = 0;
                continue;
            }
            
            while( S[i + l] == S[ P[i] + l ] ) l++;
            PLCP[i] = l;
            l = max(l-1, 0);
        }
        
        for(int i=0; i < n; i++)
            LCP[i] = PLCP[ A[i] ];
    }
};
