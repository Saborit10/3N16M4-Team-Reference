/* Convex Hull (Andrew's Algorithm)
 - Retorna el Convex Hull de un Conjunto de Puntos (ccw)
 - Para que acepte puntos colineares, cambiar EPS por -EPS en el
   while.
 - Tiempo: O(n log n). Memoria: O(n)
 - Tested on: moat USACO Octubre 2006 (Probar MAS)
**/

vector<pt> convex_hull(vector<pt> P){
    int N = len(P), t = 0;
    vector<pt> h(2 * N);
    
    sort(all(P), [](pt a, pt b){
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    });
    
    for(int i=0; i < N; h[t++] = P[i++])
        while( t > 1 && orient(h[t-2], h[t-1], P[i]) < EPS ) t--;
    for(int i=N-2, k=t; ~i; h[t++] = P[i--])
        while( t > k && orient(h[t-2], h[t-1], P[i]) < EPS ) t--;
    return vector<pt>(h.begin(), h.begin() + t - (t > 1));
}
