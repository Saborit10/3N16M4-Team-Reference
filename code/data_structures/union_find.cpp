/* Union-Find
 - Representa conjuntos disjuntos numerados de 1 a N.
 - Tested on: https://codeforces.com/contest/1559/problem/D1
**/

struct ds{
    int N;
    int SET[MX], R[MX];
    
    ds(int N): N(N){
        for(int i=1; i<=N; i++)
            SET[i] = i, R[i] = 1;
    }
    
    int fset(int v){ return SET[v] != v ? SET[v] = fset(SET[v]) : v; }
    inline bool diff(int a, int b){ return fset(a) != fset(b); }
    
    bool join(int a, int b){
        if( (a = fset(a)) == (b = fset(b)) )
            return false;
         
        if( R[a] < R[b] ) swap(a, b);
        SET[b] = a, R[a]++;
        return true;
    }
};
