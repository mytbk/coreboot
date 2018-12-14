global PeiInstallPpi
global PeiLocatePpi
global PeiNotifyPpi
global PeiGetBootMode
global PeiGetHobList
global PeiCreateHob

extern mrc_alloc
extern mrc_printk
extern printGuid

PeiGetHobList:
push ebp
mov ebp, esp
mov eax, dword [ebp + 8]
mov eax, dword [eax]
cmp dword [eax - 4], 0xfeadb00b
je short loc_fffa0410

loc_fffa040e:
jmp short loc_fffa040e

loc_fffa0410:
mov edx, dword [eax + 0x254]
mov eax, dword [ebp + 0xc]
mov dword [eax], edx
xor eax, eax
pop ebp
ret

PeiGetBootMode:
push ebp
mov ebp, esp
mov eax, dword [ebp + 8]
mov eax, dword [eax]
cmp dword [eax - 4], 0xfeadb00b
je short loc_fffa0432

loc_fffa0430:
jmp short loc_fffa0430

loc_fffa0432:
mov edx, dword [eax + 0x68]
mov eax, dword [ebp + 0xc]
mov dword [eax], edx
xor eax, eax
pop ebp
ret

PeiCreateHob:
push ebp
mov ebp, esp
push edi
push esi
push ebx
lea esp, [esp - 0x1c]
mov ecx, dword [ebp + 8]
mov edi, dword [ebp + 0x10]
mov edx, dword [ebp + 0xc]
movzx eax, di
mov esi, dword [ebp + 0x14]
mov ebx, dword [ecx]
cmp dword [ebx - 4], 0xfeadb00b
jne short loc_fffa29f2
add eax, 4
mov dword [ebp - 0x1c], edx
call mrc_alloc
test eax, eax
mov edx, dword [ebp - 0x1c]
jne short loc_fffa29f4
jmp short loc_fffa2a1e

loc_fffa29f2:
jmp short loc_fffa29f2

loc_fffa29f4:
lea ecx, [eax + 4]
mov dword [esi], ecx
mov word [eax + 4], dx
mov edx, dword [esi]
mov word [edx + 2], di
mov edx, dword [esi]
mov dword [edx + 4], 0
mov edx, dword [ebx + 0x254]
mov dword [eax], edx
mov dword [ebx + 0x254], eax
xor eax, eax
jmp short loc_fffa2a23

loc_fffa2a1e:
mov eax, 0x80000009

loc_fffa2a23:
lea esp, [esp + 0x1c]
pop ebx
pop esi
pop edi
pop ebp
ret

PeiNotifyPpi:
push ebp
mov ebp, esp
push edi
push esi
mov eax, dword [ebp + 8]
push ebx
mov eax, dword [eax]
cmp dword [eax - 4], 0xfeadb00b
jne short loc_fffa0462
lea edx, [eax - 4]
mov ebx, 3
mov eax, dword [eax + 0x250]
jmp short loc_fffa0464

loc_fffa0462:
jmp short loc_fffa0462

loc_fffa0464:
cmp eax, 0x13
ja short loc_fffa0494
inc eax
mov esi, dword [ebp + 0xc]
imul ecx, eax, 0xc
mov dword [edx + 0x254], eax
lea edi, [edx + ecx + 0x158]
mov ecx, ebx
rep movsd
mov esi, dword [ebp + 0xc]
mov ecx, dword [esi]
add esi, 0xc
test ecx, ecx
mov dword [ebp + 0xc], esi
jns short loc_fffa0464
xor eax, eax
jmp short loc_fffa0499

loc_fffa0494:
mov eax, 0x80000009

loc_fffa0499:
pop ebx
pop esi
pop edi
pop ebp
ret

PeiLocatePpi:
push ebp
mov ebp, esp
push edi
push esi
push ebx
lea esp, [esp - 0x1c]
mov edx, dword [ebp + 8]
mov eax, dword [ebp + 0xc]
mov edx, dword [edx]
cmp dword [edx - 4], 0xfeadb00b
jne short loc_fffa2aa4
lea ecx, [edx - 4]
mov edx, dword [edx + 0x15c]
mov dword [ebp - 0x20], edx
mov dword [ebp - 0x1c], ecx
xor edx, edx
jmp short loc_fffa2aea

loc_fffa2aa4:
jmp short loc_fffa2aa4

loc_fffa2aa6:
imul ecx, edx, 0xc
mov ebx, dword [ebp - 0x1c]
lea edi, [ebx + ecx + 0x70]
mov ebx, dword [eax]
mov ecx, dword [edi + 4]
mov esi, dword [ecx + 4]
cmp dword [eax + 4], esi
jne short loc_fffa2ad7
cmp ebx, dword [ecx]
jne short loc_fffa2ad7
mov esi, dword [eax + 8]
mov ebx, dword [eax + 0xc]
xor esi, dword [ecx + 8]
xor ebx, dword [ecx + 0xc]
or esi, ebx
sete cl
movzx ecx, cl
jmp short loc_fffa2ad9

