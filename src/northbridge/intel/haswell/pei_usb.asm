global mrc_init_usb

extern PeiServiceGetBootMode
extern mrc_pch_revision
extern usleep
extern mrc_pch_iobp_update
extern nb_usb2_ports
extern mrc_sku_type
extern ref_fffcb998
extern ref_fffcb99c
extern ref_fffcc988
extern xhci_setup_ss_route
extern frag_usb_fffaecbe
extern frag_usb_fffaed66
extern frag_usb_fffaeb10

mrc_init_usb:
push ebp
mov ebp, esp
push edi
push esi
lea ecx, [ebp - 0x20]
push ebx
lea esp, [esp - 0x78]
mov eax, dword [ebp + 8]
mov edx, dword [eax]
push ecx
push 0
push 0
push ref_fffcc988  ; push 0xfffcc988
push eax
call dword [edx + 0x20]  ; ucall
add esp, 0x20
test eax, eax
mov dword [ebp - 0x58], eax
jne loc_fffafa2f  ; jne 0xfffafa2f
mov eax, dword [ebp - 0x20]
mov dl, byte [eax]
mov ebx, dword [eax + 0xe]
mov esi, dword [eax + 6]
mov eax, dword [eax + 1]
test eax, eax
mov byte [ebp - 0x67], dl
mov dword [ebp - 0x30], eax
je loc_fffaf9ce  ; je 0xfffaf9ce
mov eax, dword [0xf0000060]
and eax, 0xfc000000
mov eax, dword [eax + 0xf80f0]
and eax, 0xfffffffe
mov dword [ebp - 0x44], eax
mov ecx, dword [eax + 0x3418]
mov dword [ebp - 0x48], ecx
call mrc_sku_type
mov dword [ebp - 0x5c], eax
mov eax, dword [0xf0000060]
and eax, 0xfc000000
mov dword [ebp - 0x2c], eax
mov edi, dword [0xf0000060]
mov edx, dword [0xf0000060]
and edi, 0xfc000000
and edx, 0xfc000000
cmp dword [ebp - 0x5c], 1
mov dword [ebp - 0x4c], edx
mov dword [ebp - 0x50], 0
jne short loc_fffaead0  ; jne 0xfffaead0
mov eax, dword [0xf0000060]
and eax, 0xfc000000
add eax, 0xd0000
mov dword [ebp - 0x50], eax

loc_fffaead0:
mov ecx, dword [ebp - 0x2c]
mov edx, dword [ebp - 0x2c]
mov cx, word [ecx + 0xf8040]
mov ax, word [edx + 0xf8002]
mov word [ebp - 0x6a], cx
mov ecx, dword [ebp - 0x30]
mov eax, dword [ebp - 0x48]
or ah, 0x80
test byte [ecx + 0x55], 1
cmovne eax, dword [ebp - 0x48]
cmp dword [ebp - 0x5c], 1
mov dword [ebp - 0x48], eax
jne short loc_fffaeb10  ; jne 0xfffaeb10
or ah, 0x20
test byte [ecx + 0x56], 1
cmovne eax, dword [ebp - 0x48]
mov dword [ebp - 0x48], eax

loc_fffaeb10:
mov edx, dword [ebp - 0x30]
mov eax, dword [ebp - 0x48]
or eax, 0x8000000
test byte [edx + 0x57], 3
cmovne eax, dword [ebp - 0x48]
mov dword [ebp - 0x48], eax

push esi
push dword [ebp - 0x30]
call frag_usb_fffaeb10
add esp, 8

call frag_usb_fffaecbe

loc_fffaed46:
mov eax, dword [ebp - 0x30]
test byte [eax + 0x57], 3
je short loc_fffaed66  ; je 0xfffaed66
mov dword [edi + 0xa0010], ebx
mov ax, word [edi + 0xa0004]
or eax, 6
mov word [edi + 0xa0004], ax

loc_fffaed66:
push ebx
push dword [ebp - 0x30]
call frag_usb_fffaed66
add esp, 8

loc_fffaefd0:
call mrc_sku_type
dec eax
cmp eax, 1
ja short loc_fffaefee  ; ja 0xfffaefee
mov edx, dword [eax*4 + ref_fffcb9e0]  ; mov edx, dword [eax*4 - 0x34620]
mov esi, dword [eax*4 + ref_fffcb9e8]  ; mov esi, dword [eax*4 - 0x34618]
mov dword [ebp - 0x3c], edx
jmp short loc_fffaeff7  ; jmp 0xfffaeff7

loc_fffaefee:
xor esi, esi
mov dword [ebp - 0x3c], 0

