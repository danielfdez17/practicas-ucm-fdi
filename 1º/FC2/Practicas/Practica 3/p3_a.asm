/*
 * FC2prac3.asm
 *
 *  Created on: 21/03/2022
 */
 
 // APARTADO A
/*
.extern _stack
.global start
.equ N,4
.data
A: .word 7,3,25,4
.bss
max: .space 4
ind: .space 4
.text
start:
		ldr sp, =_stack @ sp = &_stack
		mov fp, #0 @ Se actualiza el fp a 0
		ldr r0, =A @ r0 = &A
		mov r1, #N @ r1 = N
		bl MAX @ Salta a la etiqueta MAX y en lr se almacena la dir de la siguiente instrucción
		ldr r4, =ind @ r4 = &ind
		str r0, [r4] @ r4 = valor de retorno de la función MAX
		b .

MAX:	push {r4-r8,fp,lr} @ Se guardan en la pila los valores de los registros que se usan en la función MAX
		@ Guardo lr por si en las modificaciones es necesario llamar a otra función dentro de MAX
		add fp, sp, #24 @ Se ajusta el marco de pila en función de los registros que se usen
		@ 24 = 4(bytes)*(7(nº_reg_usados)-1(registro))
		mov r4, #0 @ i = 0
		ldr r5, =max @ r5 = &max
		mov r6, #0 @ max = 0
		mov r7, #0 @ ind = 0

for:	cmp r4, r1 @ Comparo i con N
		bge endfor @ Salto si i >= N
		ldr r8, [r0,r4,lsl#2] @ r8 = A(i) = MEM(r0 + r5*2^2)

if:		cmp r8, r6 @ Comparo A(i) con max
		ble endif @ Salto si A(i) <= max
		mov r6, r8 @ max = A(i)
		str r6, [r5] @ Se escribe A(i) en memoria
		mov r7, r4 @ Se copia/guarda el valor de i

endif:	add r4, r4, #1 @ i++
		b for

endfor:	mov r0, r7 @ r0 = r7 = índice del valor máximo del vector (r0 = registro de retorno de MAX)
		sub sp, fp, #24 @ Reestablece el marco de la pila a como estaba antes de llamar a la función MAX
		pop {r4-r8,fp,lr} @ Se restauran los valores de los registros usados en MAX
		mov pc, lr @ Se guarda en el pc la dirección de la siguiente instrucción
		.end
*/
