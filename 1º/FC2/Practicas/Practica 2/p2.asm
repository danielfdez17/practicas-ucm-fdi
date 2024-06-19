/*
 * FC2prac2b.asm
 *
 *  Created on: 23/02/2022
	B)
	#define N 8
	int A[N]={7,3,25,4,75,2,1,1};
	int B[N];
	int max, ind;
	for(j=0; j<N; j++){
		max=0;
		for(i=0; i<N; i++){
			if(A[i]>max){
				max=A[i];
				ind=i;
			}
		}
		B[j]=A[ind];
		A[ind]=0;
	}
 */
 
.global start
.equ N,8
.data
A: .word 7,3,25,4,75,2,1,1 @ Vector sobre el que operar
.bss
B: .space 4*N @ Vector en el que se guarda el vector A ordenado de mayor a menor
max: .space 4
ind: .space 4
.text
start:	mov r0,#0 @ r0 = j
		mov r1,#0 @ r1 = i sobra porque ya lo hago dentro del for
		ldr r2,=max @ r2 = &max
		ldr r3,[r2] @ r3 = max
		ldr r4,=ind @ r4 = &ind
		ldr r5,[r4] @ r5 = ind
		ldr r6,=A @ r6 = &A
		ldr r7,=B @ r7 = &B
for1:	cmp r0,#N @ j con N
		bge endfor1 @ j >= N
		mov r1,#0 @ i = 0
		mov r3,#0 @ max = 0
for2:	cmp r1,#N @ i con N
		bge endfor2
		ldr r8,[r6,r1,lsl#2] @ r8 = A(i)
if:		cmp r8,r3 @ A(i) con max
		ble endif @ A(i) <= max
		mov r3,r8 @ r3 = A(i)
		str r3,[r2] @ max = A(i)
		mov r5,r1 @ r5 = i
		str r5,[r4] @ ind = r5
endif:	add r1,r1,#1 @ i++
		b for2
endfor2:
		@ldr r9,[r7,r0,lsl#2] @ r9 = B(j)
		ldr r10,[r6,r5,lsl#2] @ r10 = A(ind)
		@mov r9,r10 @ B(j) = A(ind)
		@str r9,[r7,r0,lsl#2] @ Escribir en la pos de mem de B(j) el valor de A(ind)
		str r10,[r7,r0,lsl#2]
		mov r10,#0 @ A(ind) = 0
		str r10,[r6,r5,lsl#2] @ Escribir en la pos de mem de A(ind) un 0
		add r0,r0,#1 @ j++
		b for1
endfor1:b .
		.end
