/* Set con Order Statistics en la STL 
- Para usarlo como multiset se guardan los elementos como un par 
  {element, id} y asi diferenciarlos. Luego para hacer referencia a
  un elemento se busca el par {element, 0}.
- Se detallan lo metodos para que funcione como multiset.
- Tested: https://codeforces.com/contest/459/problem/D
**/

/* =============================================================
 - Incluir las siguientes bibliotecas
**/ 
    #include <ext/pb_ds/assoc_container.hpp>
    #include <ext/pb_ds/tree_policy.hpp>
    using namespace __gnu_pbds;
/* =============================================================
 - Declaracion del tipo
**/
    typedef tree<
        pair<int, int>,
        null_type,
        less< pair<int, int> >,
        rb_tree_tag,
        tree_order_statistics_node_update>
    ordered_set;
/* =============================================================
 - Inicializacion
**/
    int t = 0;
    ordered_set Set;
/* =============================================================
 - Inserta un elemento x en el conjunto
**/
    Set.insert( {x, ++t} );
/* =============================================================
 - Eliminar un elemento x del conjunto
**/
    Set.erase( Set.lower_bound({x, 0}) );
/* =============================================================
 - Cantidad de menores que x
 **/
    Set.order_of_key( {x, 0} )
/* =============================================================
 - Cantidad de mayores o iguales que x
 **/ 
     Set.size() - Set.order_of_key( {x, 0} );
/* =============================================================
 - Cantidad de mayores que x
**/ 
    Set.size() - Set.order_of_key( {x + 1, 0} );
/* =============================================================
 - Devuelve un iterador al elemeto en la posicion p (0-indexed) 
**/
    Set.find_by_order(p)
/* ========================================================== */
