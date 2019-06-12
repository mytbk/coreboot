global mrc_init_memory

extern mrc_zeromem
extern mrc_memcpy
extern haswell_family_model
extern haswell_stepping
extern gEfiPeiReadOnlyVariablePpiGuid
extern gEfiPeiStallPpiGuid
extern gPchMeUmaPpiGuid
extern ref_fffcd4a4
extern ref_fffcd4e4

extern fcn_fffa10df
extern fcn_fffa11b3
extern fcn_fffa1d20
extern fcn_fffa56ac
extern fcn_fffa782c
extern fcn_fffa7899
extern fcn_fffa78a0
extern fcn_fffa7a1c
extern fcn_fffa7e71
extern fcn_fffa7e78
extern fcn_fffa7ecd
extern fcn_fffa8fb6
extern fcn_fffa9196
extern fcn_fffa948c
extern fcn_fffa94dd
extern fcn_fffaa6af
extern fcn_fffaa884
extern fcn_fffaa9d1
extern fcn_fffaacb1
extern fcn_fffab210
extern fcn_fffab280
extern fcn_fffab4c0
extern fcn_fffad6f1
extern fcn_fffaddd4
extern fcn_fffadf82
extern fcn_fffadfcf
extern fcn_fffae02a
extern fcn_fffae04b
extern fcn_fffae06c
extern fcn_fffae80e
extern fcn_fffb2e66
extern fcn_fffb365a
extern fcn_fffb3f6c
extern fcn_fffb5038
extern fcn_fffb514c
extern fcn_fffb5535
extern fcn_fffb568f
extern fcn_fffb5763
extern fcn_fffb5811
extern fcn_fffb58c8
extern fcn_fffb59af
extern fcn_fffb5a70
extern fcn_fffb5c9f
extern fcn_fffb5cbc
extern fcn_fffb8040
extern fcn_fffb85ca
extern fcn_fffb8625
extern fcn_fffb8689
extern fcn_fffb89f8
extern fcn_fffb8c0b
extern fcn_fffb8d2d
extern fcn_fffba408
extern fcn_fffbb819
extern fcn_fffbd4c2
extern fcn_fffbd5ac
extern fcn_fffbd7da
extern fcn_fffc6438
extern fcn_fffc6986
extern fcn_fffc7720
extern fcn_fffc83be

extern frag_fffc1d20
extern frag_fffc1fc3
extern create_raminit_hob

initialize_txt:
mov edx, cr4
mov eax, edx
or eax, 0x4000 ; cr4 bit 14: Safer Mode Extensions Enable
mov cr4, eax
xor eax, eax
mov ebx, eax
getsec
mov cr4, edx
ret


; mrc_init_memory(eax is **PeiServices)
mrc_init_memory:
push ebp
mov edx, 0x5022
mov ebp, esp
push edi
push esi
push ebx
lea esp, [esp - 0x50bc]
mov dword [ebp - 0x50bc], eax
lea eax, [ebp - 0x503a]
call mrc_zeromem
lea eax, [ebp - 0x5079]
mov ecx, 0x3f
mov edx, ref_fffcbee8
mov dword [ebp - 0x38ce], eax
call mrc_memcpy
mov edx, dword [ebp - 0x50bc]
push edi
push edi
mov eax, dword [edx]
lea edx, [ebp - 0x509c] ; stores boot mode
push edx
push dword [ebp - 0x50bc]
call dword [eax + 0x28] ; GetBootMode
add esp, 0x10
cmp dword [ebp - 0x509c], 0x11
je short loc_fffc1bfd
call create_raminit_hob
mov dword [ebp - 0x50a0], eax
jmp short loc_fffc1c07

loc_fffc1bfd: ; boot mode is 3
mov dword [ebp - 0x50a0], 0

