/* Fast Hash
 - Funcion de dispersion. Dada una cadena, retorna un entero de 64 bits.
**/

// Version de la funcion splitmix. Dado un entero sin signo de 64 bits,
// retorna un entero sin signo de 32 bits.
inline uint32_t to32(uint64_t x) {
	x += 0x9e3779b97f4a7c15;
	x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
	x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
	return (x ^ (x >> 31)) >> 32;
}

const int BASE1 = 29; // Bases del hash
const int BASE2 = 31;

uint64_t fast_hash(string S){
	auto hash32 = [&](int base){
		uint64_t ans = 0, pot = 1;
	
		for(int i=0; i < len(S); i++){
			int c = S[i] - 'a';
			
			ans = to32(ans + c * pot);
			pot = to32(pot * base);
		}
		return ans;
	};
	return hash32(BASE1) + (hash32(BASE2) << 32);
}