loc_fffa2ad7:
xor ecx, ecx

loc_fffa2ad9:
test ecx, ecx
je short loc_fffa2ae9
mov eax, dword [ebp + 0x18]
mov edx, dword [edi + 8]
mov dword [eax], edx
xor eax, eax
jmp short loc_fffa2af9

loc_fffa2ae9:
inc edx

loc_fffa2aea:
cmp edx, dword [ebp - 0x20]
jl short loc_fffa2aa6
call printGuid
mov eax, 0x8000000e

loc_fffa2af9:
lea esp, [esp + 0x1c]
pop ebx
pop esi
pop edi
pop ebp
ret

PeiInstallPpi:
push ebp
mov ebp, esp
push edi
push esi
push ebx
lea esp, [esp - 0x1c]
mov edx, dword [ebp + 8]
mov ebx, dword [edx]
cmp dword [ebx - 4], 0xfeadb00b
jne short loc_fffa2b1f
sub ebx, 4
jmp short loc_fffa2b21

loc_fffa2b1f:
jmp short loc_fffa2b1f

loc_fffa2b21:
mov edi, dword [ebx + 0x160]
xor esi, esi
mov dword [ebp - 0x1c], edi
jmp short loc_fffa2b87

loc_fffa2b2e:
mov edx, dword [ebp + 0xc]
mov eax, dword [edx + 4]
imul edx, esi, 0xc
mov edi, dword [eax + 4]
mov edx, dword [ebx + edx + 0x74]
cmp dword [edx + 4], edi
mov ecx, dword [edx]
jne short loc_fffa2b5f
cmp ecx, dword [eax]
jne short loc_fffa2b5f
mov ecx, dword [edx + 8]
mov edx, dword [edx + 0xc]
xor ecx, dword [eax + 8]
xor edx, dword [eax + 0xc]
or ecx, edx
sete al
movzx eax, al
jmp short loc_fffa2b61

loc_fffa2b5f:
xor eax, eax

loc_fffa2b61:
test eax, eax
je short loc_fffa2b86
push eax
push eax
push ref_fffc9eec
push ref_fffcc505
call mrc_printk
mov edx, dword [ebp + 0xc]
mov eax, dword [edx + 4]
call printGuid
add esp, 0x10
jmp short loc_fffa2b8c

loc_fffa2b86:
inc esi

loc_fffa2b87:
cmp esi, dword [ebp - 0x1c]
jne short loc_fffa2b2e

loc_fffa2b8c:
cmp esi, dword [ebx + 0x160]
jne short loc_fffa2bc0
cmp esi, 0x13
jbe short loc_fffa2bb7
push eax
push eax
push ref_fffc9eec
push ref_fffcc519
call mrc_printk
add esp, 0x10
mov eax, 0x80000009
jmp near loc_fffa2c49

loc_fffa2bb7:
lea eax, [esi + 1]
mov dword [ebx + 0x160], eax

loc_fffa2bc0:
imul esi, esi, 0xc
mov ecx, 3
lea eax, [ebx + esi + 0x70]
mov esi, dword [ebp + 0xc]
mov edi, eax
rep movsd
xor esi, esi
jmp short loc_fffa2c2c

loc_fffa2bd7:
imul eax, esi, 0xc
mov edi, dword [ebp + 0xc]
lea ecx, [ebx + eax + 0x164]
mov eax, dword [edi + 4]
mov edx, dword [ecx + 4]
mov edi, dword [edx]
mov dword [ebp - 0x1c], edi
mov edi, dword [eax + 4]
cmp dword [edx + 4], edi
jne short loc_fffa2c14
mov edi, dword [ebp - 0x1c]
cmp edi, dword [eax]
jne short loc_fffa2c14
mov edi, dword [edx + 8]
mov edx, dword [edx + 0xc]
xor edi, dword [eax + 8]
xor edx, dword [eax + 0xc]
or edi, edx
sete al
movzx eax, al
jmp short loc_fffa2c16

loc_fffa2c14:
xor eax, eax

loc_fffa2c16:
test eax, eax
je short loc_fffa2c2b
mov eax, dword [ebp + 0xc]
push edi
push dword [eax + 8]
push ecx
push dword [ebp + 8]
call dword [ecx + 8]
add esp, 0x10

loc_fffa2c2b:
inc esi

loc_fffa2c2c:
cmp esi, dword [ebx + 0x254]
jb short loc_fffa2bd7
mov edx, dword [ebp + 0xc]
mov eax, dword [edx]
add edx, 0xc
test eax, eax
mov dword [ebp + 0xc], edx
jns loc_fffa2b21
xor eax, eax

loc_fffa2c49:
lea esp, [ebp - 0xc]
pop ebx
pop esi
pop edi
pop ebp
ret

ref_fffc9eec:
db 'install_ppi',0x00

ref_fffcc505:
db '%s: overwrite GUID ',0x00

ref_fffcc519:
db '%s: no room for a new PPI',0x0a,0x00