loc_fffc1c07:
mov edx, dword [ebp - 0x50bc]
sub esp, 0xc
mov esi, 1
xor edi, edi
mov eax, dword [edx]
lea edx, [ebp - 0x50a4]
push edx
push 0
push 0
push ref_fffcd4e4
push dword [ebp - 0x50bc]
call dword [eax + 0x20] ; LocatePpi
add esp, 0x20
lea eax, [ebp - 0x503a]
mov edx, 0xdd00
call fcn_fffc83be
mov ecx, dword [ebp - 0x50bc]
sub esp, 0xc
lea edx, [ebp - 0x50a8]
mov byte [ebp - 0x50aa], 0
mov eax, dword [ecx]
push edx
push 0
push 0
push gEfiPeiReadOnlyVariablePpiGuid
push ecx
call dword [eax + 0x20] ; LocatePpi
mov eax, esi
mov ecx, edi
cpuid
add esp, 0x20
and cl, 0x40
je loc_fffc1d20  ; je 0xfffc1d20
mov eax, esi
mov ecx, edi
cpuid
mov esi, ecx
xor eax, eax
and esi, 0x40
je short loc_fffc1ca2  ; je 0xfffc1ca2
call initialize_txt ; this will set ebx to 0
xor ebx, ebx

loc_fffc1ca2:
test al, 1
je short loc_fffc1d20  ; je 0xfffc1d20
mov edx, dword [ebp - 0x50bc]
sub esp, 0xc
mov ebx, 0x2ee
mov eax, dword [edx]
lea edx, [ebp - 0x5088]
push edx
push 0
push 0
push gEfiPeiStallPpiGuid
push dword [ebp - 0x50bc]
call dword [eax + 0x20] ; LocatePpi
add esp, 0x20

loc_fffc1cd2:
mov ecx, dword [ebp - 0x50bc]
mov eax, dword [ecx]
mov eax, dword [eax + 0x60]
push 0
push 0xfed40000
push eax
push ecx
call dword [eax + 0x30] ; GetHobList
add esp, 0x10
cmp al, 0xff
je short loc_fffc1d15  ; je 0xfffc1d15
test al, al
js loc_fffc2369  ; js 0xfffc2369
push esi
mov eax, dword [ebp - 0x5088]
push 0x3e8
push eax
push dword [ebp - 0x50bc]
call dword [eax + 4]  ; ucall
add esp, 0x10
dec bx
jne short loc_fffc1cd2  ; jne 0xfffc1cd2

loc_fffc1d15:
mov ecx, 0x2e6
xor eax, eax
xor edx, edx
wrmsr

loc_fffc1d20:
cmp dword [ebp - 0x509c], 0x11
mov dword [ebp - 0x50c4], 2
je short loc_fffc1d5a  ; je 0xfffc1d5a
call frag_fffc1d20
mov dword [ebp - 0x50c4], eax

loc_fffc1d5a:
lea eax, [ebp - 0x5094]
xor ebx, ebx
call fcn_fffa9196  ; call 0xfffa9196
mov eax, dword [ebp - 0x50a4]
mov esi, dword [eax + 0x15]
test esi, esi
je short loc_fffc1dac  ; je 0xfffc1dac
cmp dword [ebp - 0x509c], 4
je short loc_fffc1dac  ; je 0xfffc1dac
lea eax, [esi + 4]
mov edx, 0xfd0
call fcn_fffab210  ; call 0xfffab210
cmp eax, dword [esi]
jne short loc_fffc1dac  ; jne 0xfffc1dac
mov edx, dword [ebp - 0x50bc]
push ebx
mov bl, 1
mov eax, dword [edx]
lea edx, [ebp - 0x5036]
push 0xfd4
push esi
push edx
call dword [eax + 0x50] ; CopyMem
add esp, 0x10

loc_fffc1dac:
cmp dword [ebp - 0x509c], 0x11
jne short loc_fffc1dc2  ; jne 0xfffc1dc2
test bl, bl
mov eax, 0x8000000e
je loc_fffc23a2  ; je 0xfffc23a2

