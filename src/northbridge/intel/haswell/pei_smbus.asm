global smbus_exec
extern mrc_smbus_inb
extern mrc_smbus_outb
extern usleep

smbus_exec:
push ebp
mov ebp, esp
push edi
push esi
push ebx
lea esp, [esp - 0x2c]
mov esi, dword [ebp + 0x10]
mov cl, byte [ebp + 0x1c]
and esi, 0x7f
cmp dword [ebp + 0x18], 1
mov edi, dword [ebp + 0x20]
mov byte [ebp - 0x25], cl
jbe short loc_fffc5f40  ; jbe 0xfffc5f40
cmp dword [ebp + 0x24], 0
mov ebx, 0x80000002
sete dl
test edi, edi
sete al
or dl, al
jne loc_fffc642a  ; jne 0xfffc642a

loc_fffc5f40:  ; not directly referenced
xor eax, eax
mov ebx, 0x80000012
call mrc_smbus_inb
test al, 0x40
jne loc_fffc642a  ; jne 0xfffc642a
test al, 1
je short loc_fffc5f64  ; je 0xfffc5f64
mov edx, 0xff
xor eax, eax
jmp near loc_fffc6416  ; jmp 0xfffc6416

loc_fffc5f64:  ; not directly referenced
movzx edx, al
xor eax, eax
call mrc_smbus_outb
lea ecx, [esi + esi + 1]
mov byte [ebp - 0x1d], cl
dec ecx
mov dword [ebp - 0x24], 3
mov byte [ebp - 0x1e], cl
mov ecx, dword [ebp + 0x18]
and ecx, 0xfffffffd
mov byte [ebp - 0x20], 0
mov dword [ebp - 0x30], ecx

loc_fffc5f8d:  ; not directly referenced
mov al, byte [ebp + 0x14]
cmp dword [ebp + 0x18], 0xb
mov byte [ebp - 0x1f], al
ja loc_fffc6138  ; ja 0xfffc6138
mov ecx, dword [ebp + 0x18]
jmp dword [ecx*4 + ref_fffcc1e8]  ; ujmp: jmp dword [ecx*4 - 0x33e18]

loc_fffc5fa7:  ; case 1
movzx esi, byte [ebp - 0x1e]
jmp short loc_fffc5fb1  ; jmp 0xfffc5fb1

loc_fffc5fad:  ; case 0
movzx esi, byte [ebp - 0x1d]

loc_fffc5fb1:  ; not directly referenced
cmp byte [ebp - 0x25], 1
je loc_fffc6126  ; je 0xfffc6126
mov byte [ebp - 0x1c], 0
jmp near loc_fffc6120  ; jmp 0xfffc6120

loc_fffc5fc4:  ; case 3
movzx esi, byte [ebp - 0x1e]
mov ecx, dword [ebp + 0x24]
mov cl, byte [ecx]
mov byte [ebp - 0x1f], cl
jmp short loc_fffc5fd6  ; jmp 0xfffc5fd6

loc_fffc5fd2:  ; case 2
movzx esi, byte [ebp - 0x1d]

loc_fffc5fd6:  ; not directly referenced
cmp dword [edi], 1
mov byte [ebp - 0x1c], 4
sbb ebx, ebx
mov dword [edi], 1
and ebx, 0x80000005
jmp near loc_fffc60f4  ; jmp 0xfffc60f4

loc_fffc5ff0:  ; case 5
mov ecx, dword [ebp + 0x24]
mov eax, 5
movzx edx, byte [ecx]
call mrc_smbus_outb
movzx esi, byte [ebp - 0x1e]
mov dword [edi], 1
jmp short loc_fffc6010  ; jmp 0xfffc6010

loc_fffc600c:  ; case 4
movzx esi, byte [ebp - 0x1d]

loc_fffc6010:  ; not directly referenced
mov eax, dword [edi]
test eax, eax
je loc_fffc63e8  ; je 0xfffc63e8
cmp eax, 1
je loc_fffc611c  ; je 0xfffc611c
cmp eax, 0x100
ja loc_fffc6138  ; ja 0xfffc6138
cmp byte [ebp - 0x25], 1
je loc_fffc6126  ; je 0xfffc6126
mov byte [ebp - 0x1c], 0x18
jmp near loc_fffc6120  ; jmp 0xfffc6120