loc_fffaeff7:
mov ecx, dword [ebp - 0x30]
test byte [ecx + 0x57], 3
je loc_fffaf5ea  ; je 0xfffaf5ea
call mrc_sku_type
cmp eax, 1
jne loc_fffaf0b7  ; jne 0xfffaf0b7
mov eax, dword [edi + 0xa00e0]
and eax, 6
cmp eax, 4
je short loc_fffaf04a  ; je 0xfffaf04a
cmp eax, 6
je short loc_fffaf03c  ; je 0xfffaf03c
cmp eax, 2
setne al
movzx eax, al
lea edx, [eax + eax + 0xc]
mov dword [ebp - 0x38], edx
mov edx, 0x3fff
jmp short loc_fffaf056  ; jmp 0xfffaf056

loc_fffaf03c:
mov dword [ebp - 0x38], 8
mov edx, 0xff
jmp short loc_fffaf056  ; jmp 0xfffaf056

loc_fffaf04a:
mov dword [ebp - 0x38], 0xa
mov edx, 0xfff

loc_fffaf056:
mov ecx, dword [edi + 0xa00e0]
and ecx, 0x18
cmp ecx, 0x10
je short loc_fffaf092  ; je 0xfffaf092
cmp ecx, 0x18
je short loc_fffaf087  ; je 0xfffaf087
xor eax, eax
cmp ecx, 8
setne al
mov ecx, 0xf
lea eax, [eax + eax + 4]
mov dword [ebp - 0x34], eax
mov eax, 0x3f
cmove eax, ecx
jmp short loc_fffaf09e  ; jmp 0xfffaf09e

loc_fffaf087:
mov dword [ebp - 0x34], 0
xor eax, eax
jmp short loc_fffaf09e  ; jmp 0xfffaf09e

loc_fffaf092:
mov dword [ebp - 0x34], 2
mov eax, 3

loc_fffaf09e:
mov ecx, dword [edi + 0xa00e0]
and ecx, 0x20
je short loc_fffaf0ab  ; je 0xfffaf0ab
jmp short loc_fffaf0df  ; jmp 0xfffaf0df

loc_fffaf0ab:
or dh, 0x40
mov dword [ebp - 0x54], 1
jmp short loc_fffaf106  ; jmp 0xfffaf106

loc_fffaf0b7:
cmp eax, 2
jne short loc_fffaf0e8  ; jne 0xfffaf0e8
mov eax, dword [edi + 0xa00e0]
mov dword [ebp - 0x34], 4
and eax, 0x20
je short loc_fffaf0ee  ; je 0xfffaf0ee
mov dword [ebp - 0x38], 8
mov eax, 0xf
mov edx, 0xff

loc_fffaf0df:
mov dword [ebp - 0x54], 0
jmp short loc_fffaf106  ; jmp 0xfffaf106

loc_fffaf0e8:
xor eax, eax
xor edx, edx
jmp short loc_fffaf106  ; jmp 0xfffaf106

loc_fffaf0ee:
mov dword [ebp - 0x54], 1
mov dword [ebp - 0x38], 8
mov eax, 0xf
mov edx, 0x1ff

loc_fffaf106:
mov ecx, dword [edi + 0xa00d4]
and ecx, 0xffff8000
or ecx, edx
mov dword [edi + 0xa00d4], ecx
mov edx, dword [edi + 0xa00dc]
and edx, 0xffffffc0
or edx, eax
mov dword [edi + 0xa00dc], edx
lea eax, [ebp - 0x1c]
call PeiServiceGetBootMode
cmp dword [ebp - 0x1c], 0x11
jne short loc_fffaf177  ; jne 0xfffaf177
call xhci_setup_ss_route
jmp near loc_fffaf5ea  ; jmp 0xfffaf5ea

loc_fffaf177:
mov edx, dword [ebp - 0x2c]
mov ax, word [edx + 0xf80a2]
test al, 0x20
je short loc_fffaf1cb  ; je 0xfffaf1cb
mov eax, dword [edx + 0xf80ac]
test eax, 0x10000
je short loc_fffaf1cb  ; je 0xfffaf1cb
call xhci_setup_ss_route

loc_fffaf1cb:
mov ecx, dword [ebp - 0x2c]
mov eax, dword [ecx + 0xf80ac]
and eax, 0xfffeffff
mov dword [ecx + 0xf80ac], eax
mov edx, dword [ebp - 0x30]
mov al, byte [edx + 0x57]
mov dl, 1
test al, 4
je short loc_fffaf1f6  ; je 0xfffaf1f6
mov dl, al
and edx, 7
cmp dl, 6
sete dl

loc_fffaf1f6:
and eax, 7
cmp al, 5
jne short loc_fffaf276  ; jne 0xfffaf276
mov ecx, dword [ebp - 0x2c]
mov ax, word [ecx + 0xf80a2]
test al, 0x20
jne short loc_fffaf226  ; jne 0xfffaf226
jmp near loc_fffaf9e7  ; jmp 0xfffaf9e7