loc_fffc1dc2:
mov ecx, dword [ebp - 0x50bc]
sub esp, 0xc
lea edx, [ebp - 0x5098]
mov eax, dword [ecx]
push edx
push 0
push 0
push gPchMeUmaPpiGuid
push ecx
call dword [eax + 0x20] ; LocatePpi
mov eax, dword [ebp - 0x50c4]
add esp, 0x20
dec eax
cmp eax, 1
jbe short loc_fffc1e18  ; jbe 0xfffc1e18
push ecx
lea eax, [ebp - 0x50aa]
push eax
mov eax, dword [ebp - 0x5098]
push 0
push dword [ebp - 0x50bc]
call dword [eax + 4]  ; ucall
add esp, 0x10
mov al, 0
cmp byte [ebp - 0x50aa], 1
cmove ebx, eax

loc_fffc1e18:
call haswell_family_model
mov esi, eax
call haswell_stepping
cmp esi, 0x40650
jne short loc_fffc1e38
mov dword [ebp - 0x4035], 0x40650
jmp short loc_fffc1e8b

loc_fffc1e38:
cmp esi, 0x306c0
jne short loc_fffc1e79
cmp eax, 2
mov dword [ebp - 0x4035], 0x306c0
je short loc_fffc1e61
cmp eax, 3
je short loc_fffc1e6d
dec eax
setne al
movzx eax, al
lea eax, [eax + eax + 1]
jmp short loc_fffc1e96  ; jmp 0xfffc1e96

loc_fffc1e61:
mov dword [ebp - 0x4039], 2
jmp short loc_fffc1ea8  ; jmp 0xfffc1ea8

loc_fffc1e6d:
mov dword [ebp - 0x4039], 3
jmp short loc_fffc1ea8  ; jmp 0xfffc1ea8

loc_fffc1e79:
cmp esi, 0x40660
jne short loc_fffc1ea8  ; jne 0xfffc1ea8
mov dword [ebp - 0x4035], 0x40660

loc_fffc1e8b:
test eax, eax
je short loc_fffc1e9e  ; je 0xfffc1e9e
dec eax
sete al
movzx eax, al

loc_fffc1e96:
mov dword [ebp - 0x4039], eax
jmp short loc_fffc1ea8  ; jmp 0xfffc1ea8

loc_fffc1e9e:
mov dword [ebp - 0x4039], 0

loc_fffc1ea8:
mov eax, dword [ebp - 0x50c4]
dec eax
cmp eax, 1
jbe short loc_fffc1ee8  ; jbe 0xfffc1ee8
dec bl
jne loc_fffc2376  ; jne 0xfffc2376
mov edx, dword [ebp - 0x50a4]
mov eax, dword [edx + 9]
cmp byte [eax + 0x56], 0
je loc_fffc2376  ; je 0xfffc2376
lea eax, [ebp - 0x503a]
mov edi, 3
call fcn_fffa10df  ; call 0xfffa10df
test al, al
je short loc_fffc1f53  ; je 0xfffc1f53
jmp near loc_fffc2376  ; jmp 0xfffc2376

loc_fffc1ee8:
test bl, bl
je loc_fffc2376  ; je 0xfffc2376
mov edx, dword [ebp - 0x50a4]
lea eax, [ebp - 0x503a]
call fcn_fffa10df  ; call 0xfffa10df
dec al
je loc_fffc2376  ; je 0xfffc2376
mov eax, dword [ebp - 0x50a4]
mov eax, dword [eax + 1]
mov eax, dword [eax + 4]
movq qword [ebp - 0x5088], mm0
movq mm0, qword [eax + 0x5d10]
movq qword [ebp - 0x5090], mm0
movq mm0, qword [ebp - 0x5088]
emms
mov eax, dword [ebp - 0x508c]
or eax, dword [ebp - 0x5090]
mov edi, dword [ebp - 0x50c4]
jne short loc_fffc1f53  ; jne 0xfffc1f53
dec edi
je loc_fffc2376  ; je 0xfffc2376
mov edi, 2

loc_fffc1f53:
mov edx, 4
mov eax, ref_fffcd4a4  ; mov eax, 0xfffcd4a4
call fcn_fffa11b3  ; call 0xfffa11b3
test eax, eax
je short loc_fffc1f77  ; je 0xfffc1f77
mov dl, byte [eax + 0x21]
add dl, byte [eax + 0x19]
je short loc_fffc1f77  ; je 0xfffc1f77
movzx edx, dl
mov dword [ebp - 0x3fdb], edx

