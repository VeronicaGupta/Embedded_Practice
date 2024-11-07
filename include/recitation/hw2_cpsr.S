(a) ldr r1, =0xffffffff
 ldr
 add
 (b) ldr
 ldr
 cmn
 (c) ldr
 ldr
 adds
 (d) ldr
 ldr
 r2, =0x00000001
 r0, r1, r2
 r1, =0xffffffff
 r2, =0x00000001
 r1, r2
 r1, =0xffffffff
 r2, =0x00000001
 r0, r1, r2
 r1, =0xffffffff
 r2, =0x00000001
 addeq r0, r1, r2
 (e) ldr
 r1, =0x7fffffff
 ldr
 adds
 r2, =0x7fffffff
 r0, r1, r2