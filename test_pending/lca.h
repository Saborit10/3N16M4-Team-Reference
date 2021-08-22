typedef int edge;

struct lca{
	int cn;
	vector<edge> *G;
	int L[MX], P[MX][20];
	
	lca(){}
	lca(int cn, vector<int> G[], int ni): cn(cn), G(G){
		L[ni] = 1, P[ni][0] = 0;
		dfs(ni, -1);
		
		for(int j=1, lg=log2(cn); j<=lg; j++)
			for(int i=1; i<=cn; i++)
				P[i][j] = P[ P[i][j-1] ][j-1];
	}
	
	void dfs(int nod, int p){
		for(edge nwn: G[nod]) if( nwn != p ){
			L[nwn] = L[nod] + 1;
			P[nwn][0] = nod;
			dfs(nwn, nod);
		}
	}
	
	int qry(int a, int b){
		if( L[a] < L[b] ) swap(a, b);
		
		for(int i=log2(L[a]); ~i; i--)
			if( L[ P[a][i] ] >= L[b] )
				a = P[a][i];
		if( a == b ) return a;
		
		for(int i=log2(L[a]); ~i; i--)
			if( P[a][i] && P[a][i] != P[b][i] )
				a = P[a][i], b = P[b][i];
		return P[a][0];
	}
};