loc_fffc6041:  ; case 6
movzx esi, byte [ebp - 0x1d]
cmp dword [edi], 2
sbb ebx, ebx
mov dword [edi], 2
and ebx, 0x80000005
jmp short loc_fffc608e  ; jmp 0xfffc608e

loc_fffc6058:  ; case 7
mov ecx, dword [ebp + 0x24]
mov eax, 6
movzx edx, byte [ecx + 1]
call mrc_smbus_outb
mov ecx, dword [ebp + 0x24]
mov eax, 5
movzx edx, byte [ecx]
call mrc_smbus_outb
movzx esi, byte [ebp - 0x1e]
cmp dword [edi], 2
sbb ebx, ebx
mov dword [edi], 2
and ebx, 0x80000005

loc_fffc608e:  ; not directly referenced
mov byte [ebp - 0x1c], 0xc
jmp short loc_fffc60f4  ; jmp 0xfffc60f4

loc_fffc6094:  ; case 9
movzx edx, byte [edi]
mov eax, 5
call mrc_smbus_outb
movzx esi, byte [ebp - 0x1e]
mov cl, byte [edi]
mov byte [ebp - 0x20], cl
jmp short loc_fffc60b0  ; jmp 0xfffc60b0

loc_fffc60ac:  ; case 8
movzx esi, byte [ebp - 0x1d]

loc_fffc60b0:  ; not directly referenced
mov eax, dword [edi]
dec eax
cmp eax, 0x1f
jbe short loc_fffc6130  ; jbe 0xfffc6130
jmp short loc_fffc6138  ; jmp 0xfffc6138

loc_fffc60ba:  ; case 10
mov ecx, dword [ebp + 0x24]
mov eax, 6
movzx edx, byte [ecx + 1]
call mrc_smbus_outb
mov ecx, dword [ebp + 0x24]
mov eax, 5
movzx edx, byte [ecx]
call mrc_smbus_outb
cmp dword [edi], 2
mov byte [ebp - 0x1c], 0x10
sbb ebx, ebx
mov dword [edi], 2
movzx esi, byte [ebp - 0x1d]
and ebx, 0x80000005

loc_fffc60f4:  ; not directly referenced
xor edx, edx
jmp short loc_fffc6142  ; jmp 0xfffc6142

loc_fffc60f8:  ; case 11
mov eax, dword [edi]
dec eax
cmp eax, 0x1f
ja short loc_fffc6138  ; ja 0xfffc6138
movzx edx, byte [edi]
mov eax, 5
call mrc_smbus_outb
mov cl, byte [edi]
mov byte [ebp - 0x1c], 0x1c
movzx esi, byte [ebp - 0x1d]
mov byte [ebp - 0x20], cl
jmp short loc_fffc6134  ; jmp 0xfffc6134

loc_fffc611c:  ; not directly referenced
mov byte [ebp - 0x1c], 8

loc_fffc6120:  ; not directly referenced
xor edx, edx

loc_fffc6122:  ; not directly referenced
xor ebx, ebx
jmp short loc_fffc614a  ; jmp 0xfffc614a

loc_fffc6126:  ; not directly referenced
mov ebx, 0x80000003
jmp near loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc6130:  ; not directly referenced
mov byte [ebp - 0x1c], 0x14

loc_fffc6134:  ; not directly referenced
mov dl, 2
jmp short loc_fffc6122  ; jmp 0xfffc6122

loc_fffc6138:  ; default
mov ebx, 0x80000002
jmp near loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc6142:  ; not directly referenced
test ebx, ebx
js loc_fffc63f4  ; js 0xfffc63f4

loc_fffc614a:  ; not directly referenced
mov al, dl
or eax, 1
cmp byte [ebp - 0x25], 1
cmove edx, eax
mov eax, 0xd
movzx edx, dl
call mrc_smbus_outb
mov eax, 2
call mrc_smbus_inb
cmp dword [ebp - 0x30], 9
je short loc_fffc61a4  ; je 0xfffc61a4

loc_fffc6173:  ; not directly referenced
mov eax, esi
movzx edx, al
mov eax, 4
call mrc_smbus_outb
cmp dword [ebp + 0x18], 4
jne short loc_fffc61c4  ; jne 0xfffc61c4
jmp short loc_fffc61b4  ; jmp 0xfffc61b4

loc_fffc618a:  ; not directly referenced
mov eax, dword [ebp + 0x24]
movzx edx, byte [eax + ecx]
mov eax, 7
mov dword [ebp - 0x34], ecx
call mrc_smbus_outb
mov ecx, dword [ebp - 0x34]
inc ecx
jmp short loc_fffc61ad  ; jmp 0xfffc61ad

