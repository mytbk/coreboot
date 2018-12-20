global mrc_pch_init

extern mrc_sku_type
extern mrc_pch_revision
extern mrc_pch_iobp_read
extern mrc_pch_iobp_update

mrc_pch_init:
push ebp
mov ebp, esp
push edi
push esi
push ebx
lea esp, [esp - 0x3c]
call mrc_sku_type
mov dword [ebp - 0x34], eax
mov eax, dword [0xf0000060]
and eax, 0xfc000000
mov eax, dword [eax + 0xf80f0]
and eax, 0xfffffffe
mov dword [ebp - 0x38], eax ; [ebp - 0x38] = rcba
mov eax, dword [0xf0000060]
and eax, 0xfc000000
mov ax, word [eax + 0xf8002]
mov word [ebp - 0x2c], ax ; u16 [ebp - 0x2c] = DID
mov esi, dword [0xf0000060]
and esi, 0xfc000000
mov edx, dword [0xf0000060]
mov al, byte [esi + 0xfa092] ; D31:F2, SATA controller, PCS
test al, 0xf
setne al
cmp dword [ebp - 0x34], 1
jne loc_fffc8280  ; jne 0xfffc8280
mov cl, byte [esi + 0xfa092]
and cl, 0x30
je loc_fffc8273  ; je 0xfffc8273

loc_fffc7d10:
lea ecx, [ebp - 0x1c]
mov edx, 0xea000aac
mov eax, dword [ebp - 0x38]
call mrc_pch_iobp_read
jmp near loc_fffc8288  ; jmp 0xfffc8288

loc_fffc7d25:
mov al, byte [esi + 0xfa090] ; SATA, MAP
and eax, 0x1f
or eax, 0x60 ; up to 6 SATA ports @ D31:F2, AHCI mode
jmp short loc_fffc7d45  ; jmp 0xfffc7d45

loc_fffc7d33:
cmp dword [ebp - 0x34], 2
jne short loc_fffc7d4b  ; jne 0xfffc7d4b
mov al, byte [esi + 0xfa090]
and eax, 0x3f
or eax, 0x40

loc_fffc7d45:
mov byte [esi + 0xfa090], al

loc_fffc7d4b:
mov dword [ebp - 0x1c], 0xfffffe00
mov eax, dword [esi + 0xfa094]
and eax, 0xfffffe00
or eax, 0x183
mov dword [esi + 0xfa094], eax
mov ax, word [esi + 0xfa092]
or ax, 0x8000
mov word [esi + 0xfa092], ax
and edx, 0xfc000000
mov dword [ebp - 0x3c], edx
mov al, byte [edx + 0xe0410]
mov byte [ebp - 0x2d], al
call mrc_pch_revision
cmp eax, 3
ja short loc_fffc7da6  ; ja 0xfffc7da6
movzx edi, byte [eax + ref_fffcc32c]  ; movzx edi, byte [eax - 0x33cd4]
mov ebx, dword [eax*4 + ref_fffcc330]  ; mov ebx, dword [eax*4 - 0x33cd0]
jmp short loc_fffc7daa  ; jmp 0xfffc7daa

loc_fffc7da6:
xor ebx, ebx
xor edi, edi

loc_fffc7daa:
mov word [ebp - 0x2a], 0
jmp short loc_fffc7dcf  ; jmp 0xfffc7dcf

loc_fffc7db2:
sub esp, 0xc
mov ecx, dword [ebx + 4]
push dword [ebx + 8]
mov eax, dword [ebp - 0x38]
mov edx, dword [ebx]
call mrc_pch_iobp_update
add ebx, 0xc
inc word [ebp - 0x2a]
add esp, 0x10

loc_fffc7dcf:
cmp word [ebp - 0x2a], di
jne short loc_fffc7db2  ; jne 0xfffc7db2
call mrc_pch_revision
cmp eax, 6
ja short loc_fffc7def  ; ja 0xfffc7def
movzx edx, byte [eax + ref_fffcc340]  ; movzx edx, byte [eax - 0x33cc0]
mov ebx, dword [eax*4 + ref_fffcc348]  ; mov ebx, dword [eax*4 - 0x33cb8]
jmp short loc_fffc7df3  ; jmp 0xfffc7df3

loc_fffc7def:
xor ebx, ebx
xor edx, edx

loc_fffc7df3:
imul edx, edx, 0xc
mov al, byte [ebp - 0x2d]
and eax, 0x10
mov byte [ebp - 0x2e], al
lea edi, [ebx + edx]
mov dl, byte [ebp - 0x2d]
and edx, 0x20
mov byte [ebp - 0x2a], dl
jmp short loc_fffc7e88  ; jmp 0xfffc7e88

loc_fffc7e0d:
cmp dword [ebp - 0x34], 2
jne short loc_fffc7e48  ; jne 0xfffc7e48
mov eax, dword [ebx]
and eax, 0xfe00
cmp eax, 0x2000
jne short loc_fffc7e23  ; jne 0xfffc7e23
jmp short loc_fffc7e5c  ; jmp 0xfffc7e5c

loc_fffc7e23:
cmp eax, 0x2200
jne short loc_fffc7e2c  ; jne 0xfffc7e2c
jmp short loc_fffc7e69  ; jmp 0xfffc7e69

loc_fffc7e2c:
cmp eax, 0x2400
jne short loc_fffc7e39  ; jne 0xfffc7e39
test byte [ebp - 0x2d], 0x40
jmp short loc_fffc7e6d  ; jmp 0xfffc7e6d

loc_fffc7e39:
cmp eax, 0x2600
jne short loc_fffc7e6f  ; jne 0xfffc7e6f
cmp byte [ebp - 0x2d], 0
jns short loc_fffc7e6f  ; jns 0xfffc7e6f
jmp short loc_fffc7e85  ; jmp 0xfffc7e85

loc_fffc7e48:
cmp dword [ebp - 0x34], 1
jne short loc_fffc7e6f  ; jne 0xfffc7e6f
mov eax, dword [ebx]
and eax, 0xfe00
cmp eax, 0x2000
jne short loc_fffc7e62  ; jne 0xfffc7e62

