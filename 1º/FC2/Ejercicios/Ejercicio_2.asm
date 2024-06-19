/*
 * FC2Ejer2.asm
 *
 *  Created on: 18/02/2022
 	if (x >= y) {
		x = x+2;
		y = y-2;
	}
 */
 
.global start
.data
X:	.word 0x06
Y:	.word 0x05
.text
start:	LDR R0, =X  @ Cargo en R0 la dir de mem de X
		LDR R1, =Y @ Cargo en R1 la dir de mem de Y
		LDR R2,[R0] @ Cargo en R2 el contenido de la dir de mem de R0
		LDR R3,[R1] @ Cargo en R3 el contenido de la dir de mem de R1
IF:		CMP R2, R3 @ Comparo el contenido de R2 con el de R3
		BLT SALIR @ Si R2 < R3, salta a la etiqueta SALIR
		ADD R2, R2, #2 @ R0 += 2
		SUB R3, R3, #2 @ R1 -= 2
		STR R2, [R0] @ Guardo el contenido de R0 en la dir de mem que contiene R2
		STR R3, [R1] @ Guardo el contenido de R1 en la dir de mem que contiene R3
SALIR:	B .
		.END


