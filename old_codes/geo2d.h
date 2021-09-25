/* Geometry Library
 - Not Completely Tested Yet!!!
**/
#define SQ(X) ((X)*(X))
#define EPS 1e-12
typedef double type;

/*===================================================================
 - Funciones Basicas y Constantes
**/
    const type PI = acos(-1);
/*===================================================================
 - Conversiones de grados a radianes y viceversa.
**/
    inline type deg_to_rad(type deg){ return deg * PI / 180.0; }
    inline type rad_to_deg(type rad){ return rad * 180.0 / PI; }
/*===================================================================
 Signo de un numero real.
**/
    int sgn(type a){ return a < -EPS ? -1 : a > EPS; }
/*===================================================================
 - Clase Point-Vector 
**/
    struct pt{
        type x, y;

        /* Basics (1)*/
        pt(type x, type y): x(x), y(y){}
        pt operator + (const pt p){ return {x + p.x, y + p.y}; }
        pt operator - (const pt p){ return {x - p.x, y - p.y}; }
        pt operator * (type d){ return {x * d, y * d}; }
        pt operator / (type d){ return {x / d, y / d}; }
        
        /* Dot and Cross Product (2)*/
        type operator * (const pt p){ return x * p.x + y * p.y; }
        type operator ^ (const pt p){ return x * p.y - y * p.x; }
        
        /* Operador de Igualdad (1)*/
        bool operator == (const pt p){
            return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; 
        }

        /* Operador de Comparacion segun las Coordenadas (1)*/
        bool operator < (const pt p)const{
            if( fabs(x - p.x) < EPS ) return y < p.y;
            return x < p.x;
        }

        /* Norma del vector (1) */
        type norm(){ return sqrt(x * x + y * y); }

        /* Norma al Cuadrado del Vector (2) */
        type norm2(){ return x * x + y * y; }

        /* Traslada un punto en la direcccion del vector vec */
        pt translate(pt vec){ return *this + vec; }

        /* Escala el punto, a un ratio, alrededor del centro c */
        pt scale(pt c, type ratio){ return c + (*this - c) * ratio; }

        /* Rota el punto un angulo a */
        pt rot(type a){ 
            return {x*cos(a) - y*sin(a), x*sin(a) + y*cos(a) }; 
        }

        /* Vector perpendicular (1) */
        pt perp(){ return {-y, x};  }
    };
/*===================================================================
 - Devuelve + si c esta izq(ab), - der(ab) y 0 si abc son colineares 
   (2)
**/
    type orient(pt a, pt b, pt c){ return (b - a) ^ (c - a); }
