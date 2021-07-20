/* Pollar-Rho Algorithm
 - Dado un entero n <= 10^18, llena el vector ans con los divisores 
   de n, en cualquier orden.  
 - Tested on: [link del contest]
**/
static ArrayList<Long> ans = new ArrayList<>();
static final BigInteger TWO = BigInteger.valueOf(2);

static BigInteger PollarRho(long n){
    if( n % 2 == 0 ) 
        return TWO;
    
    BigInteger N = BigInteger.valueOf(n);
    
    while( true ){
        BigInteger x = 
                    BigInteger.valueOf((long)(Math.random() * (n-1)));
        BigInteger y = new BigInteger(x.toString());
        BigInteger c = 
                    BigInteger.valueOf((long)(Math.random() * (n-1)));
        
        if( c.compareTo(BigInteger.ZERO) == 0 || 
            c.compareTo(TWO) == 0 )
            c = BigInteger.ONE;
        
        for(int i=1, k=2;; i++){
            x = x.multiply(x).remainder(N);
            
            if( x.compareTo(c) >= 0 ) x = x.subtract(c);
            else x = x.add(N.subtract(c));
            
            if( x.compareTo(N) == 0 ) 
                x = BigInteger.ZERO;
            if( x.compareTo(BigInteger.ZERO) == 0 ) 
                x = N.subtract(BigInteger.ONE);
            else 
                x = x.subtract(BigInteger.ONE);
            
            BigInteger d = null;
            if( x.compareTo(y) > 0 )
                d = x.subtract(y);
            else
                d = y.subtract(x);
            
            d = d.gcd(N);
            
            if( d.compareTo(N) == 0 ) 
                break;
            
            if( d.compareTo(BigInteger.ONE) != 0 )
                return d;
            if( i==k ){
                y = new BigInteger(x.toString());
                k<<=1;
            }
        }
    }
}
    
static void fact(long n){
    if( n==1 ) return;
    if( BigInteger.valueOf(n).isProbablePrime(10) ){
        ans.add(n);
        return;
    }
    
    long p = PollarRho(n).longValue();
    
    fact(p);
    fact(n/p);
} 

