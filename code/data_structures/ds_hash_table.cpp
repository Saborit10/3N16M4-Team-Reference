/* Tabla Hash con API semejante a un unordered_map
 - Se especifica un tamanno inicial, el cual debe ser una potencia de
   2.
 - En teoria es mas rapida que un unordered_set
 - [BUSCAR MAS INFORMACION]
*/
struct chash{
    const uint64_t C = (int64)(2e18 * M_PI) + 71;
    int64 operator ()(int64 x)const{ return __builtin_bswap64(x*C); }
};

gp_hash_table<int64, int, chash> h({}, {}, {}, {}, {1<<16});