loc_fffc1f77:
push eax
lea ecx, [ebp - 0x4062]
mov edx, edi
push eax
push dword [ebp - 0x50a4]
push dword [ebp - 0x50bc]
mov eax, dword [ebp - 0x509c]
call fcn_fffa1d20  ; call 0xfffa1d20
mov dword [ebp - 0x4015], eax
mov dword [ebp - 0x3feb], 0
pop eax
pop edx
mov eax, dword [ebp - 0x5098]
push 0
push dword [ebp - 0x50bc]
call dword [eax]  ; ucall
mov dword [ebp - 0x3feb], eax
add esp, 0x10

loc_fffc1fc3:
mov ecx, dword [ebp - 0x4015]
test ecx, ecx
jne short loc_fffc2000  ; jne 0xfffc2000

; ecx needs to be saved
mov esi, ecx
call frag_fffc1fc3
mov ecx, esi

loc_fffc2000:
lea eax, [ebp - 0x397c]
mov dword [ebp - 0x3963], ecx
mov ebx, 1
call fcn_fffa9196  ; call 0xfffa9196
mov dl, 1
mov word [ebp - 0x50c0], 0
jmp near loc_fffc2116

loc_fffc2026:
movzx esi, word [ebp - 0x50c0]
imul esi, esi, 0xc
movzx eax, ax
movzx edx, word [esi + ref_fffcbf2c]  ; movzx edx, word [esi - 0x340d4]
cmp word [esi + ref_fffcbf2c], -1
lea ecx, [esi + ref_fffcbf28]  ; lea ecx, [esi - 0x340d8]
cmove edx, eax
lea eax, [ebp - 0x503a]
mov dword [ebp - 0x50c8], ecx
call fcn_fffc83be  ; call 0xfffc83be
cmp dword [esi + ref_fffcbf28], 0  ; cmp dword [esi - 0x340d8], 0
mov dl, 1
mov ecx, dword [ebp - 0x50c8]
je loc_fffc210f  ; je 0xfffc210f
mov al, byte [ecx + 0xb]
cmp byte [ebp - 0x4022], al
jae loc_fffc210f  ; jae 0xfffc210f
mov eax, dword [ebp - 0x4021]
test eax, eax
jne short loc_fffc2090  ; jne 0xfffc2090
test byte [ecx + 0xa], 0x10
jmp short loc_fffc2097  ; jmp 0xfffc2097

loc_fffc2090:
dec eax
jne short loc_fffc210f  ; jne 0xfffc210f
test byte [ecx + 0xa], 0x20

loc_fffc2097:
je short loc_fffc210f  ; je 0xfffc210f
mov eax, dword [ebp - 0x3963]
cmp eax, 2
jne short loc_fffc20aa  ; jne 0xfffc20aa
test byte [ecx + 0xa], 8
jmp short loc_fffc20be  ; jmp 0xfffc20be

loc_fffc20aa:
cmp eax, 3
jne short loc_fffc20b5  ; jne 0xfffc20b5
test byte [ecx + 0xa], 2
jmp short loc_fffc20be  ; jmp 0xfffc20be

loc_fffc20b5:
cmp eax, 1
jne short loc_fffc20c2  ; jne 0xfffc20c2
test byte [ecx + 0xa], 4

loc_fffc20be:
jne short loc_fffc20ce  ; jne 0xfffc20ce
jmp short loc_fffc210d  ; jmp 0xfffc210d

loc_fffc20c2:
test eax, eax
mov dl, 1
jne short loc_fffc210f  ; jne 0xfffc210f
test byte [ecx + 0xa], 1
je short loc_fffc210f  ; je 0xfffc210f

loc_fffc20ce:
mov edx, dword [ecx + 6]
cmp edx, 0x3b
jbe short loc_fffc20fc  ; jbe 0xfffc20fc

loc_fffc20d6:
call fcn_fffc6986  ; call 0xfffc6986
sub esp, 0xc
lea edx, [ebp - 0x503a]
push edx
call dword [esi + ref_fffcbf28]  ; ucall: call dword [esi - 0x340d8]
mov ebx, eax
call fcn_fffc6986  ; call 0xfffc6986
add esp, 0x10
test ebx, ebx
sete dl
jmp short loc_fffc210f  ; jmp 0xfffc210f

