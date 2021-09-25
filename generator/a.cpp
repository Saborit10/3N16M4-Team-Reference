/* Code by Saborit */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#ifndef LOCAL 
	#pragma GCC optimize("Ofast") 
#endif
#define MX 200005
#define INF (1<<30)
#define INF64 (1ll<<62)
#define EPS 1e-9
#define MOD 1000000007
#define mid (x+xend)/2
#define fr first
#define sc second
#define pb push_back
#define mp make_pair
#define len(X) ((int)((X).size()))
#define all(X) (X).begin(), (X).end()
#define chmax(X, Y) X = max((X), (Y))
#define chmin(X, Y) X = min((X), (Y))
#define unique(X) (X).resize(unique(all(X)) - (X).begin())
#ifdef LOCAL 
	#include "debug.h"
#endif
using namespace std;
using namespace __gnu_pbds;

typedef long long int64;
typedef unsigned long long unt64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pll;

/* =========================== TEMPLATE CODE =========================== */

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

/* =========================== TEMPLATE CODE =========================== */

/* =========================== TEMPLATE CODE =========================== */

/* Algoritmo de Kruskal
 - Devuelve la lista de aristas que pertenecen al MST.
 - _cost es el tipo de el costo asociado a cada arista.
 - Tested on: https://codeforces.com/contest/1184/problem/E1
 - Dependencias: struct ds;
**/
typedef int _cost;

struct edge{
    int a, b;
    _cost c;
};

struct kruskal{
    ds S;
    vector<edge> E;
    
    kruskal(int cn): S(cn){}
    
    void add_edge(int a, int b, _cost c){
        E.pb({a, b, c});
    }
    
    vector<edge> mst(){
        vector<edge> ans;
         
        sort(all(E), [](edge& a, edge& b){
            return a.c < b.c;
        });
        
        for(auto e: E) if( S.join(e.a, e.b) )
            ans.pb(e);
        return ans;
    }
};

/* =========================== TEMPLATE CODE =========================== */


int N, Q;
int c[26];
char S[MX];
torcoder A[MX];
vector<segment_tree<torcoder, pintar>> ST;

int main(void){
    //~ freopen("a.in", "r", stdin);
    //~ freopen("a.out", "w", stdout);
    
	scanf("%d%d", &N, &Q);
	scanf(" %s", S+1);
	
	for(int c=0; c < 26; c++){
		for(int i=1; i<=N; i++)
			if( S[i] == 'a' + c )
				A[i] = torcoder(1);
			else
				A[i] = torcoder(0);
		
		ST.pb(segment_tree<torcoder, pintar>(N, A));
	}
	
	while( Q-- ){
		int a, b; scanf("%d%d", &a, &b);
		
		pintar f(0);
		for(int i=0; i < 26; i++)
			c[i] = ST[i].qry(root, a, b).cant;
		
		int p = -1, cnt = 0, x = 0;
		for(int i=0; i < 26; i++)
			if( c[i] & 1 )
				cnt++, p = i;
			else
				x += c[i];
		
		//~ db() << imie(p) imie(cnt);
		//~ db() << mt(c, 2);
		
		if( cnt > 1 )
			continue;
		for(int i=0; i < 26; i++)
			ST[i].upt(root, a, b, f);
		
		f = pintar(1);
		if( cnt == 1 ){
			//~ db() << "PINTAR: " << imie(a+x) imie(b-x);
			ST[p].upt(root, a+x/2, b-x/2, f);
			c[p] = 0;
		}
		
		for(int i=0, l=a, r=b; i < 26; i++){
			ST[i].upt(root, l, l+c[i]/2-1, f);
			l += c[i]/2;
		
			ST[i].upt(root, r-c[i]/2+1, r, f);
			r -= c[i]/2;
		}
	}
	
	for(int i=1; i<=N; i++){
		for(int c=0; c < 26; c++)
			if( ST[c].qry(root, i, i).cant == 1 ){
				printf("%c", 'a' + c);
				break;
			}
	}
	printf("\n");
		
		
   return 0;
}
