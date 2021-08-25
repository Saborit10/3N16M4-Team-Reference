# 3N1?M4 Team Reference

## Requerimientos

* python 2
* latex

## Estructura

* `code` es una carpeta que contiene los codigos con los que se genera el pdf final.
* `depurar` contiene los codigos que puede que se agregen al pdf pero hay que arreglar o los que se sacaron porque ya no se necesitaban.
* `old_codes` contiene versiones viejas de codigos que fueron sustituidas por otras que ahora se prefieren. 
* `test_pending` contiene los codigos que se quieren agregar al pdf final pero que no han podido probarse.
* `TODO.txt` lista de cosas que somos muy vagos para terminar. Aqui se incluye la correccion de errores de ortografia, etc.
* `contest.txt` es el indice de los codigos, distribuidos por seccion.
* `pdf.py` es el script en python que construye el pdf final.

## Agregar un Codigo al Proyecto

* Copiar el codigo a la carpeta apropiada dentro de la carpeta `code`.
* Agregar la linea correspondiente al archivo `contents.txt`, como se indica al principio de dicho archivo.
* Si se quieren ver los cambios al pdf final construirlo (ver seccion Construir el PDF Final).

## Construir el PDF Final

* Abrir un terminal en la carpeta raiz del proyecto.
* Correr la orden `python pdf.py`
* Esta construccion, hecha en su maquina no se guarda en los cambios al proyecto.

## Normas para el Formato del Team Reference

* Encabezar cada documento con un comentario de forma igual al de los codigos ya existentes. 
* Al final del encabezado indicar la complejidad temporal y espacial del algortimo o de cada metodo de la estructura de datos.
* Comentar todo lo que se pueda ente lineas, cuidando la legibilidad del codigo.
* Es IMPORTANTE que cada linea del codigo no exceda los 70 caracteres. De ser asi en el pdf final aparecera dividida en dos.
* Como acordamos, hay que agregar codigos que esten listos para copiar y funciones cambiando la menor cantidad de cosas. 