loc_fffc20fc:
xor ecx, ecx
lea eax, [ebp - 0x503a]
call fcn_fffc6438  ; call 0xfffc6438
test eax, eax
je short loc_fffc20d6  ; je 0xfffc20d6

loc_fffc210d:
mov dl, 1

loc_fffc210f:
inc word [ebp - 0x50c0]

loc_fffc2116:
mov eax, dword [ebp - 0x50c0]
sub ax, 0x2300
cmp word [ebp - 0x50c0], 0x33
setbe cl
test cl, dl
jne loc_fffc2026  ; jne 0xfffc2026
cmp ebx, 0x16
je loc_fffc21fe  ; je 0xfffc21fe
ja short loc_fffc2151  ; ja 0xfffc2151
test ebx, ebx
je loc_fffc225d  ; je 0xfffc225d
cmp ebx, 0x15
jne loc_fffc2251  ; jne 0xfffc2251
jmp short loc_fffc2186  ; jmp 0xfffc2186

loc_fffc2151:
cmp ebx, 0x17
je short loc_fffc21b8  ; je 0xfffc21b8
cmp ebx, 0x1b
jne loc_fffc2251  ; jne 0xfffc2251
lea eax, [ebp - 0x397c]
mov edx, 0x395c
call mrc_zeromem
lea eax, [ebp - 0x5079]
inc byte [ebp - 0x4022]
mov dword [ebp - 0x38ce], eax
jmp near loc_fffc225d  ; jmp 0xfffc225d

loc_fffc2186:
sub esp, 0xc
lea ecx, [ebp - 0x50a9]
push 0
lea edx, [ebp - 0x5088]
lea eax, [ebp - 0x503a]
call fcn_fffb5038  ; call 0xfffb5038
add esp, 0x10
mov cl, byte [ebp - 0x3964]
cmp byte [ebp - 0x50a9], cl
jb short loc_fffc21b8  ; jb 0xfffc21b8
jmp near loc_fffc2251  ; jmp 0xfffc2251

loc_fffc21b8:
cmp dword [ebp - 0x4015], 3
jne short loc_fffc21ed  ; jne 0xfffc21ed
push eax
lea ecx, [ebp - 0x4062]
xor edx, edx
push eax
push dword [ebp - 0x50a4]
push dword [ebp - 0x50bc]
mov eax, dword [ebp - 0x509c]
call fcn_fffa1d20  ; call 0xfffa1d20
mov dword [ebp - 0x4015], eax
add esp, 0x10
jmp short loc_fffc21f7  ; jmp 0xfffc21f7

loc_fffc21ed:
mov dword [ebp - 0x4015], 0

loc_fffc21f7:
mov ebx, 0x17
jmp short loc_fffc225d  ; jmp 0xfffc225d

loc_fffc21fe:
push eax
push eax
push dword [ebp - 0x3feb]
push dword [ebp - 0x391a]
mov eax, dword [ebp - 0x5098]
push 1
push edi
push 0
push dword [ebp - 0x50bc]
call dword [eax + 8]  ; ucall
add esp, 0x20
lea eax, [ebp - 0x503a]
mov edx, 0xddfe
call fcn_fffc83be  ; call 0xfffc83be

; ReportStatusCode is not used in mrc
; mov edx, dword [ebp - 0x50bc]
; push eax
; push eax
; mov eax, dword [edx]
; push 0
; push 0
; push 0
; push 0x51009
; push 2
; push edx
; call dword [eax + 0x58]  ; ucall
; add esp, 0x20

loc_fffc2251:
in al, 0x80
or eax, 0xffffff80
out 0x80, al
jmp near loc_fffc239d  ; jmp 0xfffc239d

