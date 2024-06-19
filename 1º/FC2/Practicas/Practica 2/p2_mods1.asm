/*
 * FC2prac2_mods.asm
 *
 *  Created on: 10/03/2022
 */
 
.global start
.equ N,8 @ Constante que determina el tamaño de los arrays
.data
A: .word 7,3,25,4,75,2,1,1 @ Array sobre el que operar
NumMay: .word 0 @ Variable que guarda el numero de valores mayores que 5 del array A
.bss
B: .space 4*N @ Array en el que se guarda el array A ordenado de mayor a menor
max: .space 4 @ Variable que guarda el valor maximo del array A
ind: .space 4 @ Variable que guarda la posicion del valor maximo del array A
.text
start:	mov r0,#0 @ r0 = j
		ldr r2,=max @ r2 = &max
		ldr r3,[r2] @ r3 = max
		ldr r4,=ind @ r4 = &ind
		ldr r5,[r4] @ r5 = ind
		ldr r6,=A @ r6 = &A
		ldr r7,=B @ r7 = &B
		ldr r9,=NumMay @ r9 = &NumMay
		ldr r11,[r9] @ r11 = NumMay
for1:	cmp r0,#N @ Comparo j con N
		bge endfor1 @ j >= N
		mov r1,#0 @ i = 0
		mov r3,#0 @ max = 0
for2:	cmp r1,#N @ Comparo i con N
		bge endfor2
		ldr r8,[r6,r1,lsl#2] @ r8 = A(i)
if2:	cmp r0,#1 @ Comparo j con 0
		bge endif2 @ Salto si j es mayor o igual que 1
if3:	cmp r8,#5 @ Comparo los valores del array con 5
		blt endif3 @ Salto si A(i) < 5
		add r11,r11,#1 @ NumMay++
		str r11,[r9] @ Escribo en memoria el valor de NumMay
endif3:
endif2:
if:		cmp r8,r3 @ A(i) con max
		ble endif @ A(i) <= max
		mov r3,r8 @ r3 = A(i)
		str r3,[r2] @ max = A(i)
		mov r5,r1 @ r5 = i
		str r5,[r4] @ ind = r5
endif:	add r1,r1,#1 @ i++
		b for2
endfor2:
		ldr r10,[r6,r5,lsl#2] @ r10 = A(ind)
		str r10,[r7,r0,lsl#2] @ Escribo el valor de A(ind) en la posicion de memoria de B(j)
		mov r10,#0 @ r10 = 0
		str r10,[r6,r5,lsl#2] @ Escribo en la posicion de memoria de A(ind) un 0
		add r0,r0,#1 @ j++
		b for1
endfor1:b .
		.end