loc_fffc7e5c:
cmp byte [ebp - 0x2e], 0
jmp short loc_fffc7e6d  ; jmp 0xfffc7e6d

loc_fffc7e62:
cmp eax, 0x2200
jne short loc_fffc7e6f  ; jne 0xfffc7e6f

loc_fffc7e69:
cmp byte [ebp - 0x2a], 0

loc_fffc7e6d:
jne short loc_fffc7e85  ; jne 0xfffc7e85

loc_fffc7e6f:
sub esp, 0xc
mov ecx, dword [ebx + 4]
push dword [ebx + 8]
mov eax, dword [ebp - 0x38]
mov edx, dword [ebx]
call mrc_pch_iobp_update
add esp, 0x10

loc_fffc7e85:
add ebx, 0xc

loc_fffc7e88:
cmp ebx, edi
jne short loc_fffc7e0d  ; jne 0xfffc7e0d
cmp word [ebp - 0x2c], 0x8c4f
sete dl
cmp word [ebp - 0x2c], 0x8c49
sete al
or dl, al
mov byte [ebp - 0x2f], dl
jne short loc_fffc7ecc  ; jne 0xfffc7ecc
cmp word [ebp - 0x2c], 0x8c41
sete dl
cmp word [ebp - 0x2c], 0x8c4b
sete al
or dl, al
jne short loc_fffc7ecc  ; jne 0xfffc7ecc
mov eax, dword [ebp - 0x2c]
add ax, 0x63bf
cmp ax, 6
ja loc_fffc7fe1  ; ja 0xfffc7fe1

loc_fffc7ecc:
call mrc_pch_revision
cmp eax, 3
ja short loc_fffc7ee6  ; ja 0xfffc7ee6
movzx edi, byte [eax + ref_fffcc364]  ; movzx edi, byte [eax - 0x33c9c]
mov ebx, dword [eax*4 + ref_fffcc368]  ; mov ebx, dword [eax*4 - 0x33c98]
jmp short loc_fffc7eea  ; jmp 0xfffc7eea

loc_fffc7ee6:
xor ebx, ebx
xor edi, edi

loc_fffc7eea:
mov word [ebp - 0x2a], 0
jmp short loc_fffc7f0f  ; jmp 0xfffc7f0f

loc_fffc7ef2:
sub esp, 0xc
mov ecx, dword [ebx + 4]
push dword [ebx + 8]
mov eax, dword [ebp - 0x38]
mov edx, dword [ebx]
call mrc_pch_iobp_update
add ebx, 0xc
inc word [ebp - 0x2a]
add esp, 0x10

loc_fffc7f0f:
cmp word [ebp - 0x2a], di
jne short loc_fffc7ef2  ; jne 0xfffc7ef2
call mrc_pch_revision
cmp eax, 6
ja short loc_fffc7f2f  ; ja 0xfffc7f2f
movzx edx, byte [eax + ref_fffcc378]  ; movzx edx, byte [eax - 0x33c88]
mov ebx, dword [eax*4 + ref_fffcc380]  ; mov ebx, dword [eax*4 - 0x33c80]
jmp short loc_fffc7f33  ; jmp 0xfffc7f33

loc_fffc7f2f:
xor ebx, ebx
xor edx, edx

loc_fffc7f33:
imul edx, edx, 0xc
mov al, byte [ebp - 0x2d]
and eax, 0x10
mov byte [ebp - 0x2e], al
lea edi, [ebx + edx]
mov dl, byte [ebp - 0x2d]
and edx, 0x20
mov byte [ebp - 0x2a], dl
jmp short loc_fffc7fc8  ; jmp 0xfffc7fc8

loc_fffc7f4d:
cmp dword [ebp - 0x34], 2
jne short loc_fffc7f88  ; jne 0xfffc7f88
mov eax, dword [ebx]
and eax, 0xfe00
cmp eax, 0x2000
jne short loc_fffc7f63  ; jne 0xfffc7f63
jmp short loc_fffc7f9c  ; jmp 0xfffc7f9c

loc_fffc7f63:
cmp eax, 0x2200
jne short loc_fffc7f6c  ; jne 0xfffc7f6c
jmp short loc_fffc7fa9  ; jmp 0xfffc7fa9

loc_fffc7f6c:
cmp eax, 0x2400
jne short loc_fffc7f79  ; jne 0xfffc7f79
test byte [ebp - 0x2d], 0x40
jmp short loc_fffc7fad  ; jmp 0xfffc7fad

loc_fffc7f79:
cmp eax, 0x2600
jne short loc_fffc7faf  ; jne 0xfffc7faf
cmp byte [ebp - 0x2d], 0
jns short loc_fffc7faf  ; jns 0xfffc7faf
jmp short loc_fffc7fc5  ; jmp 0xfffc7fc5

loc_fffc7f88:
cmp dword [ebp - 0x34], 1
jne short loc_fffc7faf  ; jne 0xfffc7faf
mov eax, dword [ebx]
and eax, 0xfe00
cmp eax, 0x2000
jne short loc_fffc7fa2  ; jne 0xfffc7fa2

loc_fffc7f9c:
cmp byte [ebp - 0x2e], 0
jmp short loc_fffc7fad  ; jmp 0xfffc7fad

loc_fffc7fa2:
cmp eax, 0x2200
jne short loc_fffc7faf  ; jne 0xfffc7faf

loc_fffc7fa9:
cmp byte [ebp - 0x2a], 0

loc_fffc7fad:
jne short loc_fffc7fc5  ; jne 0xfffc7fc5

loc_fffc7faf:
sub esp, 0xc
mov ecx, dword [ebx + 4]
push dword [ebx + 8]
mov eax, dword [ebp - 0x38]
mov edx, dword [ebx]
call mrc_pch_iobp_update
add esp, 0x10

loc_fffc7fc5:
add ebx, 0xc

