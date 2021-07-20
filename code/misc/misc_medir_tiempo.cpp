/* Mide el tiempo que demora un fragmento de codigo en 
   ejecutarse
 - La respuesta se da en segundos
**/

auto _l = std::chrono::high_resolution_clock::now();
    
/* Aqui se pone el codigo a ser medido */        
    
auto _r = std::chrono::high_resolution_clock::now();
    
std::chrono::duration<double> diff = _r - _l;
cerr << diff.count() << endl;
