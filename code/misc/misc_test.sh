# Este es mi archivo bash para revisar
# - Tanto el programa 'check' como el generador gen.py escriben y leen
# de la entrada/salida estandar. 
 
#!/bin/bash
for((i=1; ;++i))
do
  python gen.py>int
  
  echo "Testing Number:" $i
  
  .././a < int > out1 
  ./check < int > out2 
  
  if !(diff out1 out2) 
  then
    break
  fi
done