loc_fffc7fc8:
cmp ebx, edi
jne short loc_fffc7f4d  ; jne 0xfffc7f4d

loc_fffc7fcc:
mov eax, dword [ebp - 0x2c]
and eax, 0xfffffffd
cmp ax, 0x8c44
jne loc_fffc80e6  ; jne 0xfffc80e6
jmp near loc_fffc8137  ; jmp 0xfffc8137

loc_fffc7fe1:
call mrc_pch_revision
cmp eax, 3
ja short loc_fffc7ffb  ; ja 0xfffc7ffb
movzx edi, byte [eax + ref_fffcc39c]  ; movzx edi, byte [eax - 0x33c64]
mov ebx, dword [eax*4 + ref_fffcc3a0]  ; mov ebx, dword [eax*4 - 0x33c60]
jmp short loc_fffc7fff  ; jmp 0xfffc7fff

loc_fffc7ffb:
xor ebx, ebx
xor edi, edi

loc_fffc7fff:
mov word [ebp - 0x2a], 0
jmp short loc_fffc8024  ; jmp 0xfffc8024

loc_fffc8007:
sub esp, 0xc
mov ecx, dword [ebx + 4]
push dword [ebx + 8]
mov eax, dword [ebp - 0x38]
mov edx, dword [ebx]
call mrc_pch_iobp_update
add ebx, 0xc
inc word [ebp - 0x2a]
add esp, 0x10

loc_fffc8024:
cmp word [ebp - 0x2a], di
jne short loc_fffc8007  ; jne 0xfffc8007
call mrc_pch_revision
cmp eax, 6
ja short loc_fffc8044  ; ja 0xfffc8044
movzx edx, byte [eax + ref_fffcc3b0]  ; movzx edx, byte [eax - 0x33c50]
mov ebx, dword [eax*4 + ref_fffcc3b8]  ; mov ebx, dword [eax*4 - 0x33c48]
jmp short loc_fffc8048  ; jmp 0xfffc8048

loc_fffc8044:
xor ebx, ebx
xor edx, edx

loc_fffc8048:
imul edx, edx, 0xc
mov al, byte [ebp - 0x2d]
and eax, 0x10
mov byte [ebp - 0x2e], al
lea edi, [ebx + edx]
mov dl, byte [ebp - 0x2d]
and edx, 0x20
mov byte [ebp - 0x2a], dl
jmp short loc_fffc80dd  ; jmp 0xfffc80dd

loc_fffc8062:
cmp dword [ebp - 0x34], 2
jne short loc_fffc809d  ; jne 0xfffc809d
mov eax, dword [ebx]
and eax, 0xfe00
cmp eax, 0x2000
jne short loc_fffc8078  ; jne 0xfffc8078
jmp short loc_fffc80b1  ; jmp 0xfffc80b1

loc_fffc8078:
cmp eax, 0x2200
jne short loc_fffc8081  ; jne 0xfffc8081
jmp short loc_fffc80be  ; jmp 0xfffc80be

loc_fffc8081:
cmp eax, 0x2400
jne short loc_fffc808e  ; jne 0xfffc808e
test byte [ebp - 0x2d], 0x40
jmp short loc_fffc80c2  ; jmp 0xfffc80c2

loc_fffc808e:
cmp eax, 0x2600
jne short loc_fffc80c4  ; jne 0xfffc80c4
cmp byte [ebp - 0x2d], 0
jns short loc_fffc80c4  ; jns 0xfffc80c4
jmp short loc_fffc80da  ; jmp 0xfffc80da

loc_fffc809d:
cmp dword [ebp - 0x34], 1
jne short loc_fffc80c4  ; jne 0xfffc80c4
mov eax, dword [ebx]
and eax, 0xfe00
cmp eax, 0x2000
jne short loc_fffc80b7  ; jne 0xfffc80b7

loc_fffc80b1:
cmp byte [ebp - 0x2e], 0
jmp short loc_fffc80c2  ; jmp 0xfffc80c2

loc_fffc80b7:
cmp eax, 0x2200
jne short loc_fffc80c4  ; jne 0xfffc80c4

loc_fffc80be:
cmp byte [ebp - 0x2a], 0

loc_fffc80c2:
jne short loc_fffc80da  ; jne 0xfffc80da

loc_fffc80c4:
sub esp, 0xc
mov ecx, dword [ebx + 4]
push dword [ebx + 8]
mov eax, dword [ebp - 0x38]
mov edx, dword [ebx]
call mrc_pch_iobp_update
add esp, 0x10

loc_fffc80da:
add ebx, 0xc

loc_fffc80dd:
cmp ebx, edi
jne short loc_fffc8062  ; jne 0xfffc8062
jmp near loc_fffc7fcc  ; jmp 0xfffc7fcc

loc_fffc80e6:
cmp ax, 0x8c4c
je short loc_fffc8137  ; je 0xfffc8137
cmp word [ebp - 0x2c], 0x8c5c
sete dl
cmp word [ebp - 0x2c], 0x8c50
sete al
or dl, al
jne short loc_fffc8137  ; jne 0xfffc8137
mov eax, dword [ebp - 0x2c]
and eax, 0xfffffff7
cmp ax, 0x8c42
je short loc_fffc8137  ; je 0xfffc8137
cmp byte [ebp - 0x2f], 0
jne short loc_fffc8137  ; jne 0xfffc8137
cmp word [ebp - 0x2c], 0x8c41
sete dl
cmp word [ebp - 0x2c], 0x8c4b
sete al
or dl, al
jne short loc_fffc8137  ; jne 0xfffc8137
mov eax, dword [ebp - 0x2c]
add ax, 0x63bf
cmp ax, 6
ja short loc_fffc8148  ; ja 0xfffc8148

loc_fffc8137:
mov eax, dword [esi + 0xfa098]
or eax, 0x400000
mov dword [esi + 0xfa098], eax