loc_fffaf210:
mov ecx, dword [esi + edx*4]
add ecx, ebx
mov eax, dword [ecx]
and eax, 0x7ffffffd
or eax, 0x80000000
mov dword [ecx], eax
inc edx
jmp short loc_fffaf228  ; jmp 0xfffaf228

loc_fffaf226:
xor edx, edx

loc_fffaf228:
cmp edx, dword [ebp - 0x34]
jne short loc_fffaf210  ; jne 0xfffaf210
mov eax, dword [ebp - 0x34]
mov dword [ebp - 0x2c], 0xa
lea eax, [esi + eax*4]
mov dword [ebp - 0x40], eax

loc_fffaf23d:
mov eax, esi
xor edx, edx
jmp short loc_fffaf24e  ; jmp 0xfffaf24e

loc_fffaf243:
mov ecx, dword [eax]
add eax, 4
add ecx, ebx
mov ecx, dword [ecx]
or edx, ecx

loc_fffaf24e:
cmp eax, dword [ebp - 0x40]
jne short loc_fffaf243  ; jne 0xfffaf243
mov eax, 0x2710
mov dword [ebp - 0x70], edx
call usleep
mov edx, dword [ebp - 0x70]
and dl, 0x10
je loc_fffaf9e7  ; je 0xfffaf9e7
dec dword [ebp - 0x2c]
jne short loc_fffaf23d  ; jne 0xfffaf23d
jmp near loc_fffaf9e7  ; jmp 0xfffaf9e7

loc_fffaf276:
cmp dword [ebp - 0x34], 0
je loc_fffaf44c  ; je 0xfffaf44c
dec dl
jne loc_fffaf3ef  ; jne 0xfffaf3ef
mov eax, dword [edi + 0xa00d0]
test eax, eax
jne short loc_fffaf2a0  ; jne 0xfffaf2a0
mov eax, dword [edi + 0xa00d8]
test eax, eax
je loc_fffaf3ef  ; je 0xfffaf3ef

loc_fffaf2a0:
xor eax, eax

loc_fffaf2a2:
mov edx, dword [ebp - 0x3c]
mov ecx, ebx
add ecx, dword [edx + eax*4]
mov edx, dword [ecx]
and dl, 1
je short loc_fffaf2bb  ; je 0xfffaf2bb
mov edx, dword [ecx]
and edx, 0xffffffed
or edx, 0x10
mov dword [ecx], edx

loc_fffaf2bb:
inc eax
cmp eax, dword [ebp - 0x38]
jb short loc_fffaf2a2  ; jb 0xfffaf2a2
mov dword [ebp - 0x2c], 0xa

loc_fffaf2c8:
mov dword [ebp - 0x60], 0
xor eax, eax

loc_fffaf2d1:
mov edx, dword [ebp - 0x3c]
mov ecx, dword [edx + eax*4]
inc eax
add ecx, ebx
mov edx, dword [ecx]
or dword [ebp - 0x60], edx
cmp eax, dword [ebp - 0x38]
jb short loc_fffaf2d1  ; jb 0xfffaf2d1
mov eax, 0x2710
call usleep
test byte [ebp - 0x60], 0x10
je short loc_fffaf2f9  ; je 0xfffaf2f9
dec dword [ebp - 0x2c]
jne short loc_fffaf2c8  ; jne 0xfffaf2c8

loc_fffaf2f9:
mov eax, dword [edi + 0xa00d0]
and eax, 0xffff8000
mov dword [edi + 0xa00d0], eax
xor edx, edx

loc_fffaf30c:
mov eax, dword [ebp - 0x3c]
mov ecx, ebx
add ecx, dword [eax + edx*4]
mov eax, dword [ecx]
and eax, 0xff01fffd
or eax, 0xfe0000
mov dword [ecx], eax
inc edx
cmp edx, dword [ebp - 0x38]
jne short loc_fffaf30c  ; jne 0xfffaf30c
cmp dword [ebp - 0x54], 0
je short loc_fffaf347  ; je 0xfffaf347
mov eax, dword [ebp - 0x3c]
mov ecx, dword [ebp - 0x38]
mov edx, ebx
add edx, dword [eax + ecx*4]
mov eax, dword [edx]
and eax, 0xff01fffd
or eax, 0xfe0000
mov dword [edx], eax

loc_fffaf347:
xor edx, edx

loc_fffaf349:
mov ecx, dword [esi + edx*4]
add ecx, ebx
mov eax, dword [ecx]
and eax, 0x7ffffffd
or eax, 0x80000000
mov dword [ecx], eax
inc edx
cmp edx, dword [ebp - 0x34]
jne short loc_fffaf349  ; jne 0xfffaf349
mov eax, dword [edi + 0xa00d8]
and eax, 0xffffffc0
mov dword [edi + 0xa00d8], eax
mov edx, dword [ebp - 0x34]
mov dword [ebp - 0x2c], 0xa
lea edx, [esi + edx*4]
mov dword [ebp - 0x40], edx

