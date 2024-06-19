
.global rgb2gray
.equ COEF1, 3483
.equ COEF2, 11718
.equ COEF3, 1183
.text

rgb2gray: // r0 = R, r1 = G, r2 = B
  		ldr r3, =COEF1
  		mul r0, r3, r0 // (r0 = r3*r0) == (gris = c1*R)
  		ldr r3, =COEF2
  		mla r0, r3, r1, r0 // (r0 = r0 + r3*r1) == (gris = gris + c2*G) == (gris += c2*G)
  		ldr r3, =COEF3
  		mla r0, r3, r2, r0 // (r0 = r0 + r3*r2) == (gris = gris + c3*B) == (gris += c3*B)
  		mov r0, r0, lsr #14 // gris /= 14 (r0 = r0 desplazado 14 bits a la dcha)
  		// mov r0, r0, lsr #14 == lsr r0, r0, #14; (lsr == logical shift right)
  		mov pc, lr
  		.end
*/

/*
.global RGB2GrayMatrix // de C a ensamblador
.equ N,128
.equ M,128
.text

RGB2GrayMatrix:
		push {r4-r8,fp,lr} // Se vuelcan en la pila los registros que se van a usar en esta función
		add fp,sp,#24 // Se actualiza el marco de pila (24 = 4 * (7-1))
		sub sp,sp,#4 // Se reserva espacio en la pila para los dos parámetro
		str r0,[fp,#-28] // Se guarda la dir de mem de orig[N][M] en la pila
		str r1,[fp,#-32] // Se guarda la dir de mem de dest[N][M] en la pila
		mov r4,#0 // r4 = i
		mov r5,#0 // r5 = j
		mov r6,r0 // r6 = r0 = orig[N][M]
		mov r7,r1 // r7 = r1 = dest[N][M]
		mov r8,#N // r8 = N = M (solo cargo una variable porque su valor es el mismo)

for1:	cmp r4,r8 // Se compara i con N
		bge endfor1 // Salta si i >= N

for2:	cmp r5,r8 // Se compara i con M(N)
		bge endfor2 // Salta si j >= M(N)
		ldrb r0,[r6] // Carga en r0 el primer byte de la dir de mem que indica r6 y los demás a 0
		// r0 = orig[N][M].R
		add r6,r6,#1 // Se incrementa en uno para obtener la siguiente pos de mem de orig[N][M]
		ldrb r1,[r6]
		// r1 = orig[i][j].G
		add r6,r6,#1 // Se incrementa en uno para obtener la siguiente pos de mem de orig[N][M]
		ldrb r2,[r6]
		// r2 = orig[i][j].B
		bl rgb2gray // Se llama a la función rgb2gray para obtener el valor de dest[i][j]
		strb r0,[r7,#0] // Guarda el valor de dest[i][j] en el primer byte de la pos de mem que indica r7
		add r6,r6,#1 // Se incrementa en uno para obtener la siguiente pos de mem de orig[N][M]
		add r7,r7,#1 // Se incrementa en una para obtener la siguiente pos de mem de dest[N][M]
		add r5,r5,#1 // j++
		b for2

endfor2:
		add r4,r4,#1 // i++
		mov r5,#0 // j = 0
		b for1

endfor1:
		sub sp,fp,#24 // Se reestablece el marco de pila
		pop {r4-r8,fp,lr} // Se restauran los valores
		mov pc,lr // Se carga la dir de mem de la siguiente instrucción a ejecutar
		b .
		.end
*/
