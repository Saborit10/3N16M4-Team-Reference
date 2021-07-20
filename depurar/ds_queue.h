 /* Doble Stack Queue 
  * 
  * - Soporta la operacion de maximo (minimo) en los
  * elementos que contiene
  * 
  *  - Para el minimo : 
  *     - numeric_limits<T>::min() ---->  numeric_limits<T>::max() 
  *     - ans < s1.top().second ------->  ans < s1.top().second
  *     - max(s2.top().first... ------->  min(s2.top().first...
  *     - max(val, ... ---------------->  min(val, ...
  *  - O tambien puedes introducir el opuesto del valor y cuando 
  *    lo saques de la cola, multiplicarlo por -1. 
  *  
  * - (Not Tested)
  * */
 
 template <class T>
 struct ds_queue{
     stack< pair<T, T> > s1, s2;

     int size(){ return s1.size() + s2.size(); }
     int empty(){ return s1.empty() && s2.empty(); }

     T top(){
        T ans = numeric_limits<T>::min();

        if( !s1.empty() && ans < s1.top().second )
            ans = s1.top().second;
        if( !s2.empty() && ans < s2.top().second )
            ans = s2.top().second;

        return ans;
     }

     void push(T val){
         if( s2.empty() )
             s2.push({val, val});
         else
             s2.push({val, max(val, s2.top().second)});
     }

     void pop(){
         if( s1.empty() ){
              while( !s2.empty() ){
                  if( s1.empty() )
                      s1.push({s2.top().first, s2.top().first});
                  else
                      s1.push({s2.top().first, max(s2.top().first, s1.top().second)});
                  s2.pop();
              }
         }
         assert( !s1.empty() );
         s1.pop();
     }
 };