loc_fffc8148:
mov eax, dword [esi + 0xfa098]
or eax, 0x80000
mov dword [esi + 0xfa098], eax
mov dword [ebp - 0x1c], 0xffffe27f
mov eax, dword [esi + 0xfa098]
and eax, 0xffffe27f
or ah, 2
mov dword [esi + 0xfa098], eax
mov eax, dword [esi + 0xfa098]
or eax, 0x100000
mov dword [esi + 0xfa098], eax
mov eax, dword [esi + 0xfa098]
and eax, 0xffffff9f
or eax, 0x20
mov dword [esi + 0xfa098], eax
mov eax, dword [esi + 0xfa098]
or eax, 0x40000
mov dword [esi + 0xfa098], eax
cmp dword [ebp - 0x34], 1
jne short loc_fffc81d0  ; jne 0xfffc81d0
mov al, byte [esi + 0xfa092]
or eax, 0xf
mov byte [esi + 0xfa092], al
mov edx, dword [ebp - 0x3c]
mov al, byte [edx + 0xe0410]
test al, 0x10
jne loc_fffc8255  ; jne 0xfffc8255
jmp short loc_fffc8246  ; jmp 0xfffc8246

loc_fffc81d0:
cmp dword [ebp - 0x34], 2
jne loc_fffc8288  ; jne 0xfffc8288
mov edx, dword [ebp - 0x3c]
mov al, byte [edx + 0xe0410]
test al, al
js short loc_fffc81f6  ; js 0xfffc81f6
mov al, byte [esi + 0xfa092]
or eax, 1
mov byte [esi + 0xfa092], al

loc_fffc81f6:
mov edx, dword [ebp - 0x3c]
mov al, byte [edx + 0xe0410]
test al, 0x40
jne short loc_fffc8212  ; jne 0xfffc8212
mov al, byte [esi + 0xfa092]
or eax, 2
mov byte [esi + 0xfa092], al

loc_fffc8212:
mov edx, dword [ebp - 0x3c]
mov al, byte [edx + 0xe0410]
test al, 0x20
jne short loc_fffc822e  ; jne 0xfffc822e
mov al, byte [esi + 0xfa092]
or eax, 4
mov byte [esi + 0xfa092], al

loc_fffc822e:
mov edx, dword [ebp - 0x3c]
mov al, byte [edx + 0xe0410]
test al, 0x10
jne short loc_fffc8288  ; jne 0xfffc8288
mov al, byte [esi + 0xfa092]
or eax, 8
jmp short loc_fffc826b  ; jmp 0xfffc826b

loc_fffc8246:
mov al, byte [esi + 0xfa092]
or eax, 0x10
mov byte [esi + 0xfa092], al

loc_fffc8255:
mov edx, dword [ebp - 0x3c]
mov al, byte [edx + 0xe0410]
test al, 0x20
jne short loc_fffc8288  ; jne 0xfffc8288
mov al, byte [esi + 0xfa092]
or eax, 0x20

loc_fffc826b:
mov byte [esi + 0xfa092], al
jmp short loc_fffc8288  ; jmp 0xfffc8288

loc_fffc8273:
dec al
jne loc_fffc7d25  ; jne 0xfffc7d25
jmp near loc_fffc7d10  ; jmp 0xfffc7d10

loc_fffc8280:
dec al
jne loc_fffc7d33  ; jne 0xfffc7d33

loc_fffc8288:
lea esp, [ebp - 0xc]
pop ebx
pop esi
pop edi
pop ebp
ret

ref_fffcc32c:
db 82, 69, 69, 69

ref_fffcc330:
dd ref_fffcd58c
dd ref_fffcd964
dd ref_fffcd964
dd ref_fffcd964

ref_fffcc340:
db 40, 34, 34, 34, 77, 77, 77, 0

ref_fffcc348:
dd ref_fffcdca0
dd ref_fffcde80
dd ref_fffcde80
dd ref_fffcde80
dd ref_fffce018
dd ref_fffce018
dd ref_fffce018

ref_fffcc364:
db 8, 12, 12, 12

ref_fffcc368:
dd ref_fffce3b4
dd ref_fffce414
dd ref_fffce414
dd ref_fffce414

ref_fffcc378:
db 4, 6, 6, 6, 4, 4, 4, 0

ref_fffcc380:
dd ref_fffce4a4
dd ref_fffce4d4
dd ref_fffce4d4
dd ref_fffce4d4
dd ref_fffce51c
dd ref_fffce51c
dd ref_fffce51c

ref_fffcc39c:
db 8, 12, 12, 12

ref_fffcc3a0:
dd ref_fffce54c
dd ref_fffce5ac
dd ref_fffce5ac
dd ref_fffce5ac

ref_fffcc3b0:
db 4, 6, 6, 6, 4, 4, 4, 0

ref_fffcc3b8:
dd ref_fffce63c
dd ref_fffce66c
dd ref_fffce66c
dd ref_fffce66c
dd ref_fffce6b4
dd ref_fffce6b4
dd ref_fffce6b4

