/** Union Area (Sweep Line)
 * 
 *  - DELTA es el intervalo que se le suma a las coordenadas negativas   
 **/

const int DELTA = 100000000;

 struct event{
     int x, y1, y2, ty ;
    
     bool operator < (const event &p)const{
         return x!=p.x ? x < p.x : ty < p.ty;
     }
 };

 int N, last;
 int64 sol;
 vector<event> E;

 struct node{
     int64 x, xend, val, seg;
     node *R, *L;
     node(int64 a, int64 b){
         val = 0, R = NULL, L = NULL, x = a, xend = b, seg = 0;
     }

     void update(int a, int b, int c){
        if(x > b || xend < a)
           return;

        if(L==NULL) L = new node(x, mid);
        if(R==NULL) R = new node(mid+1, xend);

        if(a<=x && xend<=b)
           seg += c;
        else
           L->update(a, b, c), R->update(a, b, c);

        if( !seg )
           val = (x==xend)? 0ll : L->val + R->val;
        else
           val = xend - x + 1ll;
     }
 };

 int main(void){
     node ST = node(0, 2*DELTA);
     
     scanf("%d", &N);
     for(int i=1, a, b, c, d; i<=N; i++){
        scanf("%d%d%d%d", &a, &b, &c, &d);
        
        E.pb({a, b-1, d, 1});
        E.pb({c, b-1, d, 0});
     }
     
     sort(all(E));

     for(auto e: E){
         if( !e.ty ){
             sol += ST.val * (int64)(e.x - last);
             ST.update(e.y2 + DELTA, e.y1 + DELTA, -1);
         }
         else{
            sol += ST.val * (int64)(e.x - last);
            T.update(e.y2 + DELTA, e.y1 + DELTA, 1);
         }
         last =  e.x; 
     }

     printf("%lld\n", sol);
