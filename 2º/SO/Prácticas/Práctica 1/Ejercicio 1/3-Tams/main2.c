#include <stdio.h>


/******** TAREAS *****
 * Compila el código y trata de ejecutarlo. Contesta a las cuestiones
 * 1. ¿Tenemos un problema de compilación o de ejecución?
		(Sí, no se puede declarar un array de enteros con una variable que no sea constante)
 * 2. ¿Por qué se da el problema?. Soluciónalo, compila y ejecuta de nuevo.
		(Constante global, o dato inmediato (7))
 * 3. a,b,c, y x están declaradas de forma consecutiva. ¿Sus direcciones son concesutivas?
		(Sí lo son)
 * 4. ¿Qué significa el modificar "%lu" en printf()?
		()
 * 5. ¿A qué dirección apunta "pc"? ¿Coincide con la de alguna variable anteriormente declarada? Si es así, ¿coinciden los tamaños de ambas?
		Apunta a x, y no coinciden los tamaños
 * 6. ¿Coincide el valor del tamaño de "array1" con el número de elementos del array? ¿Por qué?
 		No, el tamaño real es de 40 porque hay 10 enteros, es lógico que no coincidan
 		Si el tamaño fuera de un Byte (char) sí deberían coincidir
 * 7. ¿Coinciden las direcciones a la que apunta cadena1 con la de cadena2?
 		No
 * 8. ¿Por qué los tamaños (según sizeof()) de cadena1 y cadena2 son diferentes?
 		Porque cadena1 es un puntero a una cadena y cadena2 es un array de caracteres
***************/

#define ARRAY_SIZE  10

int a = 7;
unsigned long b = 8;
short c;
char x;
char* pc;

int array1[ARRAY_SIZE];
int array2[7];

char* cadena1 = "CADENA DE CARACTERES";
char cadena2[] = "CADENA DE CARACTERES";
int main()
{
	pc = &x;
	a = 16;
	printf("Direccion de a: %p Tam: %lu \n",&a,sizeof(a));
	printf("Direccion de b: %p Tam: %lu \n",&b,sizeof(b));
	printf("Direccion de c: %p Tam: %lu \n",&c,sizeof(c));
	printf("Direccion de x: %p Tam: %lu \n",&x,sizeof(x));
	printf("Direccion de pc: %p Direccion a la que apunta pc: %p Tam: %lu \n",
			&pc, pc, sizeof(pc));
	printf("Direccion de array: %p Direccion del elem 0: %p Tam de array: %lu \n",
			array1, &array1[0], sizeof(array1));
	printf("Direccion de cadena1: %p Direccion a la que apunta: %p Tam: %lu \n",
			&cadena1, cadena1, sizeof(cadena1));
	printf("Direccion de cadena2: %p Direccion a la que apunta: %p Tam: %lu \n",
			&cadena2, cadena2, sizeof(cadena2));
    return 0;
}
