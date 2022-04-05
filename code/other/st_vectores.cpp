
/* Segment Tree Vectores
 - Rango 1 .. 1e18. 
 - Maneja operaciones de la forma
 - update(1, N , 1, in, fn, val) -> Para i=[in, fn]
   hacer A[i] = val. 
 - query(1, N, 1, in, fn)     -> Calcular la suma de A[i]
   para i=[in, fn].
 - Para cada nodo del segment tree se guarda la suma del intervalo
 - Se puede modificar, cambiando la operacion & definida en la
   estructura node,
   haciendo los cambios correspondientes en la forma de updatear
   y definir el
   valor neutro para el lazy.
 - Tiempo: O(N log N). 
 - Tested on: https://codeforces.com/contest/1556/problem/C
**/


struct node{
    int64 val = 0;
    
    node operator & (const node &p){
        node ans;
        ans.val = val + p.val;
        return ans;
    }
};

struct st_vectores{
    int64 neutro_lazy;
    vector<node> T;
    vector<int64> mk;
    vector<pii>P;
    int tot;
    
    st_vectores(): neutro_lazy(0), T(2), mk(2, neutro_lazy),
        P(2,{0,0}), tot(1){}
    
    void verificar ( int nod ){
         if ( P[nod].fr == 0 ){
             P.pb({0,0}); P.pb({0,0}); T.pb( {} ); T.pb( {} );
             mk.pb ( neutro_lazy ); mk.pb ( neutro_lazy );
             tot += 2;P[nod].fr=tot-1,P[nod].sc=tot;
         }
    }
    
    void lazy(int64 a, int64 b, int nod){
         T[nod] = (node){mk[nod] * (int64)(b-a+1ll)};
         if ( a != b ){  verificar ( nod );
                if ( mk[P[nod].fr] != neutro_lazy )
                    mk[P[nod].fr] += mk[nod];
                else mk[P[nod].fr] = mk[nod];
                if ( mk[P[nod].sc] != neutro_lazy )
                    mk[P[nod].sc] += mk[nod];
                else mk[P[nod].sc] = mk[nod];}
         mk[nod] = neutro_lazy;}
         
    //node build( int64 a, int64 b, int nod ){
        //if ( a == b ){return T[nod] = { 0 };}
        //verificar ( nod );
        //return T[nod] = build(a, mid, P[nod].fr) & 
                        //build(mid+1, b, P[nod].sc);}
    
    node update( int64 a, int64 b, int nod, int64 in, int64 fn, int64 val ){
        if( mk[nod] != neutro_lazy )
            lazy(a, b, nod);
            
        if( a > fn || b < in )
            return T[nod];
            
        if( a >= in && b <= fn ){
               mk[nod] = val;  lazy ( a,b,nod );
            return T[nod];    }
            
        verificar ( nod );
        return T[nod] = update(a, mid, P[nod].fr, in, fn, val) & 
                        update(mid+1, b, P[nod].sc, in, fn, val);}
    
    node query(int64 a, int64 b, int nod, int64 in, int64 fn){
        if( mk[nod] != neutro_lazy )
            lazy(a, b, nod);
            
        if( a >= in && b <= fn ){
            return T[nod]; }
        verificar ( nod );
        if ( mid < in )return query(mid+1, b, P[nod].sc, in, fn);
        if ( mid+1 > fn )return query(a, mid, P[nod].fr, in, fn );
        return query(a, mid, P[nod].fr, in, fn ) & 
               query(mid+1, b, P[nod].sc, in, fn);    }
};