loc_fffaf381:
mov eax, esi
xor edx, edx

loc_fffaf385:
mov ecx, dword [eax]
add eax, 4
add ecx, ebx
mov ecx, dword [ecx]
or edx, ecx
cmp eax, dword [ebp - 0x40]
jne short loc_fffaf385  ; jne 0xfffaf385
mov eax, 0x2710
mov dword [ebp - 0x70], edx
call usleep
mov edx, dword [ebp - 0x70]
and dl, 0x10
je short loc_fffaf3af  ; je 0xfffaf3af
dec dword [ebp - 0x2c]
jne short loc_fffaf381  ; jne 0xfffaf381

loc_fffaf3af:
xor eax, eax

loc_fffaf3b1:
mov ecx, dword [esi + eax*4]
add ecx, ebx
mov edx, dword [ecx]
and edx, 0xff01fffd
or edx, 0xfe0000
mov dword [ecx], edx
inc eax
cmp eax, dword [ebp - 0x34]
jne short loc_fffaf3b1  ; jne 0xfffaf3b1
mov eax, dword [ebx + 0x80]
or eax, 1
mov dword [ebx + 0x80], eax
mov eax, dword [ebx + 0x80]
and eax, 0xfffffffe
mov dword [ebx + 0x80], eax
jmp near loc_fffafa2a  ; jmp 0xfffafa2a

loc_fffaf3ef:
mov ecx, dword [ebp - 0x2c]
mov ax, word [ecx + 0xf80a2]
test al, 0x20
je short loc_fffaf44c  ; je 0xfffaf44c
xor edx, edx

loc_fffaf3ff:
mov ecx, dword [esi + edx*4]
add ecx, ebx
mov eax, dword [ecx]
and eax, 0x7ffffffd
or eax, 0x80000000
mov dword [ecx], eax
inc edx
cmp edx, dword [ebp - 0x34]
jb short loc_fffaf3ff  ; jb 0xfffaf3ff
mov dword [ebp - 0x2c], 0xa

loc_fffaf41f:
xor ecx, ecx
xor eax, eax

loc_fffaf423:
mov edx, dword [esi + eax*4]
inc eax
add edx, ebx
mov edx, dword [edx]
or ecx, edx
cmp eax, dword [ebp - 0x34]
jb short loc_fffaf423  ; jb 0xfffaf423
mov eax, 0x2710
mov dword [ebp - 0x70], ecx
call usleep
mov ecx, dword [ebp - 0x70]
and cl, 0x10
je short loc_fffaf44c  ; je 0xfffaf44c
dec dword [ebp - 0x2c]
jne short loc_fffaf41f  ; jne 0xfffaf41f

loc_fffaf44c:
mov eax, dword [ebp - 0x30]
test byte [eax + 0x57], 0x10
je loc_fffaf5ea  ; je 0xfffaf5ea
xor edx, edx

loc_fffaf45b:
mov eax, dword [ebp - 0x3c]
mov ecx, ebx
add ecx, dword [eax + edx*4]
mov eax, dword [ecx]
test al, 1
je short loc_fffaf473  ; je 0xfffaf473
mov eax, dword [ecx]
and eax, 0xffffffed
or eax, 0x10
mov dword [ecx], eax

loc_fffaf473:
inc edx
cmp edx, dword [ebp - 0x38]
jb short loc_fffaf45b  ; jb 0xfffaf45b
mov dword [ebp - 0x2c], 0xa

loc_fffaf480:
mov dword [ebp - 0x60], 0
xor eax, eax

loc_fffaf489:
mov edx, dword [ebp - 0x3c]
mov ecx, dword [edx + eax*4]
inc eax
add ecx, ebx
mov edx, dword [ecx]
or dword [ebp - 0x60], edx
cmp eax, dword [ebp - 0x38]
jb short loc_fffaf489  ; jb 0xfffaf489
mov eax, 0x2710
call usleep
test byte [ebp - 0x60], 0x10
je short loc_fffaf4b1  ; je 0xfffaf4b1
dec dword [ebp - 0x2c]
jne short loc_fffaf480  ; jne 0xfffaf480

loc_fffaf4b1:
xor eax, eax
xor ecx, ecx

loc_fffaf4b5:
mov edx, dword [ebp - 0x30]
cmp byte [edx + ecx + 0x58], 1
jne short loc_fffaf4c8  ; jne 0xfffaf4c8
mov edx, 1
shl edx, cl
or eax, edx

loc_fffaf4c8:
inc ecx
cmp ecx, dword [ebp - 0x38]
jb short loc_fffaf4b5  ; jb 0xfffaf4b5
mov edx, dword [edi + 0xa00d0]
and edx, 0xffff8000
or edx, eax
mov dword [edi + 0xa00d0], edx
xor eax, eax

