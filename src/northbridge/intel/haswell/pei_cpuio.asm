global gCpuIoPpi

; interface:
; CpuIoXXX(EFI_PEI_SERVICES **pps, EFI_PEI_CPU_IO_PPI *This, u64 addr, u64 data)

CpuIoWrite16:
push ebp
mov ebp, esp
mov edx, dword [ebp + 0x10]
mov eax, dword [ebp + 0x18]
out dx, ax
pop ebp
ret

CpuMemRead32:
push ebp
mov ebp, esp
mov eax, dword [ebp + 0x10]
pop ebp
mov eax, dword [eax]
ret

CpuMemRead8:
push ebp
mov ebp, esp
mov eax, dword [ebp + 0x10]
pop ebp
mov al, byte [eax]
ret

gCpuIoPpi:
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd CpuIoWrite16
dd 0x00000000
dd 0x00000000
dd CpuMemRead8
dd 0x00000000
dd CpuMemRead32
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd 0x00000000
dd 0x00000000

