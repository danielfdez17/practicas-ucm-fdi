/*
 * FC2prac1.asm
 *
 *  Created on: 16/02/2022
 	C = 0
	while( A >= B ) {
		A = A - B
		C = C + 1
 	}
 */
 
 .global start
 .data
 A:		.word 0x06
 B:		.word 0x03
 C:		.word 0x00

 .bss
 .text
 start:
 		LDR R1, =C // Cargo en R1 la direccion de memoria de C
 		LDR R2, =A // Cargo en R2 la direccion de memoria de A
 		LDR R3, =B // Cargo en R3 la direccion de memoria de B
 		//LDR R7, =D // Cargo en R7 la direccion de memoria de D
 		LDR R4, [R2] // (ldr r4, A) Cargo en R4 el contenido de la direccion de memoria almacenada en R2
 		LDR R5, [R3] // (ldr r5, B)Cargo en R5 el contenido de la direccion de memoria almacenada en R3
 		LDR R6, [R1] // (ldr r6, C)Cargo en R6 el contenido de la direccion de memoria almacenada en R1
WHILE:	CMP R4, R5 // Comparo los valores de A y B
		BLT SALIR // Si R4 < R4 salto a la etiqueta SALIR
		SUB R4, R4, R5 // A -= B
		ADD R6, R6, #1 // C++
		B WHILE // Salto a la etiqueta WHILE porque no se ha terminado el bucle
SALIR:	STR R6, [R1] // Almaceno el contenido de R2 en la variable A
			B .
			.END