ref_fffcd58c:
dd 0xea008008
dd 0x00ffffff
dd 0x1c000000
dd 0xea00800c
dd 0xffff8000
dd 0x00002b50
dd 0xea0024a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0026a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0008a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea000aa4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0024ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0026ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0008ac
dd 0xffffffcf
dd 0x00000020
dd 0xea000aac
dd 0xffffffcf
dd 0x00000020
dd 0xea002488
dd 0xffff00ff
dd 0x00008000
dd 0xea002688
dd 0xffff00ff
dd 0x00008000
dd 0xea000888
dd 0xffff00ff
dd 0x00008000
dd 0xea000a88
dd 0xffff00ff
dd 0x00008000
dd 0xea002494
dd 0x7fffffff
dd 0x80000000
dd 0xea002694
dd 0x7fffffff
dd 0x80000000
dd 0xea000894
dd 0x7fffffff
dd 0x80000000
dd 0xea000a94
dd 0x7fffffff
dd 0x80000000
dd 0xea002540
dd 0xff000000
dd 0x00180918
dd 0xea002740
dd 0xff000000
dd 0x00180918
dd 0xea000940
dd 0xff000000
dd 0x00180918
dd 0xea000b40
dd 0xff000000
dd 0x00180918
dd 0xea002544
dd 0xff000000
dd 0x00140918
dd 0xea002744
dd 0xff000000
dd 0x00140918
dd 0xea000944
dd 0xff000000
dd 0x00140918
dd 0xea000b44
dd 0xff000000
dd 0x00140918
dd 0xea002548
dd 0xff000000
dd 0x00140918
dd 0xea002748
dd 0xff000000
dd 0x00140918
dd 0xea000948
dd 0xff000000
dd 0x00140918
dd 0xea000b48
dd 0xff000000
dd 0x00140918
dd 0xea002550
dd 0xc0ffffff
dd 0x02000000
dd 0xea002750
dd 0xc0ffffff
dd 0x02000000
dd 0xea000950
dd 0xc0ffffff
dd 0x02000000
dd 0xea000b50
dd 0xc0ffffff
dd 0x02000000
dd 0xea002554
dd 0xffc0ffff
dd 0x00020000
dd 0xea002754
dd 0xffc0ffff
dd 0x00020000
dd 0xea000954
dd 0xffc0ffff
dd 0x00020000
dd 0xea000b54
dd 0xffc0ffff
dd 0x00020000
dd 0xea002410
dd 0x0000ffff
dd 0x0d510000
dd 0xea002610
dd 0x0000ffff
dd 0x0d510000
dd 0xea000810
dd 0x0000ffff
dd 0x0d510000
dd 0xea000a10
dd 0x0000ffff
dd 0x0d510000
dd 0xea002400
dd 0x30fcffff
dd 0xcf030000
dd 0xea002600
dd 0x30fcffff
dd 0xcf030000
dd 0xea000800
dd 0x30fcffff
dd 0xcf030000
dd 0xea000a00
dd 0x30fcffff
dd 0xcf030000
dd 0xea002408
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002608
dd 0x00039ef7
dd 0xea6c6108
dd 0xea000808
dd 0x00039ef7
dd 0xea6c6108
dd 0xea000a08
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002418
dd 0x0000fcff
dd 0x38250100
dd 0xea002618
dd 0x0000fcff
dd 0x38250100
dd 0xea000818
dd 0x0000fcff
dd 0x38250100
dd 0xea000a18
dd 0x0000fcff
dd 0x38250100
dd 0xea002428
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002628
dd 0x00e0ffff
dd 0x580e0000
dd 0xea000828
dd 0x00e0ffff
dd 0x580e0000
dd 0xea000a28
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002438
dd 0xfffffff0
dd 0x0000000d
dd 0xea002638
dd 0xfffffff0
dd 0x0000000d
dd 0xea000838
dd 0xfffffff0
dd 0x0000000d
dd 0xea000a38
dd 0xfffffff0
dd 0x0000000d
dd 0xea002440
dd 0xe0ffffff
dd 0x01000000
dd 0xea002640
dd 0xe0ffffff
dd 0x01000000
dd 0xea000840
dd 0xe0ffffff
dd 0x01000000
dd 0xea000a40
dd 0xe0ffffff
dd 0x01000000
dd 0xea00242c
dd 0xfffdffff
dd 0x00020000
dd 0xea00262c
dd 0xfffdffff
dd 0x00020000
dd 0xea00082c
dd 0xfffdffff
dd 0x00020000
dd 0xea000a2c
dd 0xfffdffff
dd 0x00020000
dd 0xea00241c
dd 0xffff83ff
dd 0x00002400
dd 0xea00261c
dd 0xffff83ff
dd 0x00002400
dd 0xea00081c
dd 0xffff83ff
dd 0x00002400
dd 0xea000a1c
dd 0xffff83ff
dd 0x00002400
dd 0xea002500
dd 0xffff1fc1
dd 0x00004008
dd 0xea002700
dd 0xffff1fc1
dd 0x00004008
dd 0xea000900
dd 0xffff1fc1
dd 0x00004008
dd 0xea000b00
dd 0xffff1fc1
dd 0x00004008
dd 0xea00257c
dd 0xfff0c0ff
dd 0x00003f00
dd 0xea00277c
dd 0xfff0c0ff
dd 0x00003f00
dd 0xea00097c
dd 0xfff0c0ff
dd 0x00003f00
dd 0xea000b7c
dd 0xfff0c0ff
dd 0x00003f00

