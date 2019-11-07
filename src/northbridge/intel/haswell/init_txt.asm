global initialize_txt

initialize_txt:
push ebx
mov edx, cr4
mov eax, edx
or eax, 0x4000 ; cr4 bit 14: Safer Mode Extensions Enable
mov cr4, eax
xor eax, eax
mov ebx, eax
getsec
mov cr4, edx
pop ebx
ret
