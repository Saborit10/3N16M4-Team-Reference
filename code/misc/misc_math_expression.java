/* Procesar Expresiones Matematicas   
 - Tested: http://codeforces.com/gym/100676/problem/A
**/

ScriptEngineManager mgr = new ScriptEngineManager();
ScriptEngine engine = mgr.getEngineByName("JavaScript");
        
Scanner sc = new Scanner(System.in);

while(sc.hasNextLine ())
    System.out.println(engine.eval(sc.nextLine()));
        