/*===================================================================
 - Sobrecarga del operador << para la clase point.
**/
    ostream &operator << (ostream &os, const pt &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
/*===================================================================
 - Distancia entre dos puntos.
**/
    type dist(pt& a, pt& b){ return sqrt((a - b) * (a - b)); }
/*===================================================================
 - Distancia entre dos puntos elevada al cuadrado
**/
    type dist2(pt& a, pt& b){ return (a - b) * (a - b); }
/*===================================================================
 - Angulo entre dos vectores (para C++17 se puede usar acos(clamp()))
   (1)
**/ 
    type angle(pt& a, pt& b){
        type cos = a * b / a.norm() / b.norm();
        return acos(max(-1.0, min(1.0, cos)));
    }
/*===================================================================
 - Angulo orientado, con vectice en a, y con sentido de b hacia c, en
   contra de las manecillas del reloj. (1)
**/
    type oriented_angle(pt a, pt b, pt c){
        if( orient(a, b, c) > -EPS )
            return angle(b-a, c-a);
        else
            return 2 * M_PI - angle(b-a, c-a);
    }
/*===================================================================
 - Clase Line cuya ecuacion es v ^ (x, y) = c 
**/
    struct line{
        /* Vector director (-b, a) */
        pt v;
        type c;

        line(pt v, type c): v(v), c(c){}
        line(type a, type b, type c): v({-b, a}), c(c){}
        line(pt a, pt b): v(b-a), c(v ^ a){}

        /* Interseccion de dos lineas */
        pt operator & (line l){
            type not_parall = v ^ l.v;

            assert(not_parall);
            return (l.v * c - v * l.c) / not_parall;
        }

        /* Devuelve true si las rectas son paralelas (1)*/
        bool operator | (const line p){
            return fabs(v ^ p.v) < EPS;
        }
        
        /* Devuelve true si las dos lineas son coincidentes (1)*/
        bool operator == (const line p){
            return fabs(v ^ p.v) < EPS && 
            fabs(v.x * p.c - p.v.x * c) < EPS && 
            fabs(v.y * p.c - p.v.y * c) < EPS;    
        }
        
        /* Devuelve + si izq, 0 si esta sobre la linea y - der */
        type side(pt p){ return (v ^ p) - c; }

        /* Distancia de un punto a una recta */
        type dist(pt p){ return fabs(side(p)) / v.norm(); }

        /* Distancia Cuadratica de un punto a una recta */
        type dist2(pt p){ return side(p)*side(p) / (type)v.norm2(); }

        /* Compara dos puntos por cual aparece primero en la linea */
        bool cmp_proj(pt a, pt b){ return v * a < v * b; } //(1)

        /* Traslada una linea en la direccion del vector t */
        line tranlate(pt t){ return {v, c + (v ^ t)}; }

        /* Proyeccion de p sobre la recta */
        pt proj(pt p){ return p - v.perp() * side(p) / v.norm2(); }

        /* Reflexion de p sobre la recta */
        pt refl(pt p){ return p - v.perp() * 2 * side(p) / v.norm2();}

        /* Traslada una distancia a la izq, conserv. su direccion */
        line shift_left(type dist){ return {v, c + dist * norm(v)}; }
        
        /* Linea perpendicular a esta que pasa por el punto p */
        line perp_thruogh(pt p){ return line(p, p + v.perp());  }
    };
/*===================================================================
 - Sobrecarga del operador << para la clase line
**/
    ostream &operator << (ostream &os, const line &l) {
        return os << l.v.y << "x + " << -l.v.x << "y = " << l.c;
    }
/*===================================================================
 - Bisectriz del angulo entre dos vectores
**/
    line bisector(line& l1, line& l2, bool interior){
        assert((l1.v ^ l2.v) != 0);

        type sign = interior ? 1: -1;
        return {l2.v / l2.v.norm() + l1.v / l1.v.norm() * sign,
                l2.c / l2.v.norm() + l1.c / l1.v.norm() * sign };
    }
/*===================================================================
 Segments
**/
/*===================================================================
 - Chequea si un punto p esta sobre el disco de diametro [ab] (1)
**/
    bool in_disk(pt a, pt b, pt p){
        return (a - p) * (b - p) < EPS;
    }
/*===================================================================
 - Chequea si un punto p pertenece al segmento [a, b]. (1)
**/ 
    bool on_segment(pt a, pt b, pt p){
        return fabs(orient(a, b, p)) < EPS && in_disk(a, b, p);
    }
/*===================================================================
 - Retorna true si los segmentos ab y cd tienen exactamente un punto 
   de interseccion que no es ninguno de sus extremos (a, b, c, d). La
   respuesta se guarda en out. (1)
**/
    bool seg_proper_inter(pt a, pt b, pt c, pt d, pt& out){
        type oa = orient(c, d, a);
        type ob = orient(c, d, b);
        type oc = orient(a, b, c);
        type od = orient(a, b, d);
    
        if( oa * ob < 0 && oc * od < 0 ){
            out = (a * ob - b * oa) / (ob - oa);
            return true;
        }
        return false;
    }
/*===================================================================
 - Calcula la interseccion de dos segmentos. Retorna un vector vacio
   si los segmentos no se intersecan. Retorna un punto si la 
   interseccion ocurre solo en este. Retorna dos puntos si la 
   interseccion es un segmento. (1)
**/
    vector<pt> seg_inter(pt a, pt b, pt c, pt d){
        pt out;
        if( seg_proper_inter(a, b, c, d, out) )
            return {out};
        vector<pt> ans;
        
        if( on_segment(c, d, a) ) ans.pb(a);
        if( on_segment(c, d, b) ) ans.pb(b);
        if( on_segment(a, b, c) ) ans.pb(c);
        if( on_segment(a, b, d) ) ans.pb(d);
        sort(all(ans)); unique(ans);
        return ans;
    }
/*===================================================================
 - Calcula la distancia entre un segmento ab y un punto p. 
**/
    type seg_pt_dist(pt a, pt b, pt p){
        if( !(a == b) ){
            if( (p-a)*(b-a) > -EPS && (p-b)*(a-b) > -EPS ){
                auto v = (b-a);
                type c = v ^ a;
                return fabs(-v.y * p.x + v.x * p.y - c) / v.norm();
            }
        }
        return min(dist(p, a), dist(p, b));
    }
/*===================================================================
 Polygons
**/
/*===================================================================
 - Chequea si un poligono es convexo (Puede estar degenerado).
**/
    bool is_convex(vector<pt>& P){
       bool has_pos = false, has_neg = false;

       for(int i=0, n = P.size(); i < n; i++){
           type o = orient(P[i], P[(i+1)%n], P[(i+2)%n]);
           if( o > 0 ) has_pos = true;
           if( o < 0 ) has_neg = true;
       }

       return !(has_pos && has_neg);
    }
/*===================================================================
 - Area de un Triangulo 
**/
    type area_triangle(pt a, pt b, pt c){
        return fabs((b-a) ^ (c-a)) / 2.0;
    }
/*===================================================================
 - Area del Poligono
**/
    type area_poligon(vector<pt>& P){
        type ans = 0.0;

        for(int i=0, n = P.size(); i < n; i++)
            ans += P[i] ^ P[(i+1)%n];
        return fabs(ans) / 2.0;
    }
/*===================================================================
 - Chequea si [pq] cruza el rayo que sale de a
**/
    bool crosses_ray(pt a, pt p, pt q){
        return ((q.y - a.y > -EPS) - (p.y - a.y > -EPS)) 
        * orient(a, p, q) > EPS;
    }
/*===================================================================
 - Chequea si un punto esta dentro de un poligono.
**/
    bool in_polygon(vector<pt>& P, pt a, bool strict = true){
        int ans = 0;

        for(int i=0, n = P.size(); i < n; i++){
            if( on_segment(P[i], P[(i+1)%n], a) )
                return !strict;
            ans += crosses_ray(a, P[i], P[(i+1)%n]);
        }
        return ans & 1;
    }
/*===================================================================
 - Grupos de Puntos
**/
/*===================================================================
 - Ordena los puntos por su angulo, desde (-PI, PI].
**/
    void polar_sort(vector<pt>& P, pt o = {0, 0}){
        sort(all(P), [o](pt a, pt b){
            a = a - o, b = b - o;
            assert((a.x != 0 || a.y != 0) && (b.x != 0 || b.y != 0));

            bool as = a.y > 0 || (a.y == 0 && a.x < 0);
            bool bs = b.y > 0 || (b.y == 0 && b.x < 0);

            return as == bs ? 0 < (a ^ b) : as < bs;
        });
    }
/*===================================================================
 - Circulos
**/
/*===================================================================
 - Class Circle-Circunference
**/
    struct circle{
        pt o;
        type r;

        /* Constructores Basicos */
        circle(pt o, type r): o(o), r(r){}

        /* Constructor dados tres puntos no colineales */
        circle(pt a, pt b, pt c): o(0, 0){
            b = b - a, c = c - a;

            assert( fabs(b ^ c) > EPS );

            o = a + (b * c.norm2() - c * b.norm2()) / (b ^ c) / 2;
            r = dist(o, a);
        }

        /* Longitud de la Circunferencia */
        type length(){ return 2.0 * PI * r; }

        /* Intersecciones con una recta */
        vector<pt> operator & (line l){
            vector<pt> ans;

            type h2 = r*r - l.dist2(o);

            if( h2 > -EPS ){
                pt p = l.proj(o);
                pt h = l.v * sqrt(h2) / l.v.norm();

                ans.push_back(p + h);
                if( h2 > EPS ) ans.push_back(p - h);
            }
            return ans;
        }
        
        /* Interseccions con otra circunferencia. Aborta si las 
           circunferencias son coincidentes. */
        vector<pt> operator & (circle& p){
            vector<pt> ans;
            pt d = p.o - o;
            type d2 = d.norm2();
            
            if( d2 < EPS ){
                assert( fabs(p.r - r) > EPS );
                return ans;
            }
            
            type pd = (d2 + SQ(r) - SQ(p.r)) / 2;
            type h2 = SQ(r) - SQ(pd) / d2;
            
            if( h2 > -EPS ){
                pt p = o + d * pd / d2, h = d.perp() * sqrt(h2/d2);
                if( h2 > EPS ) ans = {p-h, p+h};
                else ans = {p};
            }
            return ans;
        }
        
        /* Devuelve los pares de puntos donde los circulos son 
           tangentes a una recta. El parametro inner define si las 
           tangentes buscadas son las interiores o no. Aborta si
           las circunferencias son coincidentes. (1) */
        vector<pair<pt, pt>> tangents(circle p, bool inner){
            vector<pair<pt, pt>> ans;
            pt d = p.o - o;
            type dr = r - (inner ? p.r : -p.r);
            type d2 = d.norm2(), h2 = d2 - SQ(dr);
            
            if( d2 < EPS || h2 < -EPS ){
                assert( fabs(h2) > EPS );
                return ans;
            }
            
            for(type sign: {-1, 1}){
                pt v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
                ans.pb({o + v * r, p.o + v * p.r});
            }
            return ans;
        }
    };
/*===================================================================
