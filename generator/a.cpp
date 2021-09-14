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

/* =========================== TEMPLATE CODE =========================== */

/* =========================== TEMPLATE CODE =========================== */

/* Criba de Eratostenes y Funciones Usadas en Teoria de Numeros 
 - Se usan las variables globales mk[] y p para la criba y para 
   guardar los primos respectivamente.
 - init()       Construye el vector con los primos menores que MX
   Tested on: http://dmoj.uclv.cu/problem/oci19day1a  
 - euler_phi(N) Cuenta el numero de enteros positivos menores que N 
   que son coprimos con N 
   Tested on: http://dmoj.uclv.cu/problem/oci19day1a 
 - cant_pf(N)   Cuenta la cantidad de factores primos de N 
 - diff_pf(N)   Cuenta la cantidad de factores primos diferentes 
   de N
   Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=3274  
 - cant_div(N)  Cuenta la cantidad de divisores de N 
 - sum_div(N)   Devuelve la suma de los divisores de N
   Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=1132
**/

/* Criba de Eratostenes */
bool mk[MX];
vector<int> p;

void init(){
    for(int64 i=2; i < MX; i++) if( !mk[i] ){
        p.pb(i);
        for(int64 j=i*i; j < MX; j+=i) mk[j] = true;    
    }    
}

/* Cantidad de Enteros Positivos Menores que N Coprimos con El */
int64 euler_phi(int64 N){
    int64 ans = N;
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        if( N % p[i] == 0 ) ans -= ans / p[i];
        while( N % p[i] == 0 ) N /= p[i];
    }    
    if( N > 1ll ) ans -= ans / N;
    
    return ans;
}

/* Cantidad de Factores Primos */
int cant_primos(int64 N){
    int ans = 0;
    
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        while( N % p[i] == 0 ){
            ans++;
            N /= p[i];   
        }     
    }
    if( N > 1ll ) ans++;
    
    return ans;
}

/* Cantidad de Factores Primos Diferentes */
int cant_primos_diff(int64 N){
    int ans = 0;
    
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        if( N % p[i] == 0 ) ans++;
        while( N % p[i] == 0 ) N /= p[i];    
    }
    if( N > 1ll )    
        ans++;
        
    return ans;    
}

/* Cantidad de Divisores */
int cant_div(int64 N){
    int ans = 1, power;
    
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        power = 0;
        
        while( N % p[i] == 0 ){
            N /= p[i];
            power++;    
        }
        ans *= power + 1;    
    }  
    if( N > 1ll ) ans *= 2;
    
    return ans;  
}

/* Suma de los Divisores */ 
int64 sum_div(int64 N){
    int64 ans = 1ll, power;
    
    for(int i=0; (int64)p[i]*p[i]<=N; i++){
        power = 0;
        
        while( N % p[i] == 0 ){
            N /= p[i];
            power++;    
        }
        ans *= ((int64)pow((double)p[i], power + 1.0)-1) / (p[i]-1);    
    }    
    if( N > 1ll )
        ans *= ((int64)pow((double)N, 2.0) - 1) / (N - 1);
        
    return ans;    
}

/* =========================== TEMPLATE CODE =========================== */

/* =========================== TEMPLATE CODE =========================== */

/* Convex Hull Trick Dinamico
 - Para C++14 o superior:
  - Para minimo, cambiar los signos '<' por '>' en las lineas:
    * return m < p.m;
    * x->l = x->b > y->b ? INF : -INF; 
 - Tested on: https://www.codechef.com/JAN16/problems/CYCLRACE
 
 - Para compilar en C++11 se una la clase line correspondiente y deben 
   cambiarse las sgtes lineas en la clase cht:
   - [adicionar] typedef multiset<line>::iterator iterator; 
   - struct cht : public multiset<line>
   - auto li = lower_bound({0, 0, (long double)x, 1}); 
 - Tiempo: add() y query(): O(lg n), con constantes elevadas.
 - Memoria: O(n)
 - Tested on: https://icpcarchive.ecs.baylor.edu/ (...) problem=3134  
**/
 
//C++11
struct line{
    mutable int64 m, b;
    mutable long double l;
    mutable bool cmp_by_limit;
    
    bool operator < (const line &p)const{
        return p.cmp_by_limit ? l < p.l : m < p.m;    
    }
      
    inline int64 eval(int64 x)const{ return m*x + b; } 
};

// C++14
struct line{
    mutable int64 m, b;
    mutable long double l;
    
    bool operator < (const line &p)const{ return m < p.m; }
    bool operator < (int64 x)const{ return l < x; }
    
    inline int64 eval(int64 x)const{ return m * x + b; } 
};

struct cht : public multiset<line, less<>>{
    bool sect(iterator x, iterator y){
        if( y == end() ) { x->l = INF; return false; } 
        
        if( x->m == y->m ) 
            x->l = x->b > y->b ? INF : -INF;
        else 
            x->l = (long double)(x->b - y->b) / (y->m - x->m);
        
        return x->l >= y->l; 
    }
    
    void add(int64 m, int64 b){
        auto r = insert({m, b, 0}), it = r++, l = it;
        
        while( sect(it, r) ) r = erase(r);
        
        if( l != begin() && sect(--l, it) )
            sect(l, it = erase(it));
            
        while( (it = l) != begin() && (--l)->l >= it->l )
            sect(l, erase(it));
    }
    
    int64 query(int64 x){ 
        auto li = *lower_bound(x);
        return li.eval(x); 
    }
}; 

/* =========================== TEMPLATE CODE =========================== */

/* =========================== TEMPLATE CODE =========================== */

/* Segment Tree
 - segment_tree(): construye el segment tree.
 - upt(): actualiza la posicion a con el monoide t.
 - qry(): devuelve la respuesta en el rango [a, b]. 
 - Los constructores reciben o un arreglo de monoides, o un monoide,
   el cual se convierte en el valor de las hojas.
 
 Un Monoid es una clase que implementa los siguientes metodos:
 - Monoid(): Constructor que crea el elemento identidad de los
   monoides.
 - Monoid(const Monoid&, const Monoid&): constructor a partir de
   combinar dos monoides.

 - Tested on: https://codeforces.com/contest/1567/problem/E
*/
#define izq (nod<<1)
#define der (izq | 1)
#define self x, xend, nod
#define context int x, int xend, int nod
#define call_childs(X, Y...) X(x, mid, izq, Y), X(mid+1, xend, der, Y)
#define root 1, N, 1

template<class M>
struct segment_tree{
    int N;
    vector<M> T;
    
    explicit segment_tree(int N, M t): N(N), T(4*N){
        build(root, &t, NULL);
    }
    
    explicit segment_tree(int N, M* A): N(N), T(4*N){
        build(root, NULL, A);
    }
    
    void build(context, M* t, M* A){
        if( x==xend ){
            T[nod] = t ? *t : A[x];
            return;
        }
        call_childs(build, t, A);
        T[nod] = M(T[izq], T[der]);
    }
    
    void upt(context, int a, M& t){
        if( a < x || xend < a )
            return;
        if( a<=x && xend<=a )
            T[nod] = t;
        else{
            call_childs(upt, a, t);
            T[nod] = M(T[izq], T[der]);
        }
    }
    
    M qry(context, int a, int b){
        if( b < x || xend < a )
            return M();
        if( a<=x && xend<=b )
            return T[nod];
        return M(call_childs(qry, a, b));
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
