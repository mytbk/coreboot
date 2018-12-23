global PchMeUmaDesc
global gPchMeUmaPpiGuid

extern gEfiPeiStallPpiGuid
extern mrc_sku_type
extern gWdtPpiGuid

fcn_fffbdf70:  ; not directly referenced
push ebp
mov ebp, esp
push esi
push ebx
mov ebx, eax
lea esp, [esp - 0x20]
mov byte [ebp - 0x1c], dl
mov dword [ebp - 0xc], 0
call mrc_sku_type
sub esp, 0xc
lea edx, [ebp - 0xc]
mov esi, eax
mov eax, dword [ebx]
push edx
push 0
push 0
push gWdtPpiGuid
push ebx
call dword [eax + 0x20]  ; ucall
mov eax, dword [0xf00f80ac]
and eax, 0xffebffff
mov dword [0xf00f80ac], eax
mov edx, 0xcf9
in al, dx
mov bl, al
mov cl, byte [ebp - 0x1c]
and ebx, 0xfffffff1
add esp, 0x20
cmp cl, 6
jne short loc_fffbdfd2  ; jne 0xfffbdfd2
mov ecx, dword [0xf00f8048]
and ecx, 0xfffffffe
jmp short loc_fffbdffc  ; jmp 0xfffbdffc

loc_fffbdfd2:  ; not directly referenced
cmp cl, 2
je short loc_fffbdfe8  ; je 0xfffbdfe8
cmp cl, 6
je short loc_fffbdffa  ; je 0xfffbdffa
mov al, bl
or eax, 6
dec cl
cmove ebx, eax
jmp short loc_fffbe059  ; jmp 0xfffbe059

loc_fffbdfe8:  ; not directly referenced
sub esp, 0xc
mov eax, dword [ebp - 0xc]
push 2
or ebx, 0xe
call dword [eax]  ; ucall
add esp, 0x10
jmp short loc_fffbe059  ; jmp 0xfffbe059

loc_fffbdffa:  ; not directly referenced
xor ecx, ecx

loc_fffbdffc:  ; not directly referenced
cmp esi, 1
jne short loc_fffbe021  ; jne 0xfffbe021
mov edx, ecx
in eax, dx
or eax, 0x40000000
out dx, eax
mov esi, ecx
lea edx, [esi + 4]
in eax, dx
and eax, 0xbfffffff
out dx, eax
lea edx, [esi + 0xc]
in eax, dx
and eax, 0xbfffffff
jmp short loc_fffbe03c  ; jmp 0xfffbe03c

loc_fffbe021:  ; not directly referenced
cmp esi, 2
jne short loc_fffbe03d  ; jne 0xfffbe03d
lea edx, [ecx + 0x1f0]
in eax, dx
or eax, 1
out dx, eax
in eax, dx
and eax, 0xfffffffb
out dx, eax
in eax, dx
and eax, 0x7fffffff

loc_fffbe03c:  ; not directly referenced
out dx, eax

loc_fffbe03d:  ; not directly referenced
lea edx, [ecx + 0x60]
in eax, dx
or eax, 0x40000000
out dx, eax
mov eax, dword [0xf00f80ac]
or eax, 0x100000
mov dword [0xf00f80ac], eax
or ebx, 0xe

loc_fffbe059:  ; not directly referenced
mov eax, dword [ebp - 0xc]
call dword [eax + 0xc]  ; ucall
mov edx, 0xcf9
mov al, bl
out dx, al
lea esp, [ebp - 8]
xor eax, eax
pop ebx
pop esi
pop ebp
ret

fcn_fffbe110:  ; not directly referenced
push ebp
mov ebp, esp
lea esp, [esp - 8]
mov ecx, dword [0xf00b0048]
mov dl, byte [ebp + 0x10]
mov eax, dword [ebp + 8]
cmp dl, 2
je short loc_fffbe138  ; je 0xfffbe138
cmp dl, 6
je short loc_fffbe13f  ; je 0xfffbe13f
dec dl
jne short loc_fffbe149  ; jne 0xfffbe149
mov edx, 1
jmp short loc_fffbe144  ; jmp 0xfffbe144

loc_fffbe138:  ; not directly referenced
mov edx, 2
jmp short loc_fffbe144  ; jmp 0xfffbe144

loc_fffbe13f:  ; not directly referenced
mov edx, 6

loc_fffbe144:  ; not directly referenced
call fcn_fffbdf70  ; call 0xfffbdf70

loc_fffbe149:  ; not directly referenced
xor eax, eax
leave
ret

