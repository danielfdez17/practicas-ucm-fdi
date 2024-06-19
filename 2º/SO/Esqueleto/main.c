#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Orden a cumplir en el tablon.
int tablon; 

// E2. Variables para sincronización. 

// E2. Variables globales.

typedef struct {
  int id;         // Identificador del obrero.
  int nordenes; // Numero de ordenes a leer/ejecutar.
}obrero_t;

typedef struct {
  int nobreros; // Numero de obreros a cargo.
  int nordenes; // Numero de ordenes a colgar.
}capataz_t;

void escribeOrden( int Norden, int Nobreros ) {
  int i;

  printf( "[Capataz ] Esperando para escribir nueva orden\n" );

  // E2. Espera si hay obreros pendientes de leer orden

  // Escribir siguiente orden en el tablon.
  tablon = Norden;
  
  printf( "[Capataz ] Nueva orden escrita (%d)\n", tablon );

  // E2. Avisa a los obreros porque hay una nueva orden en el tablón.
  
}

// Funcion de entrada para hilo capataz
void * capataz( void * arg ){
  capataz_t * capataz_info = NULL; // E1. Recogida de argumentos.
  int Nobreros; // E1. Número de obreros a cargo.
  int Nordenes; // E1. Número de ordenes a colgar.
  int Norden = 0;

  while( Norden++ < Nordenes ) 
	  escribeOrden( Norden, Nobreros );
}

int leeorden( int id ) {
  int orden;

  printf( "[Obrero %d] Esperando orden\n", id );
 
  // E2. Espera si el tablon esta vacio, o si lo que hay en el tablon no lo leyo ya este mismo obrero. 

  // Recoge la orden del tablon.
  orden = tablon;

  // E2. Informa de que ya ha leido el tablon y avisa si es necesario para que el capaz cuelgue una nueva orden.

  printf( "[Obrero %d] Orden leída (%d)\n", id, orden );

  return orden;
}

void trabaja( int id, int orden ){
  printf( "[Obrero %d] Trabajando (%d)\n", id, orden );
  sleep( rand()%10 );
  printf( "[Obrero %d] Finaliza orden (%d)\n", id, orden );
}

// Funcion de entrada para hilo obrero
void * obrero( void * arg ){
  obrero_t * obrero_info = NULL; // E1. Recogida de argumentos.
  int id;                        // E1. Identificador de obrero.
  int Nordenes;                  // E1. Número de ordenes a ejecutar.

  int Norden = 0;
  int orden;

  while( Norden++ < Nordenes )
  {
	  orden = leeorden( id );
	  trabaja( id, orden );
  }

}

int main( int argc, char * argv[] )
{

  int Nobreros = 0; // Primer argumento del programa.
  int Nordenes = 0; // Segundo argumento del programa.

  // E1. Creación de estructuras de datos dinámicas para argumentos de cada hilo (si es necesario).
  
  // E1. Creación de hilo para capataz (función capataz).
  
  // E1. Creación de hilos para obreros (función obrero).

  // E1. Espera a la finalización de hilos.

  // E1. Liberación de estructuras de datos dinámicas (si es necesario).
  
  // E1. Liberación de otros recursos.

}
