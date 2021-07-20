/* Knuth-Morris-Pratt Algorithm
 - fail guarda el largo del mayor prefijo que es 
   a la vez sufijo del patron 
*/
scanf("%s\n%s\n", &T, &P);
lt = strlen(T);
lp = strlen(P);

fail[0] = 0;
for(int i=1, st; i < lp; i++){
    st = fail[i-1];
    while( st > 0 && P[st]!=P[i] ) st = fail[st-1];
    if( P[st]== P[i])
        fail[i] = st + 1;
}

for(int i=0; i < lt; i++){
    while( st > 0 && P[st]!=T[i]) st = fail[st-1];
    if(P[st]==T[i]) st++;
    if( st==lp ){
        printf("There is an occurrence at %d\n", i-lp+1);
        st = fail[st-1];
    }
}