loc_fffaf4e4:
mov edx, dword [ebp - 0x3c]
mov ecx, ebx
add ecx, dword [edx + eax*4]
mov edx, dword [ecx]
and edx, 0xff01fffd
or edx, 0xfe0000
mov dword [ecx], edx
inc eax
cmp eax, dword [ebp - 0x38]
jne short loc_fffaf4e4  ; jne 0xfffaf4e4
cmp dword [ebp - 0x54], 0
je short loc_fffaf51e  ; je 0xfffaf51e
mov ecx, dword [ebp - 0x3c]
mov edx, ebx
add edx, dword [ecx + eax*4]
mov eax, dword [edx]
and eax, 0xff01fffd
or eax, 0xfe0000
mov dword [edx], eax

loc_fffaf51e:
xor edx, edx
jmp short loc_fffaf536  ; jmp 0xfffaf536

loc_fffaf522:
mov ecx, dword [esi + edx*4]
add ecx, ebx
mov eax, dword [ecx]
and eax, 0x7ffffffd
or eax, 0x80000000
mov dword [ecx], eax
inc edx

loc_fffaf536:
cmp edx, dword [ebp - 0x34]
jne short loc_fffaf522  ; jne 0xfffaf522
xor eax, eax
xor ecx, ecx
jmp short loc_fffaf555  ; jmp 0xfffaf555

loc_fffaf541:
mov edx, dword [ebp - 0x30]
cmp byte [edx + ecx + 0x66], 1
jne short loc_fffaf554  ; jne 0xfffaf554
mov edx, 1
shl edx, cl
or eax, edx

loc_fffaf554:
inc ecx

loc_fffaf555:
cmp ecx, dword [ebp - 0x34]
jne short loc_fffaf541  ; jne 0xfffaf541
mov edx, dword [edi + 0xa00d8]
and edx, 0xffffffc0
or edx, eax
mov dword [edi + 0xa00d8], edx
mov ecx, dword [ebp - 0x34]
mov dword [ebp - 0x38], 0xa
lea ecx, [esi + ecx*4]
mov dword [ebp - 0x2c], ecx

loc_fffaf57b:
mov eax, esi
xor edx, edx
jmp short loc_fffaf58c  ; jmp 0xfffaf58c

loc_fffaf581:
mov ecx, dword [eax]
add eax, 4
add ecx, ebx
mov ecx, dword [ecx]
or edx, ecx

loc_fffaf58c:
cmp eax, dword [ebp - 0x2c]
jne short loc_fffaf581  ; jne 0xfffaf581
mov eax, 0x2710
mov dword [ebp - 0x70], edx
call usleep
mov edx, dword [ebp - 0x70]
and dl, 0x10
je short loc_fffaf5c5  ; je 0xfffaf5c5
dec dword [ebp - 0x38]
jne short loc_fffaf57b  ; jne 0xfffaf57b
jmp short loc_fffaf5c5  ; jmp 0xfffaf5c5

loc_fffaf5ad:
mov ecx, dword [esi + eax*4]
add ecx, ebx
mov edx, dword [ecx]
and edx, 0xff01fffd
or edx, 0xfe0000
mov dword [ecx], edx
inc eax
jmp short loc_fffaf5c7  ; jmp 0xfffaf5c7

loc_fffaf5c5:
xor eax, eax

loc_fffaf5c7:
cmp eax, dword [ebp - 0x34]
jne short loc_fffaf5ad  ; jne 0xfffaf5ad
mov eax, dword [ebx + 0x80]
or eax, 1
mov dword [ebx + 0x80], eax
mov eax, dword [ebx + 0x80]
and eax, 0xfffffffe
mov dword [ebx + 0x80], eax

loc_fffaf5ea:
call mrc_sku_type
mov dword [ebp - 0x34], eax
xor esi, esi
xor edx, edx
xor ebx, ebx
jmp short loc_fffaf635  ; jmp 0xfffaf635

loc_fffaf5fa:
mov eax, dword [ecx + ebx*4 + 0x6c]
cmp eax, 8
je short loc_fffaf634  ; je 0xfffaf634
cmp ebx, 7
ja short loc_fffaf61b  ; ja 0xfffaf61b
cmp eax, 3
ja short loc_fffaf634  ; ja 0xfffaf634
lea ecx, [ebx + eax*8]
mov eax, 1
shl eax, cl
or edx, eax
jmp short loc_fffaf634  ; jmp 0xfffaf634

loc_fffaf61b:
cmp dword [ebp - 0x34], 1
jne short loc_fffaf634  ; jne 0xfffaf634
lea ecx, [eax - 4]
cmp ecx, 3
ja short loc_fffaf634  ; ja 0xfffaf634
lea ecx, [ebx + eax*8 - 0x28]
mov eax, dword [ebp - 0x34]
shl eax, cl
or esi, eax

