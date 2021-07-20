/* Uso del Bitset
 - La complejidad de cualquier operacion que recorra el bitset, asi 
   como la memoria, se divide entre el tamanho de palabra de la 
   maquina.
 - Para optimizar el conteo de bits, utilizar el pragma (ver 
   seccion de optimizacion).
**/

/* Creacion */
/* N se convierte a binario y se guarda b */
bitset<MAX_SIZE> b(int N) 

/* Guarda los bits que representa S (formada por 0 o 1) */
bitset<MAX_SIZE> b(string S) 

/* Metodos y Operadores */
count()                  // Cuenta la cantidad de bits encendidos.
b[i]                     // Es una referencia al i-esimo bit.
!=, ==                   // Comparan el contenido de dos bitsets.
test(int pos)            // Retorna el bit en la posicion pos.
set(int pos, int val=1)  // Modifica el bit en la posicion pos.
&=, |=, ^=, ~            // Operadores Logicos.
<<=, >>=, <<, >>         // Operadores de Desplazamiento.
// OJO: En la representacion el bit menos significativo es el ultimo,
// por tanto, la cadena estara el reves.
string to_string         // Devuelve un string represent. los datos. 
unsigned long to_ulong   // Devuelve un unsigned long repr. los datos.
unsigned long long to_ullong   // Solo en (C++11).

/*====================== FUNCIONES OCULTAS =======================*/
/*
    Devuelve el primer bit encendido, o size() si esta vacio. 
*/
_Find_first()

/*
   Devuelve la proxima posicion que tiene un bit en uno, a partir 
   de la posicion i, o size() si no existe. 
*/
_Find_next(i) 
