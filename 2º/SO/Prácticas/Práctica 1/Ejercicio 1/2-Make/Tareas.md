1. Examina el makefile, identifica las variables definidas, los objetivos
   (targets) y las reglas.
   VARIABLES: gcc, FLAGS, LIBS
   OBJETIVOS: %.o, all, .PHONY, clean
   REGLAS: 
   			%.o: %.c
   					$(CC) $(CFLAGS) -c -o $@ $<
   			all: aux.o init.o aux.h
   					gcc $(CFLAGS) -o prueba aux.o init.o $(LIBS)
   			.PHONY: clean
   			
   			clean: 
   					-re *.o prueba
2. Ejecuta make en la linea de comandos y comprueba las ordenes que ejecuta para
   construir el proyecto.
   EJECUTA: 
   	gcc -Wall -g -c -o aux.o aux.c
	gcc -Wall -g -c -o init.o init.c
	gcc -Wall -g -o prueba aux.o init.o -lm
	////////////////////////////////////////
3. Marca el fichero aux.c como modificado ejecutando touch aux.c. Después
   ejecuta de nuevo make. ¿Qué diferencia hay con la primera vez que lo
   ejecutaste? ¿Por qué? 
   EJECUTA: se salta la compilación de init.c, y se vuelve a ejecutar la compilación de
   			aux.c porque el archivo ha sido modificado
4. Ejecuta la orden make clean. ¿Qué ha sucedido? Observa que el objetivo clean
   está marcado como phony en la orden .PHONY: clean. ¿por qué? Para comprobarlo
   puedes comentar dicha línea del makefile, compilar de nuevo haciendo make, y
   después crear un fichero en el mismo directorio que se llame clean, usando el
   comando touch clean. Ejecuta ahora make clean, ¿qué pasa?
   1º Borra los archivos .o y ejecutables
   2º Evita que se ejecute un fichero con el mismo nombre
   3º Sigue ejecutándose igual
   4º Mensaje: "make: 'clean' está actualizado"
5. Comenta la linea LIBS = -lm poniendo delante una almoadilla (#). Vuelve a
   contruir el proyecto ejecutando make (haz un clean antes si es necesario).
   ¿Qué sucede? ¿Qué etapa es la que da problemas?
	Hay problemas porque se hacen referencias a funciones de una librería que no es
	linkeada
