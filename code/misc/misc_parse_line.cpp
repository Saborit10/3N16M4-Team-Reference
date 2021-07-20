/* Procesar una linea Completa
 - Lee una linea y la divide en enteros, guardandolos en el arreglo A
 - En el codigo, 99 es el maximo numero de caracteres que seran leidos
   de la entrada, y '\n' es el delimitador. 
**/

int A[5];
char S[100000];
char *in;

cin.getline(S, 99, '\n')
        
cant = 0;
for( in=strtok(S, " "); in; in=strtok(NULL, " ") )
    A[cant++] = atoi(in);
