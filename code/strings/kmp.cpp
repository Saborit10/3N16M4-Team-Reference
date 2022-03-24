/* Knuth-Morris-Pratt Algorithm
 - Recibe un texto T y un patron P y devuelve un vector con los
   indices donde comienzan las ocurrencias del patron dentro del
   texto.
 - fail guarda el largo del mayor prefijo que es a la vez sufijo
   del intervalo [0, i] del patron.
 - Tested on: 
*/
vector<int> kmp(char* T, char* P){
    int lt = strlen(T);
    int lp = strlen(P);
    vector<int> ans, fail(lp);

    for(int i=1, st; i < lp; i++){
        st = fail[i-1];
        while( st > 0 && P[st]!=P[i] ) st = fail[st-1];
        if( P[st]== P[i])
            fail[i] = st + 1;
    }

    for(int i=0, st = 0; i < lt; i++){
        while( st > 0 && P[st]!=T[i]) st = fail[st-1];
        if(P[st]==T[i]) st++;
        if( st==lp ){
            ans.pb(i-lp+1);
            st = fail[st-1];
        }
    }
    return ans;
}
