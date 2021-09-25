/* Recta Normalizada de la Forma ax + by = c
  - Dados dos puntos, genera una representacion de la recta que los
    contiene.
  - Cada objeto de la clase tline retornada por este metodo representa
    univocamente una recta en el plano.
  - Solo para type == int64 (type debe ser un tipo entero).
  - Tested on: https://codeforces.com/contest/1163/problem/c2/c2.html
**/
struct tline{
    type a, b, c; 
    
    bool operator == (const tline& p) const{
        return a==p.a && b==p.b && c==p.c;
    }
    
    bool operator < (const tline& p)const{
        if( a != p.a ) return a < p.a;
        if( b != p.b ) return b < p.b;
        return c < p.c;
    }
};

tline normalized_line(pt p, pt q){
    type a = q.y - p.y, b = p.x - q.x, c = p.x * q.y - q.x * p.y;
    
    type g = __gcd(labs(a), __gcd(labs(b), labs(c)));
    
    if( g == 0ll ) return {a, b, c};
    
    a /= g, b /= g, c /= g;
    
    if( a < 0 )
        a = -a, b = -b, c = -c;
    else if( a == 0 ){
        if( b < 0 )
            b = -b, c = -c;
        else if( b == 0 )
            c = -c;
    }
    return {a, b, c};
}