loc_fffaf634:
inc ebx

loc_fffaf635:
mov dword [ebp - 0x70], edx
call nb_usb2_ports
movzx eax, al
mov ecx, dword [ebp - 0x30]
cmp ebx, eax
mov edx, dword [ebp - 0x70]
jb short loc_fffaf5fa  ; jb 0xfffaf5fa
test byte [ecx + 0x55], 1
je short loc_fffaf659  ; je 0xfffaf659
mov eax, dword [ebp - 0x4c]
mov dword [eax + 0xe8074], edx

loc_fffaf659:
cmp dword [ebp - 0x34], 1
jne short loc_fffaf66e  ; jne 0xfffaf66e
mov edx, dword [ebp - 0x30]
test byte [edx + 0x56], 1
je short loc_fffaf66e  ; je 0xfffaf66e
mov ecx, dword [ebp - 0x50]
mov dword [ecx + 0x74], esi

loc_fffaf66e:
call mrc_sku_type
mov dword [ebp - 0x3c], eax
mov eax, dword [ebp - 0x30]
test byte [eax + 0x57], 3
jne short loc_fffaf6c2  ; jne 0xfffaf6c2
jmp near loc_fffaf75b  ; jmp 0xfffaf75b

loc_fffaf684:
mov edx, dword [ebp - 0x30]
mov eax, dword [edx + ebx*4 + 0x6c]
cmp eax, 8
je short loc_fffaf6bf  ; je 0xfffaf6bf
cmp ebx, 7
ja short loc_fffaf6a9  ; ja 0xfffaf6a9
cmp eax, 3
ja short loc_fffaf6bf  ; ja 0xfffaf6bf
lea ecx, [ebx + eax*8]
mov eax, 1
shl eax, cl
or dword [ebp - 0x34], eax
jmp short loc_fffaf6bf  ; jmp 0xfffaf6bf

loc_fffaf6a9:
lea edx, [eax - 4]
cmp edx, 3
ja short loc_fffaf6bf  ; ja 0xfffaf6bf
lea ecx, [ebx + eax*8 - 0x28]
mov eax, 1
shl eax, cl
or dword [ebp - 0x38], eax

loc_fffaf6bf:
inc ebx
jmp short loc_fffaf6d2  ; jmp 0xfffaf6d2

loc_fffaf6c2:
mov dword [ebp - 0x38], 0
mov dword [ebp - 0x34], 0
xor ebx, ebx

loc_fffaf6d2:
call nb_usb2_ports
movzx eax, al
cmp ebx, eax
jb short loc_fffaf684  ; jb 0xfffaf684
xor esi, esi
mov dword [ebp - 0x2c], 0
xor ebx, ebx
jmp short loc_fffaf71c  ; jmp 0xfffaf71c

loc_fffaf6eb:
mov ecx, dword [ebp - 0x30]
mov eax, dword [ecx + ebx*4 + 0xa4]
cmp eax, 8
je short loc_fffaf71b  ; je 0xfffaf71b
cmp eax, 3
ja short loc_fffaf70e  ; ja 0xfffaf70e
lea ecx, [ebx + eax*8]
mov eax, 1
shl eax, cl
or dword [ebp - 0x2c], eax
jmp short loc_fffaf71b  ; jmp 0xfffaf71b

loc_fffaf70e:
lea ecx, [ebx + eax*8 - 0x20]
mov eax, 1
shl eax, cl
or esi, eax

loc_fffaf71b:
inc ebx

loc_fffaf71c:
call mrc_sku_type
dec eax
xor edx, edx
cmp eax, 1
ja short loc_fffaf730  ; ja 0xfffaf730
movzx edx, byte [eax + ref_fffcb9dc]  ; movzx edx, byte [eax - 0x34624]

loc_fffaf730:
cmp ebx, edx
jb short loc_fffaf6eb  ; jb 0xfffaf6eb
mov edx, dword [ebp - 0x34]
mov dword [edi + 0xa00c0], edx
mov edx, dword [ebp - 0x2c]
mov dword [edi + 0xa00c8], edx
cmp dword [ebp - 0x3c], 1
jne short loc_fffaf75b  ; jne 0xfffaf75b
mov edx, dword [ebp - 0x38]
mov dword [edi + 0xa00c4], edx
mov dword [edi + 0xa00cc], esi

loc_fffaf75b:
mov esi, dword [ebp - 0x30]
xor ebx, ebx
jmp short loc_fffaf797  ; jmp 0xfffaf797