ref_fffcd964:
dd 0xea008008
dd 0x00ffffff
dd 0x1c000000
dd 0xea002408
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002608
dd 0x00039ef7
dd 0xea6c6108
dd 0xea000808
dd 0x00039ef7
dd 0xea6c6108
dd 0xea000a08
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002438
dd 0xfffffff0
dd 0x0000000d
dd 0xea002638
dd 0xfffffff0
dd 0x0000000d
dd 0xea000838
dd 0xfffffff0
dd 0x0000000d
dd 0xea000a38
dd 0xfffffff0
dd 0x0000000d
dd 0xea002440
dd 0xe0ffffff
dd 0x01000000
dd 0xea002640
dd 0xe0ffffff
dd 0x01000000
dd 0xea000840
dd 0xe0ffffff
dd 0x01000000
dd 0xea000a40
dd 0xe0ffffff
dd 0x01000000
dd 0xea002410
dd 0x0000ffff
dd 0x0d510000
dd 0xea002610
dd 0x0000ffff
dd 0x0d510000
dd 0xea000810
dd 0x0000ffff
dd 0x0d510000
dd 0xea000a10
dd 0x0000ffff
dd 0x0d510000
dd 0xea00242c
dd 0xfffdf7ff
dd 0x00020000
dd 0xea00262c
dd 0xfffdf7ff
dd 0x00020000
dd 0xea00082c
dd 0xfffdf7ff
dd 0x00020000
dd 0xea000a2c
dd 0xfffdf7ff
dd 0x00020000
dd 0xea002418
dd 0x0000fcff
dd 0x38250100
dd 0xea002618
dd 0x0000fcff
dd 0x38250100
dd 0xea000818
dd 0x0000fcff
dd 0x38250100
dd 0xea000a18
dd 0x0000fcff
dd 0x38250100
dd 0xea002400
dd 0x30fcffff
dd 0xcf030000
dd 0xea002600
dd 0x30fcffff
dd 0xcf030000
dd 0xea000800
dd 0x30fcffff
dd 0xcf030000
dd 0xea000a00
dd 0x30fcffff
dd 0xcf030000
dd 0xea002428
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002628
dd 0x00e0ffff
dd 0x580e0000
dd 0xea000828
dd 0x00e0ffff
dd 0x580e0000
dd 0xea000a28
dd 0x00e0ffff
dd 0x580e0000
dd 0xea00241c
dd 0xffff83ff
dd 0x00002400
dd 0xea00261c
dd 0xffff83ff
dd 0x00002400
dd 0xea00081c
dd 0xffff83ff
dd 0x00002400
dd 0xea000a1c
dd 0xffff83ff
dd 0x00002400
dd 0xea00248c
dd 0xff00ffff
dd 0x00800000
dd 0xea00268c
dd 0xff00ffff
dd 0x00800000
dd 0xea00088c
dd 0xff00ffff
dd 0x00800000
dd 0xea000a8c
dd 0xff00ffff
dd 0x00800000
dd 0xea0024a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0026a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0008a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea000aa4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0024ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0026ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0008ac
dd 0xffffffcf
dd 0x00000020
dd 0xea000aac
dd 0xffffffcf
dd 0x00000020
dd 0xea002540
dd 0xff000000
dd 0x00140718
dd 0xea002740
dd 0xff000000
dd 0x00140718
dd 0xea000940
dd 0xff000000
dd 0x00140718
dd 0xea000b40
dd 0xff000000
dd 0x00140718
dd 0xea002544
dd 0xff000000
dd 0x0014091b
dd 0xea002744
dd 0xff000000
dd 0x0014091b
dd 0xea000944
dd 0xff000000
dd 0x0014091b
dd 0xea000b44
dd 0xff000000
dd 0x0014091b
dd 0xea002548
dd 0xff000000
dd 0x00140918
dd 0xea002748
dd 0xff000000
dd 0x00140918
dd 0xea000948
dd 0xff000000
dd 0x00140918
dd 0xea000b48
dd 0xff000000
dd 0x00140918
dd 0xea00257c
dd 0xfcffffff
dd 0x03000000
dd 0xea00277c
dd 0xfcffffff
dd 0x03000000
dd 0xea00097c
dd 0xfcffffff
dd 0x03000000
dd 0xea000b7c
dd 0xfcffffff
dd 0x03000000
dd 0xea002578
dd 0xffffe0ff
dd 0x00001800
dd 0xea002778
dd 0xffffe0ff
dd 0x00001800
dd 0xea000978
dd 0xffffe0ff
dd 0x00001800
dd 0xea000b78
dd 0xffffe0ff
dd 0x00001800

ref_fffcdca0:
dd 0xea0020a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0022a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0020ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0022ac
dd 0xffffffcf
dd 0x00000020
dd 0xea002088
dd 0xffff00ff
dd 0x00008000
dd 0xea002288
dd 0xffff00ff
dd 0x00008000
dd 0xea002094
dd 0x7fffffff
dd 0x80000000
dd 0xea002294
dd 0x7fffffff
dd 0x80000000
dd 0xea002140
dd 0xff000000
dd 0x00180918
dd 0xea002340
dd 0xff000000
dd 0x00180918
dd 0xea002144
dd 0xff000000
dd 0x00140918
dd 0xea002344
dd 0xff000000
dd 0x00140918
dd 0xea002148
dd 0xff000000
dd 0x00140918
dd 0xea002348
dd 0xff000000
dd 0x00140918
dd 0xea002150
dd 0xc0ffffff
dd 0x02000000
dd 0xea002350
dd 0xc0ffffff
dd 0x02000000
dd 0xea002154
dd 0xffc0ffff
dd 0x00020000
dd 0xea002354
dd 0xffc0ffff
dd 0x00020000
dd 0xea002010
dd 0x0000ffff
dd 0x0d510000
dd 0xea002210
dd 0x0000ffff
dd 0x0d510000
dd 0xea002000
dd 0x30fcffff
dd 0xcf030000
dd 0xea002200
dd 0x30fcffff
dd 0xcf030000
dd 0xea002008
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002208
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002018
dd 0x0000fcff
dd 0x38250100
dd 0xea002218
dd 0x0000fcff
dd 0x38250100
dd 0xea002028
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002228
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002038
dd 0xfffffff0
dd 0x0000000d
dd 0xea002238
dd 0xfffffff0
dd 0x0000000d
dd 0xea002040
dd 0xe0ffffff
dd 0x01000000
dd 0xea002240
dd 0xe0ffffff
dd 0x01000000
dd 0xea00202c
dd 0xfffdf8ff
dd 0x00020100
dd 0xea00222c
dd 0xfffdf8ff
dd 0x00020100
dd 0xea00201c
dd 0xffff83ff
dd 0x00002400
dd 0xea00221c
dd 0xffff83ff
dd 0x00002400
dd 0xea002100
dd 0xffff1fc1
dd 0x00004008
dd 0xea002300
dd 0xffff1fc1
dd 0x00004008
dd 0xea00217c
dd 0xfff0c0ff
dd 0x00003f00
dd 0xea00237c
dd 0xfff0c0ff
dd 0x00003f00

