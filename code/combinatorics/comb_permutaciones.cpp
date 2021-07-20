/*  Solo para permutaciones sin repeticion
 - build_permutation: construye una permutacion sin repeticion
   dado su orden k y la cantidad de elementos N 
 - permutation_id: dada una permutacion devuelve el orden de esta
 - Llamar a init en el main.
**/
 
 int64 F[MN+10];

 void init(){
     F[0] = 1ll;
     for(int64 i=1; i<=MN; i++)
         F[i] = F[i-1] * i;
 }

 vector<int> build_permutation(int64 k, int64 N){
     vector<int> ans;
     set<int> S;

     for(int i=1; i<=N; i++) S.insert(i);
     k--;

     for(int i=N, get; i > 0; i--){
         get = (int)(k/F[i-1]) + 1;
         k -= (get - 1) * F[i-1];

         for(auto it=S.begin(); ; get--, it++) if( get == 1 ){
             ans.push_back(*it);

             S.erase(it);
             break;
         }
     }

     return ans;
 }

 int64 permutation_id(vector<int>& V){
     int64 ans = 0;
     set<int> S;

     for(int i=1; i<=V.size(); i++) S.insert(i);

     for(int i=0, n=V.size(); i < V.size(); i++, n--){
         int pos = 1;
         for(auto it=S.begin(); ; pos++, it++) if( *it == V[i] ){
             S.erase(it);
             break;
         }
         ans += (pos - 1) * F[n - 1];
     }

     return ans + 1;
 }
