/* Debug function
**/

#define d(args...) { cerr << "("<< #args << ") --> (" << 
    err(args) << ")\n"; }   
string err() {return "";}
template<typename T, typename... Args>
string err(T a, Args... args) { return to_string(a) + " " + 
    err(args...); }
