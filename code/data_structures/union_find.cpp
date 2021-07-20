/* Union-Find
**/
int SET[MN], R[MN];

void init(){
    for(int i=1; i<=cn; i++)
        SET[i] = i, R[i] = 1;
}

int find_set(int nod){
    if( nod != SET[nod] )
        return find_set(SET[nod]);
    return nod;
}

void join_set(int nod, int nwn){
    if( R[nod] > R[nwn] )
        SET[nwn] = nod, R[nod]++;
    else
        SET[nod] = nwn, R[nwn]++;
}
