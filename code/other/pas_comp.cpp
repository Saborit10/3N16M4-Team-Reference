// Path Compression

map<int, int>pc;

void pas_comp (){
     int cont = 0;
     for ( auto it = pc.begin(); it != pc.end(); it++ )
          it->second = ++cont;
}