loc_fffc225d:
cmp ebx, 0x1b
sete dl
cmp ebx, 0x17
sete al
or dl, al
jne loc_fffc1fc3  ; jne 0xfffc1fc3
mov eax, 0x100
in al, 0x84
test edi, edi
mov ecx, dword [ebp - 0x3feb]
sete bl
cmp byte [ebp - 0x50c4], 1
sete al
and eax, ebx
neg eax
and eax, 3
cmp ecx, 0x20
ja short loc_fffc22d0  ; ja 0xfffc22d0
mov edx, dword [0xf0000060]
and edx, 0xfc000000
mov edx, dword [edx + 0xb0010]
inc edx
je short loc_fffc22d0  ; je 0xfffc22d0
push esi
movzx eax, al
push esi
push ecx
push dword [ebp - 0x391a]
push eax
mov eax, dword [ebp - 0x5098]
push edi
push 0
push dword [ebp - 0x50bc]
call dword [eax + 8]  ; ucall
add esp, 0x20

loc_fffc22d0:
cmp dword [ebp - 0x509c], 0x11
je short loc_fffc2355  ; je 0xfffc2355
cmp edi, 3
sete dl
xor eax, eax
or dl, bl
jne short loc_fffc22ea  ; jne 0xfffc22ea
jmp short loc_fffc2311  ; jmp 0xfffc2311

loc_fffc22e7:
mov byte [eax], al
inc eax

loc_fffc22ea:
cmp eax, 0x1000
jne short loc_fffc22e7  ; jne 0xfffc22e7
mov edx, 0x14
jmp short loc_fffc230d  ; jmp 0xfffc230d

loc_fffc22f8:
cmp byte [eax], cl
jne loc_fffc238d  ; jne 0xfffc238d
inc eax

loc_fffc2301:
cmp eax, 0x1000
mov cl, al
jne short loc_fffc22f8  ; jne 0xfffc22f8
dec edx
je short loc_fffc2311  ; je 0xfffc2311

loc_fffc230d:
xor eax, eax
jmp short loc_fffc2301  ; jmp 0xfffc2301

loc_fffc2311:
mov ecx, dword [ebp - 0x50bc]
mov dword [ebp - 0x503a], 0xfd4
push edx
lea edx, [ebp - 0x503a]
mov eax, dword [ecx]
push 0x5022
push edx
mov edx, dword [ebp - 0x50a0]
add edx, 0x18
push edx
call dword [eax + 0x50]  ; ucall
mov eax, dword [ebp - 0x50a0]
mov edx, 1
add eax, 0x503a
call mrc_zeromem
add esp, 0x10

loc_fffc2355:
lea eax, [ebp - 0x503a]
mov edx, 0x55
call fcn_fffc83be  ; call 0xfffc83be
xor eax, eax
jmp short loc_fffc23a2  ; jmp 0xfffc23a2

loc_fffc2369:
test al, 1
jne loc_fffc1d15  ; jne 0xfffc1d15
jmp near loc_fffc1d20  ; jmp 0xfffc1d20

loc_fffc2376:
mov edx, 0xfd4
lea eax, [ebp - 0x5036]
call mrc_zeromem
xor edi, edi
jmp near loc_fffc1f53  ; jmp 0xfffc1f53

loc_fffc238d:
mov edx, 0xd5
lea eax, [ebp - 0x503a]
call fcn_fffc83be  ; call 0xfffc83be

loc_fffc239d:
mov eax, 0x80000007

loc_fffc23a2:
lea esp, [ebp - 0xc]
pop ebx
pop esi
pop edi
pop ebp
ret


ref_fffcbee8:
dd 0x4000f001
dd 0x02005a01
dd 0x011800dc
dd 0x9004005a
dd 0xa0020801
dd 0x01900500
dd 0x00a00208
dd 0xe000f010
dd 0x11000001
dd 0x01e000f0
dd 0xc0200000
dd 0x00018000
dd 0x00c02100
dd 0x00000180
dd 0x2200be0b
dd 0x00000001

ref_fffcbf28:
dd fcn_fffaa884

