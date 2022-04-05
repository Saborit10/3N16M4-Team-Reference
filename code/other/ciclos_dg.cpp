// Detecta ciclos en DG

int COL[MX];

bool dfs ( int nod ){
     COL[nod] = 1;
     bool v = 0;
     for ( auto nwn : G[nod] ){
          if ( COL[nwn] == 1 )return 1;
          if ( !COL[nwn] ){
              v = v | dfs(nwn);
          }
     }
     COL[nod] = 2;
     return v;
}
