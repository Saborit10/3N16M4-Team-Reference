/* Scaling Optimization
    [Arreglar para la nueva implementacion de Dinic]!!!

 - Se trata de una optimizacion que puede hacer que el Algoritmo de 
   Dinic corra en O(V*E*log(max_edge)).
 - Para ello se agragan unas pocas lineas
 - Tested on: USACO 2005 Marzo: Bovinas Ombrofobicas
**/

// Agragar ma y th como atributos. Inicializar ma a -1 en el
// constructor.

// Al final de add_edge()
ma = max(ma, c);

//En la condicion para ir a i.nwn en el metodo bfs, agregar:
i.cost >= th

//En la condicion para ir a nn en el metodo augment, agregar:
ct >= th

// El metodo throw_flow quedaria:
int64 throw_flow(){
    int64 mf = 0;
    th = ma;
    
    do{
        while( bfs() ){
            while( augment(ni) ){
                resolve(nf, INF);
                mf += f;    
            }
        }
        th >>= 1;
    }while( th );
    return mf;
} 
