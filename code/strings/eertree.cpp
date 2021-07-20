/* Palindromic Tree
 - Tested on: http://acm.timus.ru/problem.aspx?space=1&num=1960
**/
#define SIGMA 26 

struct node{
    int a, b, link;
    int ins[SIGMA];    
    
    node(){
         a = b = link = 0;;
         memset(ins, 0, sizeof ins);                
    }
    node(int _a, int _b, int _link){
         a = _a, b = _b, link = _link;
         memset(ins, 0, sizeof ins);                
    }
};

struct eertree{
    int nod, sz;
    vector<node> T;
    string S;
    
    eertree(){
        T = vector<node>(MX); 
        T[1] = node(1, -1, 1);     
        T[2] = node(1, 0, 1);
        nod = 1, sz = 2;             
    }
    
    int size(){ return sz - 2; }
    
    void add(char c){
        int t = nod, len;
        S += c;
        
        while( true ){
            len = T[t].b - T[t].a + 1;
        
            if( S.size() - len > 1 && S[S.size()-len-2] == c )
                break;
            t = T[t].link;    
        }
        
        if( T[t].ins[c -'a'] ){
            nod = T[t].ins[c -'a'];
            return;    
        }
        
        T[t].ins[c -'a'] = ++sz;
        T[sz] = node(S.size()-len-2, S.size()-1, 0);
        
        t = T[t].link;
        nod = sz;
        
        if( T[nod].b - T[nod].a == 0 ){
            T[nod].link = 2;
            return;    
        }
        
        while( true ){
            len = T[t].b - T[t].a + 1;
            
            if( S.size() - len > 1 && S[S.size()-len-2] == c )        
                 break; 
            t = T[t].link;     
        }
        
        T[nod].link = T[t].ins[c-'a'];    
    }    
}; 