loc_fffaf762:
mov al, byte [esi + 5]
mov cl, byte [esi + 6]
and eax, 7
and ecx, 7
shl ecx, 0xb
sub esp, 0xc
shl eax, 8
lea edx, [ebx + 0xe50041]
or eax, ecx
mov ecx, 0xffff80ff
push eax
shl edx, 8
mov eax, dword [ebp - 0x44]
call mrc_pch_iobp_update
inc ebx
add esi, 6
add esp, 0x10

loc_fffaf797:
call nb_usb2_ports
movzx eax, al
cmp ebx, eax
jb short loc_fffaf762  ; jb 0xfffaf762
mov ecx, dword [ebp - 0x30]
test byte [ecx], 1
je loc_fffaf94f  ; je 0xfffaf94f
mov ax, word [ebp - 0x6a]
and eax, 0xfffffffc
add eax, 0x3c
mov word [ebp - 0x34], ax
mov edx, eax
in ax, dx
mov word [ebp - 0x38], ax
or eax, 2
out dx, ax
call mrc_sku_type
mov esi, eax
xor ebx, ebx
jmp near loc_fffaf866  ; jmp 0xfffaf866

loc_fffaf7d8:
cmp ebx, 7
ja short loc_fffaf823  ; ja 0xfffaf823
mov ecx, dword [ebp - 0x30]
test byte [ecx + 0x55], 1
je short loc_fffaf823  ; je 0xfffaf823
imul eax, ebx, 6
test byte [ecx + eax + 1], 1
jne short loc_fffaf806  ; jne 0xfffaf806
mov edx, dword [ebp - 0x4c]
mov cl, bl
mov al, byte [edx + 0xe8064]
mov edx, 1
shl edx, cl
or eax, edx
jmp short loc_fffaf81a  ; jmp 0xfffaf81a

loc_fffaf806:
mov ecx, dword [ebp - 0x4c]
mov edx, 0xfffffffe
mov al, byte [ecx + 0xe8064]
mov cl, bl
rol edx, cl
and eax, edx

loc_fffaf81a:
mov edx, dword [ebp - 0x4c]
mov byte [edx + 0xe8064], al

loc_fffaf823:
cmp esi, 1
jne short loc_fffaf865  ; jne 0xfffaf865
cmp ebx, 0xd
ja short loc_fffaf865  ; ja 0xfffaf865
mov ecx, dword [ebp - 0x30]
test byte [ecx + 0x56], 1
je short loc_fffaf865  ; je 0xfffaf865
imul eax, ebx, 6
mov edx, dword [ebp - 0x50]
test byte [ecx + eax + 1], 1
mov al, byte [edx + 0x64]
lea ecx, [ebx - 8]
mov edx, esi
jne short loc_fffaf857  ; jne 0xfffaf857
shl edx, cl
mov ecx, dword [ebp - 0x50]
or eax, edx
mov byte [ecx + 0x64], al
jmp short loc_fffaf865  ; jmp 0xfffaf865

loc_fffaf857:
shl edx, cl
mov ecx, edx
not ecx
and ecx, eax
mov eax, dword [ebp - 0x50]
mov byte [eax + 0x64], cl

loc_fffaf865:
inc ebx

loc_fffaf866:
call nb_usb2_ports
movzx eax, al
cmp ebx, eax
jb loc_fffaf7d8  ; jb 0xfffaf7d8
call mrc_sku_type
mov edx, dword [ebp - 0x30]
mov dword [ebp - 0x2c], eax
test byte [edx + 0x57], 3
je loc_fffaf944  ; je 0xfffaf944
mov esi, dword [edi + 0xa00e4]
xor ebx, ebx
and esi, 0x7fff
jmp short loc_fffaf8cc  ; jmp 0xfffaf8cc

loc_fffaf89b:
cmp dword [ebp - 0x2c], 1
mov ecx, ebx
jne short loc_fffaf8aa  ; jne 0xfffaf8aa
mov ecx, dword [ebx*4 + ref_fffcb99c]  ; mov ecx, dword [ebx*4 - 0x34664]

loc_fffaf8aa:
imul eax, ebx, 6
mov edx, dword [ebp - 0x30]
test byte [edx + eax + 1], 1
jne short loc_fffaf8c2  ; jne 0xfffaf8c2
mov eax, 1
shl eax, cl
or esi, eax
jmp short loc_fffaf8cb  ; jmp 0xfffaf8cb

loc_fffaf8c2:
mov eax, 0xfffffffe
rol eax, cl
and esi, eax

loc_fffaf8cb:
inc ebx

loc_fffaf8cc:
call nb_usb2_ports
movzx eax, al
cmp ebx, eax
jb short loc_fffaf89b  ; jb 0xfffaf89b
mov ebx, dword [edi + 0xa00e8]
xor ecx, ecx
and ebx, 0x3f
jmp short loc_fffaf91a  ; jmp 0xfffaf91a