ref_fffcde80:
dd 0xea002008
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002208
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002038
dd 0xfffffff0
dd 0x0000000d
dd 0xea002238
dd 0xfffffff0
dd 0x0000000d
dd 0xea00202c
dd 0xfffdf0ff
dd 0x00020100
dd 0xea00222c
dd 0xfffdf0ff
dd 0x00020100
dd 0xea002040
dd 0xe0ffffff
dd 0x01000000
dd 0xea002240
dd 0xe0ffffff
dd 0x01000000
dd 0xea002010
dd 0x0000ffff
dd 0x0d510000
dd 0xea002210
dd 0x0000ffff
dd 0x0d510000
dd 0xea002018
dd 0x0000fcff
dd 0x38250100
dd 0xea002218
dd 0x0000fcff
dd 0x38250100
dd 0xea002000
dd 0x30fcffff
dd 0xcf030000
dd 0xea002200
dd 0x30fcffff
dd 0xcf030000
dd 0xea002028
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002228
dd 0x00e0ffff
dd 0x580e0000
dd 0xea00201c
dd 0xffff83ff
dd 0x00002400
dd 0xea00221c
dd 0xffff83ff
dd 0x00002400
dd 0xea00208c
dd 0xff00ffff
dd 0x00800000
dd 0xea00228c
dd 0xff00ffff
dd 0x00800000
dd 0xea0020a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0022a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0020ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0022ac
dd 0xffffffcf
dd 0x00000020
dd 0xea002140
dd 0xff000000
dd 0x00140718
dd 0xea002340
dd 0xff000000
dd 0x00140718
dd 0xea002144
dd 0xff000000
dd 0x0014091b
dd 0xea002344
dd 0xff000000
dd 0x0014091b
dd 0xea002148
dd 0xff000000
dd 0x00140918
dd 0xea002348
dd 0xff000000
dd 0x00140918
dd 0xea00217c
dd 0xfcffffff
dd 0x03000000
dd 0xea00237c
dd 0xfcffffff
dd 0x03000000
dd 0xea002178
dd 0xffffe0ff
dd 0x00001800
dd 0xea002378
dd 0xffffe0ff
dd 0x00001800

ref_fffce018:
dd 0xea008008
dd 0x00ffffff
dd 0x1c000000
dd 0xea002008
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002208
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002408
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002608
dd 0x00039ef7
dd 0xea6c6108
dd 0xea002038
dd 0xfffffff0
dd 0x0000000d
dd 0xea002238
dd 0xfffffff0
dd 0x0000000d
dd 0xea002438
dd 0xfffffff0
dd 0x0000000d
dd 0xea002638
dd 0xfffffff0
dd 0x0000000d
dd 0xea00202c
dd 0xfffdf0ff
dd 0x00020100
dd 0xea00222c
dd 0xfffdf0ff
dd 0x00020100
dd 0xea00242c
dd 0xfffdf0ff
dd 0x00020100
dd 0xea00262c
dd 0xfffdf0ff
dd 0x00020100
dd 0xea002040
dd 0xe0ffffff
dd 0x01000000
dd 0xea002240
dd 0xe0ffffff
dd 0x01000000
dd 0xea002440
dd 0xe0ffffff
dd 0x01000000
dd 0xea002640
dd 0xe0ffffff
dd 0x01000000
dd 0xea002010
dd 0x0000ffff
dd 0x55510000
dd 0xea002210
dd 0x0000ffff
dd 0x55510000
dd 0xea002410
dd 0x0000ffff
dd 0x55510000
dd 0xea002610
dd 0x0000ffff
dd 0x55510000
dd 0xea002150
dd 0xc0ffffff
dd 0x02000000
dd 0xea002350
dd 0xc0ffffff
dd 0x02000000
dd 0xea002550
dd 0xc0ffffff
dd 0x02000000
dd 0xea002750
dd 0xc0ffffff
dd 0x02000000
dd 0xea002154
dd 0xffc0ffff
dd 0x00020000
dd 0xea002354
dd 0xffc0ffff
dd 0x00020000
dd 0xea002554
dd 0xffc0ffff
dd 0x00020000
dd 0xea002754
dd 0xffc0ffff
dd 0x00020000
dd 0xea002140
dd 0xff000000
dd 0x00140718
dd 0xea002340
dd 0xff000000
dd 0x00140718
dd 0xea002540
dd 0xff000000
dd 0x00140718
dd 0xea002740
dd 0xff000000
dd 0x00140718
dd 0xea002144
dd 0xff000000
dd 0x0014091b
dd 0xea002344
dd 0xff000000
dd 0x0014091b
dd 0xea002544
dd 0xff000000
dd 0x0014091b
dd 0xea002744
dd 0xff000000
dd 0x0014091b
dd 0xea002148
dd 0xff000000
dd 0x00140918
dd 0xea002348
dd 0xff000000
dd 0x00140918
dd 0xea002548
dd 0xff000000
dd 0x00140918
dd 0xea002748
dd 0xff000000
dd 0x00140918
dd 0xea00217c
dd 0xfcffffff
dd 0x03000000
dd 0xea00237c
dd 0xfcffffff
dd 0x03000000
dd 0xea00257c
dd 0xfcffffff
dd 0x03000000
dd 0xea00277c
dd 0xfcffffff
dd 0x03000000
dd 0xea00208c
dd 0xff00ffff
dd 0x00800000
dd 0xea00228c
dd 0xff00ffff
dd 0x00800000
dd 0xea00248c
dd 0xff00ffff
dd 0x00800000
dd 0xea00268c
dd 0xff00ffff
dd 0x00800000
dd 0xea0020a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0022a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0024a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0026a4
dd 0xffcf00ff
dd 0x00308300
dd 0xea0020ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0022ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0024ac
dd 0xffffffcf
dd 0x00000020
dd 0xea0026ac
dd 0xffffffcf
dd 0x00000020
dd 0xea002018
dd 0x0000fcff
dd 0x38250100
dd 0xea002218
dd 0x0000fcff
dd 0x38250100
dd 0xea002418
dd 0x0000fcff
dd 0x38250100
dd 0xea002618
dd 0x0000fcff
dd 0x38250100
dd 0xea002000
dd 0x30fcffff
dd 0xcf030000
dd 0xea002200
dd 0x30fcffff
dd 0xcf030000
dd 0xea002400
dd 0x30fcffff
dd 0xcf030000
dd 0xea002600
dd 0x30fcffff
dd 0xcf030000
dd 0xea002028
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002228
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002428
dd 0x00e0ffff
dd 0x580e0000
dd 0xea002628
dd 0x00e0ffff
dd 0x580e0000
dd 0xea00201c
dd 0xffff83ff
dd 0x00002400
dd 0xea00221c
dd 0xffff83ff
dd 0x00002400
dd 0xea00241c
dd 0xffff83ff
dd 0x00002400
dd 0xea00261c
dd 0xffff83ff
dd 0x00002400
dd 0xea002178
dd 0xffffe0ff
dd 0x00001800
dd 0xea002378
dd 0xffffe0ff
dd 0x00001800
dd 0xea002578
dd 0xffffe0ff
dd 0x00001800
dd 0xea002778
dd 0xffffe0ff
dd 0x00001800

