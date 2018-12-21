;; looks like this is not used

global ref_fffcd554
global ref_fffcd560

extern haswell_stepping
extern haswell_family_model
extern ref_fffcd4a4
extern fcn_fffa11b3
extern PeiServiceGetBootMode
extern gEfiPeiReadOnlyVariablePpiGuid
extern wstr_pchinitpei

extern mrc_printk

printpc:
push dword [esp]
push fmt_str
call mrc_printk
add esp, 8
ret

fmt_str:
db 'EIP = 0x%x.', 0x0a, 0x00

fcn_fffa1227:  ; not directly referenced
push ebp
mov ebp, esp
lea esp, [esp - 8]

call printpc

call haswell_stepping
call haswell_family_model
mov edx, 4
mov eax, ref_fffcd4a4  ; mov eax, 0xfffcd4a4
call fcn_fffa11b3  ; call 0xfffa11b3
test eax, eax
je short loc_fffa124f  ; je 0xfffa124f
mov byte [eax + 0x49], 0

loc_fffa124f:  ; not directly referenced
xor eax, eax
leave
ret

fcn_fffc7c34:  ; not directly referenced
push ebp
mov ebp, esp
push ebx

call printpc

lea esp, [esp - 0x24]
lea eax, [ebp - 0x1c]
mov ebx, dword [ebp + 8]
call PeiServiceGetBootMode  ; call 0xfffbf908
cmp dword [ebp - 0x1c], 0x11
jne short loc_fffc7c96  ; jne 0xfffc7c96
sub esp, 0xc
lea edx, [ebp - 0x14]
mov eax, dword [ebx]
push edx
push 0
push 0
push gEfiPeiReadOnlyVariablePpiGuid
push ebx
call dword [eax + 0x20]  ; ucall
add esp, 0x18
lea eax, [ebp - 0xe]
push eax
lea eax, [ebp - 0x18]
mov dword [ebp - 0x18], 6
push eax
mov eax, dword [ebp - 0x14]
push 0
push ref_fffcd56c  ; push 0xfffcd56c
push wstr_pchinitpei
push ebx
call dword [eax]  ; ucall
add esp, 0x20
test eax, eax
js short loc_fffc7c96  ; js 0xfffc7c96
mov dx, word [ebp - 0xe]
xor eax, eax
out dx, ax

loc_fffc7c96:  ; not directly referenced
xor eax, eax
mov ebx, dword [ebp - 4]
leave
ret


; data ref

ref_fffcd554: ; a notify descriptor
dd 0x80000020
dd gEfiEndOfPeiSignalPpiGuid
dd fcn_fffa1227

ref_fffcd560: ; a notify descriptor
dd 0x80000020
dd gEfiEndOfPeiSignalPpiGuid
dd fcn_fffc7c34

ref_fffcd56c:
dd 0xa31b27a4
dd 0x48ffcae6
dd 0x42295a8c
dd 0x89f3e621

gEfiEndOfPeiSignalPpiGuid:
dd 0x605ea650
dd 0x42e1c65c
dd 0xa59180ba
dd 0xc618b62a
