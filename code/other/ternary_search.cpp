/*  Minimo en una funcion Tof la variable LOG = 100 o 200 segun la 
    precicion y velocidad
    cambiar signo en if(f(m1) > f(m2)) para buscar max
    Si la funcion es de enteros cambiomos el ciclo por 
    while ( b - a >= 4 ) y probamos desde a hasta b  
*/

for(int i = 0; i < LOG; i++){
    long double m1 = (a * 2 + b) / 3.0;
    long double m2 = (a + 2 * b) / 3.0;

    if(f(m1) > f(m2))
       a = m1;
    else
       b = m2;
}

ans = f(a);

