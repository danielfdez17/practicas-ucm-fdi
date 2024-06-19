#include <stdio.h>
#include <stdlib.h>

/********* TAREAS ************
 * Compila y ejecuta el código. Responde a las siguientes cuestiones:
 *  1. ¿Cuánstos bytes se reservan en memoria con la llamada a malloc()?
 		127 * 4
 *  2. ¿Cuál es la dirección del primer y último byte de dicha zona reservada?
 		&ptr[0] y &ptr[nelem - 1]		
 *  3. ¿Por qué el contenido de la dirección apuntada por "ptr" es 7 y no 5 en el primer printf()?
 		Porque la última instrucción que se ejecuta es ptr[0] = 7 === *ptr = 7
 *  4. ¿Por qué se modfica el cnotenido de ptr[1] tras la sentencia *ptr2=15;?
 		Porque ptr2 avanza antes de modificar
 *  5. Indica dos modos diferentes de escribir el valor 13 en la dirección correspondiente a ptr[100].
 		ptr2 = ptr1[100]; ptr1[100] = 13; *ptr2 = 13;
 *  6. Hay un error en el código. ¿Se manifiesta en compilación o en ejecución?
 *     Aunque no se manifieste, el error está. ¿Cuál es?
 		En ningún momento.
 		Se libera el puntero ptr y se la asigna valor después de liberarlo
 *  ***********/
int nelem;

int main(void)
{
	int *ptr;
	int * ptr2;

	nelem = 127;
	ptr = (int*) malloc(nelem*sizeof(int));
	*ptr = 5;
	ptr[0] = 7;
	ptr2 = ptr;

	printf("Direccion a la que apunta ptr %p. Contenido de esa direccion: %d \n",
			ptr, *ptr);

	ptr[1] = 10;
	printf("Direccion a la que apunta ptr[1] %p. Contenido de esa direccion: %d \n",
			&ptr[1], ptr[1]);

	ptr2++;
	*ptr2 = 15;
	printf("Direccion a la que apunta ptr[1] %p. Contenido de esa direccion: %d \n",
			&ptr[1], ptr[1]);

	free(ptr);
	*ptr = 3;
	printf("Direccion a la que apunta ptr %p. Contenido de esa direccion: %d \n",
			ptr, *ptr);
	return 0;
}