fcn_fffbe14d:  ; not directly referenced
push ebp
mov ebp, esp
push esi
push ebx
lea edx, [ebp - 0xc]
lea esp, [esp - 0x2c]
mov ebx, dword [ebp + 8]
mov cl, byte [ebp + 0x14]
mov eax, dword [ebx]
mov byte [ebp - 0x1c], cl
push edx
push 0
push 0
push gEfiPeiStallPpiGuid
push ebx
call dword [eax + 0x20]  ; ucall
mov eax, dword [0xf00b0040]
add esp, 0x20
mov edx, eax
mov cl, byte [ebp - 0x1c]
shr edx, 0x10
and edx, 0xf
cmp dl, 2
je loc_fffbe22f  ; je 0xfffbe22f
movzx edx, ah
xor eax, eax
and dl, 0xf0
jne loc_fffbe231  ; jne 0xfffbe231
mov edx, dword [0xf0000070]
mov eax, dword [0xf0000074]
shl eax, 0x1c
shr edx, 4
add edx, eax
shr edx, 0x10
mov eax, edx
or edx, 0x10800000
or eax, 0x10000000
test cl, cl
cmovs eax, edx
mov edx, ecx
and edx, 0x7f
shl edx, 0x18
or eax, edx
mov edx, dword [0xf00b004c]
mov dword [0xf00b004c], eax
push esi
mov eax, dword [ebp - 0xc]
mov esi, 0x1389
push 0x44c
push eax
push ebx
call dword [eax + 4]  ; ucall
mov eax, dword [0xf00b0040]
add esp, 0x10
jmp short loc_fffbe20c  ; jmp 0xfffbe20c

loc_fffbe1f6:  ; not directly referenced
push ecx
mov eax, dword [ebp - 0xc]
push 0x3e8
push eax
push ebx
call dword [eax + 4]  ; ucall
mov eax, dword [0xf00b0040]
add esp, 0x10

loc_fffbe20c:  ; not directly referenced
mov edx, eax
shr edx, 0x18
and dl, 0xf0
jne short loc_fffbe219  ; jne 0xfffbe219
dec esi
jne short loc_fffbe1f6  ; jne 0xfffbe1f6

loc_fffbe219:  ; not directly referenced
shr eax, 0x19
push edx
and eax, 7
push eax
push dword [ebp + 0x10]
push ebx
call fcn_fffbe110  ; call 0xfffbe110
add esp, 0x10
jmp short loc_fffbe231  ; jmp 0xfffbe231

loc_fffbe22f:  ; not directly referenced
xor eax, eax

loc_fffbe231:  ; not directly referenced
lea esp, [ebp - 8]
pop ebx
pop esi
pop ebp
ret

fcn_fffc8c78:  ; not directly referenced
push ebp
mov ebp, esp
push edi
push esi
push ebx
lea esp, [esp - 0x1c]
mov edi, dword [0xf00b0044]
mov eax, dword [0xf00b0040]
mov esi, dword [ebp + 8]
mov edx, eax
shr edx, 0x10
and edx, 0xf
cmp dl, 2
jne short loc_fffc8ca1  ; jne 0xfffc8ca1

loc_fffc8c9d:  ; not directly referenced
xor eax, eax
jmp short loc_fffc8cfc  ; jmp 0xfffc8cfc

loc_fffc8ca1:  ; not directly referenced
movzx eax, ah
test al, 0xf0
jne short loc_fffc8c9d  ; jne 0xfffc8c9d
sub esp, 0xc
lea edx, [ebp - 0x1c]
mov eax, dword [esi]
xor ebx, ebx
push edx
push 0
push 0
push gEfiPeiStallPpiGuid
push esi
call dword [eax + 0x20]  ; ucall
add esp, 0x20
jmp short loc_fffc8cdd  ; jmp 0xfffc8cdd

loc_fffc8cc5:  ; not directly referenced
push edx
mov eax, dword [ebp - 0x1c]
inc ebx
push 0x3e8
push eax
push esi
call dword [eax + 4]  ; ucall
mov edi, dword [0xf00b0044]
add esp, 0x10

loc_fffc8cdd:  ; not directly referenced
test edi, 0x10000
jne short loc_fffc8cef  ; jne 0xfffc8cef
cmp ebx, 0x1388
jne short loc_fffc8cc5  ; jne 0xfffc8cc5
jmp short loc_fffc8c9d  ; jmp 0xfffc8c9d

loc_fffc8cef:  ; not directly referenced
cmp ebx, 0x1388
je short loc_fffc8c9d  ; je 0xfffc8c9d
mov eax, edi
and eax, 0x3f

loc_fffc8cfc:  ; not directly referenced
lea esp, [ebp - 0xc]
pop ebx
pop esi
pop edi
pop ebp
ret


PchMeUmaDesc:
dd 0x80000010
dd gPchMeUmaPpiGuid
dd ref_fffcd514

gPchMeUmaPpiGuid:
dd 0x8c376010
dd 0x4d7d2400
dd 0x859d7bb4
dd 0xd1c9f31d

ref_fffcd514:
dd fcn_fffc8c78
dd fcn_fffbe070
dd fcn_fffbe14d
dd fcn_fffbe110
