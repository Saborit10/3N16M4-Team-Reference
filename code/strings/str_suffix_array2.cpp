/* Suffix Array
 - No esta probado, pero es mas rapido que el otro. Este debe ser el
   que se quede en el Team Reference.
**/
struct suffix_array{
    int N;
    int A[MX], R[MX], aa[MX], rr[MX], C[MX];
    char S[MX];
    
    suffix_array(char* ss){
        N = strlen(ss);
        
        for(int i=0; i < N; i++){
            S[i] = R[i] = ss[i];
            A[i] = i;   
        }
        
        for (int k = 1; k < N; k <<= 1){
            countingSort(k);
            countingSort(0);
        
            int r = rr[ A[0] ] = 0;
            for (int i = 1; i < N; i++)
                rr[ A[i] ] =    
                (R[A[i]] == R[A[i-1]] && R[A[i]+k] == R[A[i-1]+k]) ? 
                    r : ++r;
            for (int i = 0; i < N; i++)
                R[i] = rr[i];
            
            if (R[ A[N-1] ] == N-1) break;
        }
    }
    
    void countingSort(int k){
        int sum, ma = max(300, N);
        memset(C, 0, sizeof C);     
    
        for (int i=0; i < N; i++)       
            C[i + k < N ? R[i + k] : 0]++;
        
        for (int i=sum=0; i < ma; i++){
            int t = C[i]; C[i] = sum; sum += t;
        }
        
        for (int i=0; i < N; i++)       
            aa[ C[ A[i] + k < N ? R[ A[i] + k ] : 0 ]++ ] = A[i];
        
        for (int i=0; i < N; i++)   
            A[i] = aa[i];
    }
};