ref_fffce3b4:
dd 0xea002490
dd 0xffff0000
dd 0x00004c5a
dd 0xea002690
dd 0xffff0000
dd 0x00004c5a
dd 0xea000890
dd 0xffff0000
dd 0x00004c5a
dd 0xea000a90
dd 0xffff0000
dd 0x00004c5a
dd 0xea00248c
dd 0xff00ffff
dd 0x00800000
dd 0xea00268c
dd 0xff00ffff
dd 0x00800000
dd 0xea00088c
dd 0xff00ffff
dd 0x00800000
dd 0xea000a8c
dd 0xff00ffff
dd 0x00800000

ref_fffce414:
dd 0xea002550
dd 0xc0ffffff
dd 0x02000000
dd 0xea002750
dd 0xc0ffffff
dd 0x02000000
dd 0xea000950
dd 0xc0ffffff
dd 0x02000000
dd 0xea000b50
dd 0xc0ffffff
dd 0x02000000
dd 0xea002554
dd 0xffc0ffff
dd 0x00020000
dd 0xea002754
dd 0xffc0ffff
dd 0x00020000
dd 0xea000954
dd 0xffc0ffff
dd 0x00020000
dd 0xea000b54
dd 0xffc0ffff
dd 0x00020000
dd 0xea002490
dd 0xffff0000
dd 0x00004c5a
dd 0xea002690
dd 0xffff0000
dd 0x00004c5a
dd 0xea000890
dd 0xffff0000
dd 0x00004c5a
dd 0xea000a90
dd 0xffff0000
dd 0x00004c5a

ref_fffce4a4:
dd 0xea002090
dd 0xffff0000
dd 0x00004c5a
dd 0xea002290
dd 0xffff0000
dd 0x00004c5a
dd 0xea00208c
dd 0xff00ffff
dd 0x00800000
dd 0xea00228c
dd 0xff00ffff
dd 0x00800000

ref_fffce4d4:
dd 0xea002150
dd 0xc0ffffff
dd 0x02000000
dd 0xea002350
dd 0xc0ffffff
dd 0x02000000
dd 0xea002154
dd 0xffc0ffff
dd 0x00020000
dd 0xea002354
dd 0xffc0ffff
dd 0x00020000
dd 0xea002090
dd 0xffff0000
dd 0x00004c5a
dd 0xea002290
dd 0xffff0000
dd 0x00004c5a

ref_fffce51c:
dd 0xea002090
dd 0xffff0000
dd 0x00004c5a
dd 0xea002290
dd 0xffff0000
dd 0x00004c5a
dd 0xea002490
dd 0xffff0000
dd 0x00004c5a
dd 0xea002690
dd 0xffff0000
dd 0x00004c5a

ref_fffce54c:
dd 0xea002490
dd 0xffff0000
dd 0x00003e67
dd 0xea002690
dd 0xffff0000
dd 0x00003e67
dd 0xea000890
dd 0xffff0000
dd 0x00003e67
dd 0xea000a90
dd 0xffff0000
dd 0x00003e67
dd 0xea00248c
dd 0xff00ffff
dd 0x00800000
dd 0xea00268c
dd 0xff00ffff
dd 0x00800000
dd 0xea00088c
dd 0xff00ffff
dd 0x00800000
dd 0xea000a8c
dd 0xff00ffff
dd 0x00800000

ref_fffce5ac:
dd 0xea002550
dd 0xc0ffffff
dd 0x02000000
dd 0xea002750
dd 0xc0ffffff
dd 0x02000000
dd 0xea000950
dd 0xc0ffffff
dd 0x02000000
dd 0xea000b50
dd 0xc0ffffff
dd 0x02000000
dd 0xea002554
dd 0xffc0ffff
dd 0x00020000
dd 0xea002754
dd 0xffc0ffff
dd 0x00020000
dd 0xea000954
dd 0xffc0ffff
dd 0x00020000
dd 0xea000b54
dd 0xffc0ffff
dd 0x00020000
dd 0xea002490
dd 0xffff0000
dd 0x00003e67
dd 0xea002690
dd 0xffff0000
dd 0x00003e67
dd 0xea000890
dd 0xffff0000
dd 0x00003e67
dd 0xea000a90
dd 0xffff0000
dd 0x00003e67

ref_fffce63c:
dd 0xea002090
dd 0xffff0000
dd 0x00003e67
dd 0xea002290
dd 0xffff0000
dd 0x00003e67
dd 0xea00208c
dd 0xff00ffff
dd 0x00800000
dd 0xea00228c
dd 0xff00ffff
dd 0x00800000

ref_fffce66c:
dd 0xea002150
dd 0xc0ffffff
dd 0x02000000
dd 0xea002350
dd 0xc0ffffff
dd 0x02000000
dd 0xea002154
dd 0xffc0ffff
dd 0x00020000
dd 0xea002354
dd 0xffc0ffff
dd 0x00020000
dd 0xea002090
dd 0xffff0000
dd 0x00003e67
dd 0xea002290
dd 0xffff0000
dd 0x00003e67

ref_fffce6b4:
dd 0xea002090
dd 0xffff0000
dd 0x00003e67
dd 0xea002290
dd 0xffff0000
dd 0x00003e67
dd 0xea002490
dd 0xffff0000
dd 0x00003e67
dd 0xea002690
dd 0xffff0000
dd 0x00003e67