loc_fffc61a4:  ; not directly referenced
movzx edx, byte [ebp - 0x20]
xor ecx, ecx
mov dword [ebp - 0x2c], edx

loc_fffc61ad:  ; not directly referenced
cmp ecx, dword [ebp - 0x2c]
jb short loc_fffc618a  ; jb 0xfffc618a
jmp short loc_fffc6173  ; jmp 0xfffc6173

loc_fffc61b4:  ; not directly referenced
cmp dword [edi], 1
jbe short loc_fffc61c4  ; jbe 0xfffc61c4
movzx edx, byte [ebp - 0x1f]
mov eax, 6
jmp short loc_fffc61cd  ; jmp 0xfffc61cd

loc_fffc61c4:  ; not directly referenced
movzx edx, byte [ebp - 0x1f]
mov eax, 3

loc_fffc61cd:  ; not directly referenced
call mrc_smbus_outb
mov dl, byte [ebp - 0x1c]
mov eax, 2
add edx, 0x40
mov esi, 0x186a0
movzx edx, dl
call mrc_smbus_outb

loc_fffc61ea:  ; not directly referenced
xor eax, eax
call mrc_smbus_inb
test al, 0x8e
jne loc_fffc641d  ; jne 0xfffc641d
mov eax, 0xa
call usleep
dec esi
jne short loc_fffc61ea  ; jne 0xfffc61ea
jmp near loc_fffc6328  ; jmp 0xfffc6328

loc_fffc620b:  ; not directly referenced
mov eax, 0xc
call mrc_smbus_inb
and eax, 1
cmp al, 1
sbb ebx, ebx
and ebx, 0xffffffec
sub ebx, 0x7fffffe5
jmp near loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc622a:  ; not directly referenced
test al, 8
je short loc_fffc626d  ; je 0xfffc626d
xor eax, eax
mov edx, 8
call mrc_smbus_outb
xor eax, eax
mov edx, 0xff
call mrc_smbus_outb
mov edx, 1
mov eax, 0xc
call mrc_smbus_outb
mov eax, 0xa
call usleep
dec dword [ebp - 0x24]
jne loc_fffc5f8d  ; jne 0xfffc5f8d
jmp near loc_fffc63ef  ; jmp 0xfffc63ef

loc_fffc626d:  ; not directly referenced
mov eax, dword [ebp + 0x18]
sub eax, 2
cmp eax, 9
ja loc_fffc63f4  ; ja 0xfffc63f4
jmp dword [eax*4 + ref_fffcc218]  ; ujmp: jmp dword [eax*4 - 0x33de8]

loc_fffc6283:  ; not directly referenced
mov eax, 6
call mrc_smbus_inb
mov ecx, dword [ebp + 0x24]
mov byte [ecx + 1], al
jmp near loc_fffc6340  ; jmp 0xfffc6340

loc_fffc6298:  ; not directly referenced
xor esi, esi
cmp dword [edi], 1
ja loc_fffc6333  ; ja 0xfffc6333
jmp near loc_fffc6340  ; jmp 0xfffc6340

loc_fffc62a8:  ; not directly referenced
mov eax, 7
call mrc_smbus_inb
mov ecx, dword [ebp + 0x24]
mov byte [ecx + esi], al
mov eax, dword [edi]
lea edx, [eax - 2]
cmp esi, edx
jne short loc_fffc62d3  ; jne 0xfffc62d3
mov eax, 2
call mrc_smbus_inb
or eax, 0x20
movzx edx, al
jmp short loc_fffc62ea  ; jmp 0xfffc62ea

loc_fffc62d3:  ; not directly referenced
dec eax
cmp esi, eax
jne short loc_fffc62f4  ; jne 0xfffc62f4
mov eax, 2
call mrc_smbus_inb
mov edx, eax
and edx, 0xdf

loc_fffc62ea:  ; not directly referenced
mov eax, 2
call mrc_smbus_outb

loc_fffc62f4:  ; not directly referenced
xor eax, eax
mov edx, 0x80
call mrc_smbus_outb
mov eax, dword [edi]
dec eax
cmp esi, eax
jae short loc_fffc6332  ; jae 0xfffc6332
mov dword [ebp - 0x1c], 0x64

