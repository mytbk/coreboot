global PeiLocatePpi
global PeiNotifyPpi
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