ref_fffcbf2c:
dd 0x0000dd1b
dd 0xff320000
dd fcn_fffaa6af
dd 0x0001dd1c
dd 0xff3e0000
dd fcn_fffa7899
dd 0x0004dd1e
dd 0xff3f0000
dd fcn_fffa78a0
dd 0x0005dd1f
dd 0xff3f0000
dd fcn_fffb8689
dd 0x0003dd20
dd 0xff310000
dd fcn_fffa782c
dd 0x0006dd21
dd 0xff3f0000
dd fcn_fffa7a1c
dd 0x0007dd22
dd 0xff3f0000
dd fcn_fffa56ac
dd 0x0008dd23
dd 0xff3f0000
dd fcn_fffc7720
dd 0x0009dd24
dd 0xff3f0000
dd fcn_fffbd7da
dd 0x000add26
dd 0xff330000
dd fcn_fffb8c0b
dd 0x000bdd27
dd 0xff330000
dd fcn_fffb3f6c
dd 0x000fdd29
dd 0xff310000
dd fcn_fffab4c0
dd 0x000ddd28
dd 0xff310000
dd fcn_fffbd5ac
dd 0x000edd25
dd 0xff330000
dd fcn_fffa94dd
dd 0x0011dd2b
dd 0xff310000
dd fcn_fffae06c
dd 0x0010dd2a
dd 0xff310000
dd fcn_fffba408
dd 0x0012dd2c
dd 0xff310000
dd fcn_fffb8625
dd 0x0014dd2e
dd 0xff310000
dd fcn_fffae02a
dd 0x0015dd2f
dd 0xff310000
dd fcn_fffb8d2d
dd 0x0020dd49
dd 0xff310000
dd fcn_fffb5763
dd 0x0016dd46
dd 0xff310000
dd fcn_fffb5cbc
dd 0x0017dd30
dd 0xff310000
dd fcn_fffb5535
dd 0x0018dd30
dd 0xff310000
dd fcn_fffb5c9f
dd 0x0019dd32
dd 0xff310000
dd fcn_fffb58c8
dd 0x001bdd33
dd 0xff310000
dd fcn_fffb5a70
dd 0x001cdd35
dd 0xff310000
dd fcn_fffb5811
dd 0x001add45
dd 0xff310000
dd fcn_fffb59af
dd 0x001edd37
dd 0xff310000
dd fcn_fffb568f
dd 0x001ddd36
dd 0xff310000
dd fcn_fffb514c
dd 0x001fdd41
dd 0xff310000
dd fcn_fffb89f8
dd 0x0032dd3d
dd 0xff310000
dd fcn_fffad6f1
dd 0x0026dd3e
dd 0xff310000
dd fcn_fffaddd4
dd 0x0023dd3a
dd 0xff310000
dd fcn_fffbb819
dd 0x0024dd3b
dd 0xff310000
dd fcn_fffadf82
dd 0x0025dd3c
dd 0xff310000
dd fcn_fffb85ca
dd 0x0021dd38
dd 0xff310000
dd fcn_fffadfcf
dd 0x0022dd39
dd 0xff310000
dd fcn_fffae80e
dd 0x0027dd3f
dd 0xff310000
dd fcn_fffb365a
dd 0x0028dd40
dd 0xff310000
dd fcn_fffae04b
dd 0x0029dd47
dd 0xff310000
dd fcn_fffb2e66
dd 0x003bdd58
dd 0x01310000
dd fcn_fffb8040
dd 0x002bdd44
dd 0xff310000
dd fcn_fffb8d2d
dd 0x0020dd49
dd 0xff310000
dd fcn_fffa7ecd
dd 0x0033dd50
dd 0xff310000
dd fcn_fffab280
dd 0x002add42
dd 0xff310000
dd fcn_fffa948c
dd 0x002ddd43
dd 0xff3e0000
dd fcn_fffbd4c2
dd 0x002edd70
dd 0xff3c0000
dd fcn_fffa7e78
dd 0x002fdd71
dd 0xff3e0000
dd fcn_fffaacb1
dd 0x0030dd5b
dd 0xff310000
dd fcn_fffa7e71
dd 0x002cdd5f
dd 0xff310000
dd fcn_fffaa9d1
dd 0x0031dd5c
dd 0xff330000
dd fcn_fffa8fb6
dd 0x0034dd5d
dd 0xff3f0000

