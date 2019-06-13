//fibonacci

//load arguments
movs r1, 1
movs r2, 1
movs r4, 233

//compute next number
COMPUTE: adds r3, r1, r2
mov  r1, r2
mov  r2, r3
cmp  r2, r4
bne COMPUTE
noop

//finished
//post condition
//r1 = 144
//r2 = 233
//r3 = 233
//r4 = 233
