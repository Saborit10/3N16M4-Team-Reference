/*
    Clase BigInteger de Java:
*/
nextBigInteger()        //De la clase Scanner lee el proximo BigInteger.
add(BigInteger a)       //retorna this + a  
subtract(BigInteger a)  //retorna this - a
multiply(BigInteger a)  //retorna this * a
pow(int exponent)       // retorna this ^ exponent
divide(BigInteger a)    // retorna this / a
remainder(BigInteger a) // retorna this % a
mod(BigInteger a): retorna this mod a
divideAndRemainder(BigInteger a): retorna [this / a, this % a]
isProbablePrime(int certainty)  es una prueba de primalidad probabilistica basada en el algoritmo Miller-Rabin. Si la funcion retorna true, entonces la probabilidad de que el BigInteger probado sea primo es de  Con certainty = 10, la probabilidad es de  0.9990234375.