loc_fffaf8e5:
cmp byte [ebp - 0x67], 2
jbe short loc_fffaf8f8  ; jbe 0xfffaf8f8
mov eax, dword [ebp - 0x30]
test byte [eax + ecx + 0xbd], 1
jmp short loc_fffaf903  ; jmp 0xfffaf903

loc_fffaf8f8:
imul eax, ecx, 6
mov edx, dword [ebp - 0x30]
test byte [edx + eax + 1], 1

loc_fffaf903:
jne short loc_fffaf910  ; jne 0xfffaf910
mov eax, 1
shl eax, cl
or ebx, eax
jmp short loc_fffaf919  ; jmp 0xfffaf919

loc_fffaf910:
mov eax, 0xfffffffe
rol eax, cl
and ebx, eax

loc_fffaf919:
inc ecx

loc_fffaf91a:
mov dword [ebp - 0x70], ecx
call mrc_sku_type
dec eax
xor edx, edx
cmp eax, 1
mov ecx, dword [ebp - 0x70]
ja short loc_fffaf934  ; ja 0xfffaf934
movzx edx, byte [eax + ref_fffcb9dc]  ; movzx edx, byte [eax - 0x34624]

loc_fffaf934:
cmp ecx, edx
jb short loc_fffaf8e5  ; jb 0xfffaf8e5
mov dword [edi + 0xa00e4], esi
mov dword [edi + 0xa00e8], ebx

loc_fffaf944:
mov eax, dword [ebp - 0x38]
mov edx, dword [ebp - 0x34]
and eax, 0xfffffffd
out dx, ax

loc_fffaf94f:
mov ecx, dword [ebp - 0x30]
test byte [ecx], 2
je short loc_fffaf971  ; je 0xfffaf971
test byte [ecx + 0x55], 1
je short loc_fffaf971  ; je 0xfffaf971
mov edx, dword [ebp - 0x4c]
mov ax, word [edx + 0xe807a]
or ah, 1
mov word [edx + 0xe807a], ax

loc_fffaf971:
cmp dword [ebp - 0x5c], 1
jne short loc_fffaf993  ; jne 0xfffaf993
mov ecx, dword [ebp - 0x30]
test byte [ecx], 4
je short loc_fffaf993  ; je 0xfffaf993
test byte [ecx + 0x56], 1
je short loc_fffaf993  ; je 0xfffaf993
mov edx, dword [ebp - 0x50]
mov ax, word [edx + 0x7a]
or ah, 1
mov word [edx + 0x7a], ax

loc_fffaf993:
mov ecx, dword [ebp - 0x30]
test byte [ecx + 0x57], 3
je short loc_fffaf9b7  ; je 0xfffaf9b7
mov ax, word [edi + 0xa0004]
and eax, 0xfffffff9
mov word [edi + 0xa0004], ax
mov dword [edi + 0xa0010], 0

loc_fffaf9b7:
mov eax, dword [ebp - 0x44]
mov edx, dword [ebp - 0x48]
mov dword [eax + 0x3418], edx
mov ecx, dword [ebp - 0x44]
mov eax, dword [ecx + 0x3418]
jmp short loc_fffafa2f  ; jmp 0xfffafa2f

loc_fffaf9ce:
mov dword [ebp - 0x58], 0x80000002
jmp short loc_fffafa2f  ; jmp 0xfffafa2f

loc_fffaf9e7:
cmp dword [ebp - 0x34], 0
je loc_fffaf44c  ; je 0xfffaf44c
call xhci_setup_ss_route

loc_fffafa2a:
jmp near loc_fffaf44c  ; jmp 0xfffaf44c

loc_fffafa2f:
mov eax, dword [ebp - 0x58]
lea esp, [ebp - 0xc]
pop ebx
pop esi
pop edi
pop ebp
ret

ref_fffcb9dc:
dd 0x00000406

ref_fffcb9e0:
dd ref_fffcc9a8
dd ref_fffcc9e4

ref_fffcb9e8:
dd ref_fffcca08
dd ref_fffcca20

ref_fffcc9a8:
dd 0x00000480
dd 0x00000490
dd 0x000004a0
dd 0x000004b0
dd 0x000004c0
dd 0x000004d0
dd 0x000004e0
dd 0x000004f0
dd 0x00000500
dd 0x00000510
dd 0x00000520
dd 0x00000530
dd 0x00000540
dd 0x00000550
dd 0x00000560

ref_fffcc9e4:
dd 0x00000480
dd 0x00000490
dd 0x000004a0
dd 0x000004b0
dd 0x000004c0
dd 0x000004d0
dd 0x000004e0
dd 0x000004f0
dd 0x00000500

ref_fffcca08:
dd 0x00000570
dd 0x00000580
dd 0x00000590
dd 0x000005a0
dd 0x000005b0
dd 0x000005c0

ref_fffcca20:
dd 0x00000510
dd 0x00000520
dd 0x00000530
dd 0x00000540
