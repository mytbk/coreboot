global udiv64

udiv64:
push ebp
mov ebp, esp
push edi
push esi
lea esp, [esp - 0x20]
mov eax, dword [ebp + 0x14]
mov edi, dword [ebp + 8]
mov ecx, dword [ebp + 0x10]
test eax, eax
mov dword [ebp - 0x10], edi
mov esi, dword [ebp + 0xc]
mov dword [ebp - 0xc], ecx
jne short loc_fffc9218  ; jne 0xfffc9218
cmp ecx, esi
ja short loc_fffc9258  ; ja 0xfffc9258
test ecx, ecx
jne short loc_fffc9202  ; jne 0xfffc9202
mov eax, 1
xor edx, edx
div ecx
mov ecx, eax

loc_fffc9202:
mov eax, esi
xor edx, edx
div ecx
mov esi, eax
mov eax, edi
div ecx
mov edx, esi

loc_fffc9210:
lea esp, [esp + 0x20]
pop esi
pop edi
pop ebp
ret

loc_fffc9218:
cmp eax, esi
ja short loc_fffc9248  ; ja 0xfffc9248
bsr ecx, eax
xor ecx, 0x1f
mov dword [ebp - 0x20], ecx
jne short loc_fffc9268  ; jne 0xfffc9268
mov edi, dword [ebp - 0x10]
xor edx, edx
cmp dword [ebp - 0xc], edi
jbe loc_fffc92d8  ; jbe 0xfffc92d8
cmp eax, esi
jb loc_fffc92d8  ; jb 0xfffc92d8
xor eax, eax
jmp short loc_fffc9210  ; jmp 0xfffc9210

loc_fffc9241:
db 0x8d
db 0xb4
db 0x26
dd 0x00000000

loc_fffc9248:
xor edx, edx
xor eax, eax
lea esp, [esp + 0x20]
pop esi
pop edi
pop ebp
ret

loc_fffc9254:
dd 0x0026748d

loc_fffc9258:
mov eax, edi
mov edx, esi
div ecx
xor edx, edx
lea esp, [esp + 0x20]
pop esi
pop edi
pop ebp
ret

loc_fffc9268:
movzx ecx, byte [ebp - 0x20]
mov edi, dword [ebp - 0xc]
mov edx, dword [ebp - 0xc]
shl eax, cl
mov dword [ebp - 0x18], eax
mov eax, 0x20
sub eax, dword [ebp - 0x20]
mov ecx, eax
shr edi, cl
or edi, dword [ebp - 0x18]
movzx ecx, byte [ebp - 0x20]
shl edx, cl
mov ecx, eax
mov dword [ebp - 0x18], edx
mov edx, esi
shr edx, cl
movzx ecx, byte [ebp - 0x20]
mov dword [ebp - 0x1c], edx
mov edx, dword [ebp - 0x10]
shl esi, cl
mov ecx, eax
shr edx, cl
mov eax, edx
or eax, esi
mov esi, dword [ebp - 0x1c]
mov edx, esi
div edi
mov esi, edx
mov dword [ebp - 0xc], eax
mul dword [ebp - 0x18]
cmp esi, edx
jb short loc_fffc92e8  ; jb 0xfffc92e8
movzx ecx, byte [ebp - 0x20]
mov edi, dword [ebp - 0x10]
shl edi, cl
cmp edi, eax
jae short loc_fffc92cd  ; jae 0xfffc92cd
cmp esi, edx
je short loc_fffc92e8  ; je 0xfffc92e8

loc_fffc92cd:
mov eax, dword [ebp - 0xc]
xor edx, edx
jmp near loc_fffc9210  ; jmp 0xfffc9210

loc_fffc92d7:
db 0x90

loc_fffc92d8:
mov eax, 1
jmp near loc_fffc9210  ; jmp 0xfffc9210

loc_fffc92e2:
db 0x8d
db 0xb6
dd 0x00000000

loc_fffc92e8:
mov eax, dword [ebp - 0xc]
xor edx, edx
sub eax, 1
lea esp, [esp + 0x20]
pop esi
pop edi
pop ebp
ret
