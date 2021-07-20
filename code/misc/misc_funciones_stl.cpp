/* 
 Trabajo con Caracteres
*/

/* =============================================================
 - Chequea si un caracter es alfanumerico, o sea, si es un 
   digito o una letra mayuscula o minuscula                             
**/
    int isalnum(int ch)
/* =============================================================
 - Chequea si un caracter es una letra (mayuscula o minuscula)
**/
    int isalpha(int ch) 
/* =============================================================
 - Chequea si un caracter es una letra minuscula 
**/
    int islower(int ch)
/* =============================================================
 - Chequea si un caracter es una letra mayuscula 
**/
    int isupper(int ch)
/* =============================================================
 - Chequea si un caracter es un digito
**/
    int isdigit(int ch)
/* =============================================================
 - Convierte el caracter a minuscula. No lo modifica si no es 
   mayuscula
**/
    int tolower(int ch) 
/* =============================================================
 - Convierte el caracter a mayuscula. No lo modifica si no es 
   minuscula 
**/
    int toupper(int ch)
/* ========================================================== */

/* 
 Conversiones a Formatos Numericos
**/  

/* =============================================================
 - Interpreta un valor de punto flotante en una cadena apuntada 
   por str. Igualmente acepta las constantes NAN y INF sin 
   importar el case. 
**/
    double atof(const char *str) 
/* =============================================================
 - Convierte una cadena a entero. La cadena puede tener un signo 
   de menos o de mas al principio.
**/
    int atoi(const char *str)
    long atol(const char *str)
    long long atoll(const char *str)
/* =============================================================
 - Convierte un entero o real a una string 
**/
    string to_string(int value)                
    string to_string(double value)             
    string to_string(long long value)
    string to_string(float value)
    string to_string(long double value)
/* ========================================================== */

/* 
 Clase string
 - Todos sus comportamientos se indefinen si la cadena esta 
   vacia.
**/

/* =============================================================
 - Retorna una substring [pos, pos+count). Si la subcadena se 
   extiende mas alla del final de la cadena la subcadena 
   retornada sera [pos, size()).
**/
    string substr(size_t pos = 0, size_t count) 
/* =============================================================
 - Elimina el ultimo caracter de la cadena
**/
    pop_back()
/* =============================================================
 - Referencia al primer caracter de la cadena
**/
    front()
/* =============================================================
 - Referencia al ultimo caracter de la cadena
**/
    back()
/* =============================================================
 - Interpreta un numero de punto flotante en una string str
**/
    float stof(str)
    double stod(str)
    long double stold(str)
/* =============================================================
 - Interpreta un numero entero en una cadena str
**/
    int stoi(str)
    long stol(str)
    long long stoll(str)
/* ========================================================== */

/*
 Algoritmos
**/

/* =============================================================
 - Llena un intervalo con incrementos sucesivos de un valor
   inicial
**/
    void iota(first, last, value)
/* =============================================================
 - Devuelve la suma(o el reultado de la operacion) aplicada
   sucesivamente a los elementos del rango, dados un valor
   inicial y opcionalmente una operacion (si no se especifica se
   usa la suma).
**/
    accumulate(first, last, init, op = '+')
/* =============================================================
 - Calcula las sumas parciales de un rango y las escribe a
   partir de d_first
**/
    partial_sum(first, last, d_first, op = '+')
/* =============================================================
 - Devuelve un iterador que apunta al primer elemento en el
   rango, que sea maximo/minimo. Opcionalmente se puede
   especificar un comparador.
**/
    max_element(first, last, op = '>')
    min_element(first, last, op = '<')
/* =============================================================
 - Devuelve la cantidad de elementos en un rango que sean
   iguales al valor dado.
**/
    int count(first, last, value)
/* =============================================================
 - Devuelve la cantidad de elementos en un rango para los cuales
   el predicado retorna verdadero.
**/
    int count_if(first, last, predicado)
/* =============================================================
 - Ejecuta una accion en cada elemento del rango, en orden.
**/
    for_each(nums.begin(), nums.end(), [](int &n){ n++; });
/* ========================================================== */

/* 
 Bounds
**/

 /*==================================================================*
  |                 |                        |                       |
  | Se Busca el...  |        Codificar       |      Si no existe:    |    
  |                 |                        |                       |
  ====================================================================
  | Primero Mayor o |       lower_bound      |                       | 
  | Igual.          |                        |                       |
  ===========================================|      Retorna end()    |    
  | Primero Mayor   |       upper_bound      |                       |
  ====================================================================
  | Ultimo Menor o  |      upper_bound-1     | Si el bound es igual  |  
  | Igual           |                        | a begin(), no existe, |
  ===========================================| y restar 1 es un      | 
  | Ultimo Menor    |      lower_bound-1     | error.                |
  *=================================================================*/  
