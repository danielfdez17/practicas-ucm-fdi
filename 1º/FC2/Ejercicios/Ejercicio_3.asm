/*
 * FC2Ejer3.asm
 *
 *  Created on: 21/02/2022
 	if (x >= y) {
		x = x+2;
		y = y+2;
	}
	else {
		x = x-2;
		y = y-2;
	}
 */
 
 .global start
 .data
 X:		.word 0x05
 Y: 	.word 0x09
.text
start:	LDR R0, =X @ Cargo en R0 la dir de mem de X
		LDR R1, =Y @ Cargo en R1 la dir de mem de Y
		LDR R2, [R0] @ Cargo en R2 el contenido de la dir de mem de R0
		LDR R3, [R1] @ Cargo en R3 el contenido de la dir de mem de R1
IF:		CMP R2, R3 @ Comparo R2 con R3
		BLT ELSE @ Si R2 < R3, salto a la etiqueta ELSE
		ADD R2, #2 @ R2 += 2
		ADD R3, #2 @ R2 += 2
		B STORE @ Salto a la etiqueta STORE
ELSE:	SUB R2, #2 @ R2 -= 2
		SUB R3, #2 @ R3 -= 2
STORE:	STR R2, [R0] @ Guardo el contenido de R2 en la dir de mem que contiene R0
		STR R3, [R1] @ Guardo el contenido de R3 en la dir de mem que contiene R1
		B .
		.END


