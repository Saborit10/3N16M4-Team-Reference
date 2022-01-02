/* Metodo de Gauss para Resolver un SEL
 - Resuelve la ecuacion matricial Ax = B.
 - n: cantidad de ecuaciones, m: cantidad de variables.
 - Recibe una matriz de n x (m+1), donde la ultima columna esta
   formada por los coeficientes de B. Los restantes elementos de
   la matriz son coeficientes de A: a[i][j] es el coeficiente de
   la j-esima variable en la ecuacion i (ambas 0-indexed).
 - Si la funcion devuelve 0, el sistema no tiene soluciones, si
   devuelve -1, tiene infinitas soluciones; y si retorna 1, tiene
   solucion unica.
 - el vector ans que se pasa a la funcion debe ser de largo m. Al
   final ans[i] guarda un posible valor para la i-esima variable
   (0-indexed).
 - Dependencias: Operaciones con Modulos; pero se pueden cambiar
   esas funciones junto al tipo de datos type para trabajar con
   numeros de punto flotante.
 - Tested on: https://codeforces.com/contest/1616/problem/F
 {Pending test for doubles}
**/
typedef int type;
typedef vector<vector<type>> matrix;

int gauss(matrix& a, vector<type>& ans){
    int n = len(a);
    if( n == 0 )
        return -1;
    int m = len(a[0]) - 1;
    
    vector<int> where(m, -1);
    for(int r=0, c=0; r < n && c < m; c++){
        int piv = r;
        for(int i=r; i < n; i++)
            if( abs(a[i][c]) > abs(a[piv][c]) )
                piv = i;
        if( abs(a[piv][c]) < EPS )
            continue;
        for(int j=c; j<=m; j++)
            swap(a[piv][j], a[r][j]);
        where[c] = r;
        
        for(int i=0; i < n; i++) if( i != r ){
            type tmp = di(a[i][c], a[r][c]);
            
            for(int j=c; j<=m; j++)
                a[i][j] = sb(a[i][j], pd(a[r][j], tmp));
        }
        r++;
    }
    
    ans.assign(m, 0);
    for(int j=0; j < m; j++) if( ~where[j] )
        ans[j] = di(a[ where[j] ][m], a[ where[j] ][j]);
    
    for(int i=0; i < n; i++){
        type sum = 0;
        
        for(int j=0; j < m; j++)
            sum = su(sum, pd(ans[j], a[i][j]));
        if( abs(sum - a[i][m]) > EPS )
            return 0;
    }
    for(int j=0; j < m; j++) if( where[j] == -1 )
        return -1;
    return 1;
}