loc_fffc630e:  ; not directly referenced
xor eax, eax
call mrc_smbus_inb
test al, al
js short loc_fffc6332  ; js 0xfffc6332
mov eax, 0xa
call usleep
dec dword [ebp - 0x1c]
jne short loc_fffc630e  ; jne 0xfffc630e

loc_fffc6328:  ; not directly referenced
mov ebx, 0x80000012
jmp near loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc6332:  ; not directly referenced
inc esi

loc_fffc6333:  ; not directly referenced
cmp esi, dword [edi]
jb loc_fffc62a8  ; jb 0xfffc62a8
jmp near loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc6340:  ; not directly referenced
mov eax, 5
call mrc_smbus_inb
mov ecx, dword [ebp + 0x24]
mov byte [ecx], al
jmp near loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc6354:  ; not directly referenced
mov edx, 0x80
xor eax, eax
call mrc_smbus_outb
jmp near loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc6365:  ; not directly referenced
mov eax, 5
xor esi, esi
call mrc_smbus_inb
movzx edx, al
cmp dword [edi], edx
mov al, 1
jae short loc_fffc6393  ; jae 0xfffc6393
jmp short loc_fffc6399  ; jmp 0xfffc6399

loc_fffc637c:  ; not directly referenced
mov eax, 7
mov dword [ebp - 0x34], edx
call mrc_smbus_inb
mov ecx, dword [ebp + 0x24]
mov byte [ecx + esi], al
inc esi
mov edx, dword [ebp - 0x34]

loc_fffc6393:  ; not directly referenced
cmp esi, edx
jb short loc_fffc637c  ; jb 0xfffc637c
xor eax, eax

loc_fffc6399:  ; not directly referenced
test al, al
mov eax, 0x80000005
mov dword [edi], edx
cmovne ebx, eax
jmp short loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc63a7:  ; not directly referenced
mov eax, 5
call mrc_smbus_inb
test al, al
je short loc_fffc63e8  ; je 0xfffc63e8
movzx ecx, al
movzx edx, byte [edi]
lea eax, [edx + ecx]
cmp eax, 0x20
jg short loc_fffc63ef  ; jg 0xfffc63ef
xor esi, esi
mov edx, ecx
jmp short loc_fffc63e0  ; jmp 0xfffc63e0

loc_fffc63c9:  ; not directly referenced
mov eax, 7
mov dword [ebp - 0x34], edx
call mrc_smbus_inb
mov ecx, dword [ebp + 0x24]
mov byte [ecx + esi], al
inc esi
mov edx, dword [ebp - 0x34]

loc_fffc63e0:  ; not directly referenced
cmp esi, edx
jb short loc_fffc63c9  ; jb 0xfffc63c9
mov dword [edi], edx
jmp short loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc63e8:  ; not directly referenced
mov ebx, 0x80000005
jmp short loc_fffc63f4  ; jmp 0xfffc63f4

loc_fffc63ef:  ; not directly referenced
mov ebx, 0x80000007

loc_fffc63f4:  ; not directly referenced
mov edx, 0xff
xor eax, eax
call mrc_smbus_outb
mov edx, 1
mov eax, 0xc
call mrc_smbus_outb
xor edx, edx
mov eax, 0xd

loc_fffc6416:  ; not directly referenced
call mrc_smbus_outb
jmp short loc_fffc642a  ; jmp 0xfffc642a

loc_fffc641d:  ; not directly referenced
test al, 4
je loc_fffc622a  ; je 0xfffc622a
jmp near loc_fffc620b  ; jmp 0xfffc620b

loc_fffc642a:  ; not directly referenced
lea esp, [esp + 0x2c]
mov eax, ebx
pop ebx
pop esi
pop edi
pop ebp
ret

ref_fffcc1e8:
dd loc_fffc5fad
dd loc_fffc5fa7
dd loc_fffc5fd2
dd loc_fffc5fc4
dd loc_fffc600c
dd loc_fffc5ff0
dd loc_fffc6041
dd loc_fffc6058
dd loc_fffc60ac
dd loc_fffc6094
dd loc_fffc60ba
dd loc_fffc60f8

ref_fffcc218:
dd loc_fffc6340
dd loc_fffc63f4
dd loc_fffc6298
dd loc_fffc63f4
dd loc_fffc6283
dd loc_fffc63f4
dd loc_fffc6365
dd loc_fffc6354
dd loc_fffc6283
dd loc_fffc63a7
