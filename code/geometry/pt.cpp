/* Clase Point-Vector 
**/
typedef double type;

struct pt{
    type x, y;

    /* Basics */
    pt operator + (const pt p){ return {x + p.x, y + p.y}; }
    pt operator - (const pt p){ return {x - p.x, y - p.y}; }
    pt operator * (type d){ return {x * d, y * d}; }
    pt operator / (type d){ return {x / d, y / d}; }
    
    /* Dot and Cross Product */
    type operator * (const pt p){ return x * p.x + y * p.y; }
    type operator ^ (const pt p){ return x * p.y - y * p.x; }
    
    /* Operador de Igualdad */
    bool operator == (const pt p){
        return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; 
    }

    /* Operador de Comparacion segun las Coordenadas */
    bool operator < (const pt p)const{
        if( fabs(x - p.x) < EPS ) return y < p.y;
        return x < p.x;
    }

    /* Norma del vector */
    type norm(){ return sqrt(x * x + y * y); }

    /* Norma al Cuadrado del Vector */
    type norm2(){ return x * x + y * y; }

    /* Traslada un punto en la direccion del vector vec */
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
