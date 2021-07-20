/* Linea de Compilacion */
    g++ -std=c++17 -Wshadow -Wall -o %e %f -fsanitize=address 
    -fsanitize=undefined -D_GLIBCXX_DEBUG -g

/* Pragmas */
/* ==================================================================
    Will make GCC auto-vectorize for loops and optimizes floating 
    points better (assumes associativity and turns off denormals).
**/
    #pragma GCC optimize ("Ofast")
/* ==================================================================
    The function __builtin_popcount() is replaced to corresponding
    machine instruction. This can make the function run up to two 
    times faster. The method bitset::count() use __builtin_popcount() 
    call in implementation, so it's also affected by this.
**/
    #pragma GCC target("popcnt")
/* ==================================================================
    Can double performance of vectorized code, but causes crashes on
    old machines.
**/
    #pragma GCC target ("avx,avx2")
/* ==================================================================
    Kills the program on integer overflows (but is really slow).
**/
    #pragma GCC optimize ("trapv")
/* ================================================================*/

/* Tricks */
/* ==================================================================
    Converts segfaults into Wrong Answers. Similarly one can catch
    SIGABRT (assertion failures) and SIGFPE (zero divisions).
    _GLIBCXX_DEBUG failures generate SIGABRT (or SIGSEGV on gcc 5.4.0
    apparently).
**/
    signal(SIGSEGV, [](int) { _Exit(0); });
/* ==================================================================
     Kills the program on NaNs (1), 0-divs (4), infinities (8) and
     denormals (16).
**/
    feenableexcept(29);
/* =============================================================== */
