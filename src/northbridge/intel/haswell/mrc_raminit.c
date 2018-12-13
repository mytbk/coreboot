/*
push ebp
xor edx, edx
mov ebp, esp
push edi
push esi
lea edi, [ebp - 0x5ac]
mov esi, ref_fffc9e38  ; mov esi, 0xfffc9e38
push ebx
mov ebx, 0xd
lea esp, [esp - 0x65c]
mov ecx, ebx
mov dword [ebp - 0x63c], eax
mov al, dl
rep stosb  ; rep stosb byte es:[edi], al
mov ebx, ecx
mov ecx, dword [ebp - 0x63c]
lea edi, [ebp - 0x59f]
mov dword [ebp - 0x5dc], 0
mov dword [ebp - 0x5d8], 0
mov dword [ebp - 0x5d4], 0
mov dword [ebp - 0x5d0], fcn_fffa10c8  ; mov dword [ebp - 0x5d0], 0xfffa10c8
mov byte [ebp - 0x60a], 1
mov eax, dword [ecx + 0x1e]
mov ecx, 0xd
mov dword [ebp - 0x609], eax
mov al, dl
rep stosb  ; rep stosb byte es:[edi], al
lea eax, [ebp - 0x59f]
lea edi, [ebp - 0x635]
mov dword [ebp - 0x5c8], eax
mov cl, 3
mov al, dl
mov dword [ebp - 0x5cc], 1
rep stosb  ; rep stosb byte es:[edi], al
lea edi, [ebp - 0x605]
mov cl, 5
rep stosb  ; rep stosb byte es:[edi], al
mov eax, dword [ebp - 0x63c]
lea edi, [ebp - 0x508]
mov byte [ebp - 0x635], 2
mov byte [ebp - 0x633], 1
mov eax, dword [eax + 0x42]
mov dword [ebp - 0x664], eax
mov al, byte [ebp - 0x605]
mov cl, byte [ebp - 0x664]
and eax, 0xfffffffe
and ecx, 1
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x605], al
mov eax, dword [ecx + 0x2e]
mov ecx, 8
mov dword [ebp - 0x604], eax
mov eax, ebx
rep stosd  ; rep stosd dword es:[edi], eax
mov al, dl
lea edi, [ebp - 0x403]
mov cl, 0xc3
rep stosb  ; rep stosb byte es:[edi], al
mov byte [ebp - 0x403], 1
mov eax, dword [ebp - 0x63c]
lea edi, [ebp - 0x632]
mov cl, byte [eax + 0x74]
mov al, byte [ebp - 0x402]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x402], al
mov al, byte [ecx + 0x76]
mov byte [ebp - 0x401], al
mov ax, word [ecx + 0x72]
mov word [ebp - 0x400], ax
mov cl, byte [ecx + 0x79]
mov al, byte [ebp - 0x3fc]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3fc], al
mov al, byte [ecx + 0x7b]
mov byte [ebp - 0x3fb], al
mov ax, word [ecx + 0x77]
mov word [ebp - 0x3fa], ax
mov cl, byte [ecx + 0x7e]
mov al, byte [ebp - 0x3f6]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3f6], al
mov al, byte [ecx + 0x80]
mov byte [ebp - 0x3f5], al
mov ax, word [ecx + 0x7c]
mov word [ebp - 0x3f4], ax
mov cl, byte [ecx + 0x83]
mov al, byte [ebp - 0x3f0]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3f0], al
mov al, byte [ecx + 0x85]
mov byte [ebp - 0x3ef], al
mov ax, word [ecx + 0x81]
mov word [ebp - 0x3ee], ax
mov cl, byte [ecx + 0x88]
mov al, byte [ebp - 0x3ea]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov byte [ebp - 0x3ea], al
mov ecx, dword [ebp - 0x63c]
mov al, byte [ecx + 0x8a]
mov byte [ebp - 0x3e9], al
mov ax, word [ecx + 0x86]
mov word [ebp - 0x3e8], ax
mov cl, byte [ecx + 0x8d]
mov al, byte [ebp - 0x3e4]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3e4], al
mov al, byte [ecx + 0x8f]
mov byte [ebp - 0x3e3], al
mov ax, word [ecx + 0x8b]
mov word [ebp - 0x3e2], ax
mov cl, byte [ecx + 0x92]
mov al, byte [ebp - 0x3de]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3de], al
mov al, byte [ecx + 0x94]
mov byte [ebp - 0x3dd], al
mov ax, word [ecx + 0x90]
mov word [ebp - 0x3dc], ax
mov cl, byte [ecx + 0x97]
mov al, byte [ebp - 0x3d8]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3d8], al
mov al, byte [ecx + 0x99]
mov byte [ebp - 0x3d7], al
mov ax, word [ecx + 0x95]
mov word [ebp - 0x3d6], ax
mov cl, byte [ecx + 0x9c]
mov al, byte [ebp - 0x3d2]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3d2], al
mov al, byte [ecx + 0x9e]
mov byte [ebp - 0x3d1], al
mov ax, word [ecx + 0x9a]
mov word [ebp - 0x3d0], ax
mov cl, byte [ecx + 0xa1]
mov al, byte [ebp - 0x3cc]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3cc], al
mov al, byte [ecx + 0xa3]
mov byte [ebp - 0x3cb], al
mov ax, word [ecx + 0x9f]
mov word [ebp - 0x3ca], ax
mov cl, byte [ecx + 0xa6]
mov al, byte [ebp - 0x3c6]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3c6], al
mov al, byte [ecx + 0xa8]
mov byte [ebp - 0x3c5], al
mov ax, word [ecx + 0xa4]
mov word [ebp - 0x3c4], ax
mov cl, byte [ecx + 0xab]
mov al, byte [ebp - 0x3c0]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3c0], al
mov al, byte [ecx + 0xad]
mov byte [ebp - 0x3bf], al
mov ax, word [ecx + 0xa9]
mov word [ebp - 0x3be], ax
mov cl, byte [ecx + 0xb0]
mov al, byte [ebp - 0x3ba]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3ba], al
mov al, byte [ecx + 0xb2]
mov byte [ebp - 0x3b9], al
mov ax, word [ecx + 0xae]
mov word [ebp - 0x3b8], ax
mov al, byte [ebp - 0x3b4]
mov cl, byte [ecx + 0xb5]
and eax, 0xfffffffe
and ecx, 1
or byte [ebp - 0x3ae], 1
or eax, ecx
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x3b4], al
or byte [ebp - 0x3ad], 1
mov al, byte [ecx + 0xb7]
mov byte [ebp - 0x3b3], al
mov ax, word [ecx + 0xb3]
mov word [ebp - 0x3b2], ax
mov al, byte [ebp - 0x3ac]
and eax, 0xfffffffc
or eax, 2
mov byte [ebp - 0x3ac], al
  movzx eax, byte [ecx + 0x75] // usb2[0].oc
mov dword [ebp - 0x397], eax
  movzx eax, byte [ecx + 0x7a] // usb2[1].oc
mov dword [ebp - 0x393], eax
  movzx eax, byte [ecx + 0x7f] // usb2[2].oc
mov dword [ebp - 0x38f], eax
  movzx eax, byte [ecx + 0x84] // usb2[3].oc
mov dword [ebp - 0x38b], eax
  movzx eax, byte [ecx + 0x89] // usb2[4].oc
mov dword [ebp - 0x387], eax
  movzx eax, byte [ecx + 0x8e] // usb2[5].oc
mov dword [ebp - 0x383], eax
movzx eax, byte [ecx + 0x93] [6].oc
mov dword [ebp - 0x37f], eax
movzx eax, byte [ecx + 0x98] [7].oc
mov dword [ebp - 0x37b], eax
movzx eax, byte [ecx + 0x9d] [8].oc
mov dword [ebp - 0x377], eax
movzx eax, byte [ecx + 0xa2] [9].oc
mov dword [ebp - 0x373], eax
movzx eax, byte [ecx + 0xa7] [10].oc
mov dword [ebp - 0x36f], eax
movzx eax, byte [ecx + 0xac] [11].oc
mov dword [ebp - 0x36b], eax
movzx eax, byte [ecx + 0xb1] [12].oc
mov dword [ebp - 0x367], eax
movzx eax, byte [ecx + 0xb6] [13].oc
mov dword [ebp - 0x363], eax
movzx eax, byte [ecx + 0xc3]
mov dword [ebp - 0x35f], eax
movzx eax, byte [ecx + 0xc5]
mov dword [ebp - 0x35b], eax
movzx eax, byte [ecx + 0xc7]
mov dword [ebp - 0x357], eax
movzx eax, byte [ecx + 0xc9]
mov dword [ebp - 0x353], eax
movzx eax, byte [ecx + 0xcb]
mov dword [ebp - 0x34f], eax
movzx eax, byte [ecx + 0xcd]
mov cl, byte [ecx + 0xc2]
mov dword [ebp - 0x34b], eax
mov al, byte [ebp - 0x346]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov byte [ebp - 0x346], al
mov eax, dword [ebp - 0x63c]
mov cl, byte [eax + 0xc4]
mov al, byte [ebp - 0x345]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov byte [ebp - 0x345], al
mov eax, dword [ebp - 0x63c]
mov cl, byte [eax + 0xc6]
mov al, byte [ebp - 0x344]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov byte [ebp - 0x344], al
mov eax, dword [ebp - 0x63c]
mov cl, byte [eax + 0xc8]
mov al, byte [ebp - 0x343]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov byte [ebp - 0x343], al
mov eax, dword [ebp - 0x63c]
mov byte [ebp - 0x4c0], 3
mov byte [ebp - 0x4bf], 0
mov dword [ebp - 0x4aa], 0
mov byte [ebp - 0x565], 4
mov cl, byte [eax + 0xca]
mov al, byte [ebp - 0x342]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov byte [ebp - 0x342], al
mov eax, dword [ebp - 0x63c]
mov cl, byte [eax + 0xcc]
mov al, byte [ebp - 0x341]
and ecx, 1
and eax, 0xfffffffe
or eax, ecx
mov ecx, 3
mov byte [ebp - 0x341], al
mov eax, dword [ebp - 0x63c]
cmp dword [eax + 0x46], 0
mov al, dl
rep stosb  ; rep stosb byte es:[edi], al
mov ecx, dword [ebp - 0x63c]
lea eax, [ebp - 0x632]
mov dword [ebp - 0x61a], eax
lea edi, [ebp - 0x585]
setne byte [ebp - 0x636]
mov eax, dword [ecx + 0x22]
mov dword [ebp - 0x4be], eax
mov eax, dword [ecx + 0x26]
mov word [ebp - 0x4ba], ax
mov eax, dword [ecx + 0x2a]
mov word [ebp - 0x4b8], ax
mov ecx, 4
lea eax, [ebp - 0x636]
mov dword [ebp - 0x4b6], eax
lea eax, [ebp - 0x61a]
mov dword [ebp - 0x4b2], eax
lea eax, [ebp - 0x60a]
mov dword [ebp - 0x4ae], eax
lea eax, [ebp - 0x5cc]
mov dword [ebp - 0x4a6], eax
lea eax, [ebp - 0x508]
mov dword [ebp - 0x4a2], eax
lea eax, [ebp - 0x635]
mov dword [ebp - 0x49e], eax
lea eax, [ebp - 0x605]
mov dword [ebp - 0x49a], eax
lea eax, [ebp - 0x403]
mov dword [ebp - 0x496], eax
mov dword [ebp - 0x564], eax
mov byte [ebp - 0x560], 1
rep movsd  ; rep movsd dword es:[edi], dword ptr [esi]
mov esi, ref_fffc9e48  ; mov esi, 0xfffc9e48
lea edi, [ebp - 0x4e8]
mov cl, 0xa
mov al, dl
rep movsd  ; rep movsd dword es:[edi], dword ptr [esi]
lea edi, [ebp - 0x592]
mov cl, 0xd
rep stosb  ; rep stosb byte es:[edi], al
mov eax, ebx
lea edi, [ebp - 0x340]
mov cl, 0x32
mov dword [ebp - 0x55f], 0xe8000000
rep stosd  ; rep stosd dword es:[edi], eax
mov ecx, dword [ebp - 0x63c]
mov dword [ebp - 0x55b], 0x800
mov dword [ebp - 0x557], 0xe8100000
mov word [ebp - 0x592], 0x800
mov word [ebp - 0x590], 2
mov byte [ebp - 0x58e], 1
mov byte [ebp - 0x58d], 2
mov byte [ebp - 0x58c], 3
mov eax, dword [ecx + 0x4a]
mov byte [ebp - 0x58b], 2
mov byte [ebp - 0x316], al
mov eax, dword [ecx + 0x4e]
mov byte [ebp - 0x315], al
mov byte [ebp - 0x340], 1
mov byte [ebp - 0x33d], 1
mov byte [ebp - 0x32f], 1
mov byte [ebp - 0x31c], 1
mov byte [ebp - 0x314], 1
mov byte [ebp - 0x312], 1
mov byte [ebp - 0x311], 1
mov byte [ebp - 0x310], 4
mov byte [ebp - 0x30f], 0xc
mov byte [ebp - 0x30d], 1
mov byte [ebp - 0x30c], 1
mov byte [ebp - 0x30b], 1
mov byte [ebp - 0x30a], 1
mov byte [ebp - 0x308], 1
mov eax, dword [ecx + 0x56]
mov byte [ebp - 0x2e9], al
mov eax, dword [ecx + 0x52]
mov byte [ebp - 0x2d4], al
mov byte [ebp - 0x2ca], al
lea edi, [ebp - 0x463]
mov eax, ebx
mov ecx, 0x18
mov byte [ebp - 0x307], 1
mov byte [ebp - 0x306], 1
mov byte [ebp - 0x304], 1
mov byte [ebp - 0x302], 1
mov byte [ebp - 0x300], 1
mov byte [ebp - 0x2ff], 1
mov byte [ebp - 0x2fe], 1
mov byte [ebp - 0x2fd], 1
mov byte [ebp - 0x2fc], 1
mov byte [ebp - 0x2f9], 1
mov byte [ebp - 0x2f8], 1
mov byte [ebp - 0x2f7], 1
mov byte [ebp - 0x2ea], 1
mov byte [ebp - 0x2e6], 1
mov byte [ebp - 0x2e4], 1
mov byte [ebp - 0x2e3], 6
mov byte [ebp - 0x2e2], 0x40
mov byte [ebp - 0x2e1], 1
mov byte [ebp - 0x2e0], 1
mov byte [ebp - 0x2de], 7
mov dword [ebp - 0x2dc], 0x5f5e100
mov byte [ebp - 0x2d6], 1
mov byte [ebp - 0x2d3], 1
mov word [ebp - 0x2d2], 0x30ce
mov byte [ebp - 0x2d0], 1
mov byte [ebp - 0x2cc], 1
mov byte [ebp - 0x2c9], 1
mov byte [ebp - 0x2c6], 3
mov byte [ebp - 0x2b8], 0xff
rep stosd  ; rep stosd dword es:[edi], eax
mov al, dl
lea edi, [ebp - 0x492]
mov cl, 0x2f
mov byte [ebp - 0x2b7], 0xff
rep stosb  ; rep stosb byte es:[edi], al
mov ecx, dword [ebp - 0x63c]
mov byte [ebp - 0x2b6], 0xff
mov byte [ebp - 0x2b5], 0xff
mov byte [ebp - 0x2b4], 0xff
mov byte [ebp - 0x2b3], 0xff
mov byte [ebp - 0x2b2], 0xff
mov byte [ebp - 0x2b1], 0xff
mov byte [ebp - 0x2b0], 0xff
mov al, byte [ecx + 0x3a]
mov byte [ebp - 0x2af], 0xff
mov byte [ebp - 0x492], al
mov al, byte [ecx + 0x3b]
mov byte [ebp - 0x491], al
mov al, byte [ecx + 0x3c]
mov byte [ebp - 0x2ae], 0xff
mov byte [ebp - 0x2ad], 0xff
mov byte [ebp - 0x2ac], 0xff
mov byte [ebp - 0x2ab], 0xff
mov byte [ebp - 0x2aa], 0xff
mov byte [ebp - 0x2a9], 0xff
mov byte [ebp - 0x294], 1
mov word [ebp - 0x293], 0x200
mov byte [ebp - 0x290], 0x30
mov byte [ebp - 0x28f], 1
mov byte [ebp - 0x28e], 0x40
mov byte [ebp - 0x27e], 1
mov byte [ebp - 0x27d], 1
mov byte [ebp - 0x27b], 1
mov byte [ebp - 0x462], 1
mov byte [ebp - 0x461], 1
mov byte [ebp - 0x460], 1
mov byte [ebp - 0x490], al
mov al, byte [ecx + 0x3d]
lea edi, [ebp - 0x575]
mov byte [ebp - 0x48f], al
mov eax, dword [ecx + 4]
mov dword [ebp - 0x48e], eax
mov eax, dword [ecx + 8]
mov dword [ebp - 0x48a], eax
mov eax, dword [ecx + 0xc]
mov dword [ebp - 0x486], eax
mov eax, dword [ecx + 0x10]
mov dword [ebp - 0x482], eax
mov esi, ref_fffc9e70  ; mov esi, 0xfffc9e70
movzx eax, word [ecx + 0x14]
mov dword [ebp - 0x47a], 0xfed84000
mov dword [ebp - 0x47e], eax
mov eax, dword [ecx + 0x36]
mov dword [ebp - 0x476], eax
mov eax, dword [ecx + 0x32]
mov byte [ebp - 0x472], al
mov ecx, 4
mov eax, ebx
mov byte [ebp - 0x471], 1
rep stosd  ; rep stosd dword es:[edi], eax
mov al, dl
lea edi, [ebp - 0x526]
mov cl, 0x1e
mov dword [ebp - 0x470], 0xfed80000
rep stosb  ; rep stosb byte es:[edi], al
mov ecx, dword [ebp - 0x63c]
lea eax, [ebp - 0x492]
lea edi, [ebp - 0x53e]
mov dword [ebp - 0x525], eax
lea eax, [ebp - 0x592]
mov dword [ebp - 0x521], eax
lea eax, [ebp - 0x340]
mov dword [ebp - 0x51d], eax
lea eax, [ebp - 0x463]
mov dword [ebp - 0x519], eax
lea eax, [ebp - 0x575]
mov dword [ebp - 0x515], eax
mov eax, dword [ecx + 0x5a]
mov ecx, 6
rep movsd  ; rep movsd dword es:[edi], dword ptr [esi]
mov dword [ebp - 0x511], eax
lea edi, [ebp - 0x600]
mov al, dl
mov cl, 5
mov dword [ebp - 0x467], 0x400000
mov byte [ebp - 0x526], 0xe
mov dword [ebp - 0x616], fcn_fffa049e  ; mov dword [ebp - 0x616], 0xfffa049e
mov dword [ebp - 0x612], fcn_fffa04c9  ; mov dword [ebp - 0x612], 0xfffa04c9
rep stosb  ; rep stosb byte es:[edi], al
lea edi, [ebp - 0x553]
mov cl, 0x15
rep stosb  ; rep stosb byte es:[edi], al
lea eax, [ebp - 0x600]
lea edi, [ebp - 0x62f]
mov dword [ebp - 0x552], eax
mov cl, 3
mov al, dl
mov edx, dword [ebp - 0x63c]
rep stosb  ; rep stosb byte es:[edi], al
mov eax, ebx
lea edi, [ebp - 0x278]
mov cl, 0x98
mov dword [ebp - 0x60e], fcn_fffa04e0  ; mov dword [ebp - 0x60e], 0xfffa04e0
rep stosd  ; rep stosd dword es:[edi], eax
mov eax, dword [edx + 0x3e]
mov byte [ebp - 0x553], 1
mov dword [ebp - 0x20c], eax
mov byte [ebp - 0x62f], 1
lea eax, [ebp - 0x5d4]
mov dword [ebp - 0x278], 0xfeadb00b
mov dword [ebp - 0x200], eax
mov dword [ebp - 0x25c], fcn_fffa2b02  ; mov dword [ebp - 0x25c], 0xfffa2b02
lea eax, [ebp - 0x526]
mov dword [ebp - 0x254], fcn_fffa2a76  ; mov dword [ebp - 0x254], 0xfffa2a76
mov dword [ebp - 0x1f4], eax
mov dword [ebp - 0x250], fcn_fffa043e  ; mov dword [ebp - 0x250], 0xfffa043e
lea eax, [ebp - 0x5dc]
mov dword [ebp - 0x24c], fcn_fffa041f  ; mov dword [ebp - 0x24c], 0xfffa041f
mov dword [ebp - 0x1e8], eax
mov dword [ebp - 0x244], fcn_fffa03fd  ; mov dword [ebp - 0x244], 0xfffa03fd
lea eax, [ebp - 0x4c0]
mov dword [ebp - 0x240], fcn_fffa29ba  ; mov dword [ebp - 0x240], 0xfffa29ba
mov dword [ebp - 0x1dc], eax
mov dword [ebp - 0x230], fcn_fffa04e7  ; mov dword [ebp - 0x230], 0xfffa04e7
lea eax, [ebp - 0x565]
mov dword [ebp - 0x224], memcpy  ; mov dword [ebp - 0x224], 0xfffa1178
mov dword [ebp - 0x1d0], eax
mov dword [ebp - 0x21c], fcn_fffa04ee  ; mov dword [ebp - 0x21c], 0xfffa04ee
lea eax, [ebp - 0x585]
mov dword [ebp - 0x214], ref_fffcc83c  ; mov dword [ebp - 0x214], 0xfffcc83c
mov dword [ebp - 0x204], ref_fffcd4b4  ; mov dword [ebp - 0x204], 0xfffcd4b4
mov dword [ebp - 0x1f8], ref_fffcd4e4  ; mov dword [ebp - 0x1f8], 0xfffcd4e4
mov dword [ebp - 0x1ec], ref_fffcd4d4  ; mov dword [ebp - 0x1ec], 0xfffcd4d4
mov dword [ebp - 0x1e0], ref_fffcca3c  ; mov dword [ebp - 0x1e0], 0xfffcca3c
mov dword [ebp - 0x1d4], ref_fffcc988  ; mov dword [ebp - 0x1d4], 0xfffcc988
mov dword [ebp - 0x1c8], ref_fffcc96c  ; mov dword [ebp - 0x1c8], 0xfffcc96c
mov dword [ebp - 0x1c4], eax
lea eax, [ebp - 0x53e]
mov dword [ebp - 0x1b8], eax
lea eax, [ebp - 0x4e8]
mov dword [ebp - 0x1ac], eax
lea eax, [ebp - 0x5ac]
mov dword [ebp - 0x1a0], eax
lea eax, [ebp - 0x616]
mov dword [ebp - 0x194], eax
lea eax, [ebp - 0x612]
mov dword [ebp - 0x188], eax
lea eax, [ebp - 0x60e]
mov dword [ebp - 0x17c], eax
lea eax, [ebp - 0x553]
mov dword [ebp - 0x170], eax
lea eax, [ebp - 0x62f]
mov dword [ebp - 0x164], eax
lea eax, [ebp - 0x274]
mov dword [ebp - 0x62c], eax
mov dword [ebp - 0x1bc], ref_fffcd488  ; mov dword [ebp - 0x1bc], 0xfffcd488
mov dword [ebp - 0x1b0], ref_fffcd534  ; mov dword [ebp - 0x1b0], 0xfffcd534
mov dword [ebp - 0x1a4], ref_fffcd524  ; mov dword [ebp - 0x1a4], 0xfffcd524
mov dword [ebp - 0x198], ref_fffcc88c  ; mov dword [ebp - 0x198], 0xfffcc88c
mov dword [ebp - 0x18c], ref_fffcc89c  ; mov dword [ebp - 0x18c], 0xfffcc89c
mov dword [ebp - 0x180], ref_fffcc8ac  ; mov dword [ebp - 0x180], 0xfffcc8ac
mov dword [ebp - 0x174], ref_fffcc8bc  ; mov dword [ebp - 0x174], 0xfffcc8bc
mov dword [ebp - 0x168], ref_fffcc8cc  ; mov dword [ebp - 0x168], 0xfffcc8cc
mov dword [ebp - 0x118], 0xe
mov dword [ebp - 0x1c], edx
mov eax, dword [edx + 0x4e2]
mov dword [0xff7d753c], eax
cmp dword [edx], 0xf
mov dword [ebp - 0x1bc], ref_fffcd488  ; mov dword [ebp - 0x1bc], 0xfffcd488
mov dword [ebp - 0x1b0], ref_fffcd534  ; mov dword [ebp - 0x1b0], 0xfffcd534
mov dword [ebp - 0x1a4], ref_fffcd524  ; mov dword [ebp - 0x1a4], 0xfffcd524
mov dword [ebp - 0x198], ref_fffcc88c  ; mov dword [ebp - 0x198], 0xfffcc88c
mov dword [ebp - 0x18c], ref_fffcc89c  ; mov dword [ebp - 0x18c], 0xfffcc89c
mov dword [ebp - 0x180], ref_fffcc8ac  ; mov dword [ebp - 0x180], 0xfffcc8ac
mov dword [ebp - 0x174], ref_fffcc8bc  ; mov dword [ebp - 0x174], 0xfffcc8bc
mov dword [ebp - 0x168], ref_fffcc8cc  ; mov dword [ebp - 0x168], 0xfffcc8cc
mov dword [ebp - 0x118], 0xe
mov dword [ebp - 0x1c], edx
jne loc_fffa559c  ; jne 0xfffa559c
sub esp, 0xc
lea eax, [ebp - 0x62c]
push ref_fffcc534  ; push 0xfffcc534
mov dword [0xff7d7538], eax
call mrc_printk  ; call 0xfffa1253
add esp, 0x10
cmp dword [ebp - 0x20c], 2
jne short loc_fffa39a6  ; jne 0xfffa39a6
mov eax, dword [ebp - 0x63c]
cmp dword [eax + 0x5a], 0
je short loc_fffa39a6  ; je 0xfffa39a6
sub esp, 0xc
mov dword [ebp - 0x20c], 0x11
push ref_fffcc552  ; push 0xfffcc552
call mrc_printk  ; call 0xfffa1253
mov eax, dword [ebp - 0x63c]
add esp, 0x10
cmp dword [eax + 0x6e], 0
je short loc_fffa39a6  ; je 0xfffa39a6
mov al, byte [ebp - 0x3ac]
and byte [ebp - 0x3ae], 0xfe
and eax, 0xfffffffc
and byte [ebp - 0x3ad], 0xfe
or eax, 5
mov byte [ebp - 0x3ac], al

loc_fffa39a6:
mov edx, dword [ebp - 0x63c]
mov eax, dword [edx + 0x6a]
cmp eax, 0x42b
je short loc_fffa39dc  ; je 0xfffa39dc
ja short loc_fffa39c1  ; ja 0xfffa39c1
cmp eax, 0x320
jne short loc_fffa39fd  ; jne 0xfffa39fd
jmp short loc_fffa39d1  ; jmp 0xfffa39d1

loc_fffa39c1:
cmp eax, 0x535
je short loc_fffa39e7  ; je 0xfffa39e7
cmp eax, 0x640
jne short loc_fffa39fd  ; jne 0xfffa39fd
jmp short loc_fffa39f2  ; jmp 0xfffa39f2

loc_fffa39d1:
mov word [ebp - 0x33f], 0x320
jmp short loc_fffa3a17  ; jmp 0xfffa3a17

loc_fffa39dc:
mov word [ebp - 0x33f], 0x42b
jmp short loc_fffa3a17  ; jmp 0xfffa3a17

loc_fffa39e7:
mov word [ebp - 0x33f], 0x535
jmp short loc_fffa3a17  ; jmp 0xfffa3a17

loc_fffa39f2:
mov word [ebp - 0x33f], 0x640
jmp short loc_fffa3a17  ; jmp 0xfffa3a17

loc_fffa39fd:
push edx
push edx
push eax
push ref_fffcc574  ; push 0xfffcc574
call mrc_printk  ; call 0xfffa1253
add esp, 0x10
mov eax, 0xfffffffe
jmp near loc_fffa56a4  ; jmp 0xfffa56a4

loc_fffa3a17:
call fcn_fffc5ca7  ; call 0xfffc5ca7
mov edx, dword [0xf0000060]
and edx, 0xfc000000
cmp eax, 1
mov dx, word [edx + 0xf8002]
jne loc_fffa3bb5
mov eax, edx
and eax, 0xfffffffd
cmp ax, 0x8c44
je short loc_fffa3aa7  ; je 0xfffa3aa7
cmp ax, 0x8c4c
je short loc_fffa3aa7  ; je 0xfffa3aa7
cmp dx, 0x8c5c
sete cl
cmp dx, 0x8c50
sete al
or cl, al
jne short loc_fffa3aa7  ; jne 0xfffa3aa7
mov eax, edx
and eax, 0xfffffff7
cmp ax, 0x8c42
je short loc_fffa3aa7  ; je 0xfffa3aa7
jmp near loc_fffa3b14  ; jmp 0xfffa3b14

loc_fffa3a6d:
imul eax, ebx, 6
lea eax, [ebp + eax - 0x402]
cmp byte [eax + 1], 0
jne short loc_fffa3a8d  ; jne 0xfffa3a8d
mov dx, word [eax + 2]
mov byte [eax + 4], 4
cmp dx, 0x7f
jbe short loc_fffa3a91  ; jbe 0xfffa3a91
jmp short loc_fffa3a97  ; jmp 0xfffa3a97

loc_fffa3a8d:
mov byte [eax + 4], 3

loc_fffa3a91:
mov byte [eax + 5], 2
jmp short loc_fffa3aa4  ; jmp 0xfffa3aa4

loc_fffa3a97:
cmp dx, 0x130
sbb edx, edx
add edx, 4
mov byte [eax + 5], dl

loc_fffa3aa4:
inc ebx
jmp short loc_fffa3aa9  ; jmp 0xfffa3aa9

loc_fffa3aa7:
xor ebx, ebx

loc_fffa3aa9:
call fcn_fffc5d89  ; call 0xfffc5d89
movzx eax, al
cmp ebx, eax
jl short loc_fffa3a6d

loc_fffa3ab5:
sub esp, 0xc
push ref_fffcc5c7  ; push 0xfffcc5c7
call mrc_printk  ; call 0xfffa1253
mov eax, dword [0xf0000060]
mov ebx, dword [0xff7d7538]
and eax, 0xfc000000
mov edx, dword [eax + 0xf80f0]
and edx, 0xfffffffe
mov word [edx + 0x3424], 0x10
mov eax, dword [edx + 0x3428]
or eax, 1
mov dword [edx + 0x3428], eax
mov eax, dword [0xf0000060]
add esp, 0x10
and eax, 0xfc000000
mov ax, word [eax + 0xf80a4]
test al, 4
je loc_fffa3c99
jmp near loc_fffa3c2e

loc_fffa3b14:
cmp dx, 0x8c4f
sete cl
cmp dx, 0x8c49
sete al
or cl, al
jne short loc_fffa3ba2  ; jne 0xfffa3ba2
cmp dx, 0x8c41
sete cl
cmp dx, 0x8c4b
sete al
or cl, al
jne short loc_fffa3ba2  ; jne 0xfffa3ba2
add dx, 0x63bf
xor ebx, ebx
cmp dx, 6
jbe short loc_fffa3ba4  ; jbe 0xfffa3ba4
jmp near loc_fffa3ab5

loc_fffa3b4e:
imul eax, ebx, 6
lea eax, [ebp + eax - 0x402]
mov dl, byte [eax + 1]
cmp dl, 5
jne short loc_fffa3b62  ; jne 0xfffa3b62
jmp short loc_fffa3b84  ; jmp 0xfffa3b84

loc_fffa3b62:
cmp dl, 2
jne short loc_fffa3b7a  ; jne 0xfffa3b7a
cmp word [eax + 2], 0x50
mov byte [eax + 4], 4
sbb edx, edx
add edx, 2
mov byte [eax + 5], dl
jmp short loc_fffa3b9f  ; jmp 0xfffa3b9f

loc_fffa3b7a:
mov dx, word [eax + 2]
cmp dx, 0x6f
ja short loc_fffa3b8a  ; ja 0xfffa3b8a

loc_fffa3b84:
mov byte [eax + 4], 5
jmp short loc_fffa3b95  ; jmp 0xfffa3b95

loc_fffa3b8a:
cmp dx, 0xff
mov byte [eax + 4], 6
ja short loc_fffa3b9b  ; ja 0xfffa3b9b

loc_fffa3b95:
mov byte [eax + 5], 2
jmp short loc_fffa3b9f  ; jmp 0xfffa3b9f

loc_fffa3b9b:
mov byte [eax + 5], 3

loc_fffa3b9f:
inc ebx
jmp short loc_fffa3ba4  ; jmp 0xfffa3ba4

loc_fffa3ba2:
xor ebx, ebx

loc_fffa3ba4:
call fcn_fffc5d89  ; call 0xfffc5d89
movzx eax, al
cmp ebx, eax
jl short loc_fffa3b4e
jmp near loc_fffa3ab5

loc_fffa3bb5:
cmp eax, 2
jne loc_fffa3ab5
jmp short loc_fffa3c1b  ; jmp 0xfffa3c1b

loc_fffa3bc0:
imul eax, ebx, 6
lea esi, [ebp + eax - 0x402]
mov al, byte [esi + 1]
cmp al, 3
sete cl
test al, al
sete dl
or cl, dl
je short loc_fffa3bf3
mov ax, word [esi + 2]
cmp ax, 0x6f
ja short loc_fffa3be7
jmp short loc_fffa3c0a

loc_fffa3be7:
cmp ax, 0xff
mov byte [esi + 4], 6
ja short loc_fffa3c14  ; ja 0xfffa3c14
jmp short loc_fffa3c0e  ; jmp 0xfffa3c0e

loc_fffa3bf3:
cmp al, 2
jne short loc_fffa3c0a  ; jne 0xfffa3c0a
cmp word [esi + 2], 0x50
mov byte [esi + 4], 4
sbb eax, eax
add eax, 2
mov byte [esi + 5], al
jmp short loc_fffa3c18

loc_fffa3c0a:
mov byte [esi + 4], 5

loc_fffa3c0e:
mov byte [esi + 5], 2
jmp short loc_fffa3c18  ; jmp 0xfffa3c18

loc_fffa3c14:
mov byte [esi + 5], 3

loc_fffa3c18:
inc ebx
jmp short loc_fffa3c1d  ; jmp 0xfffa3c1d

loc_fffa3c1b:
xor ebx, ebx

loc_fffa3c1d:
call fcn_fffc5d89  ; call 0xfffc5d89
movzx eax, al
cmp ebx, eax
jl short loc_fffa3bc0  ; jl 0xfffa3bc0
jmp near loc_fffa3ab5

loc_fffa3c2e:
mov eax, dword [edx + 0x3410]
or eax, 0x10
mov dword [edx + 0x3410], eax
mov eax, dword [edx + 0x3410]
in al, 0x70
mov esi, eax
mov eax, dword [edx + 0x3410]
and eax, 0xffffffef
and esi, 0xffffff80
mov dword [edx + 0x3410], eax
mov ecx, esi
mov eax, dword [edx + 0x3410]
or ecx, 0xa
mov al, cl
out 0x70, al
in al, 0x71
and eax, 0xffffff8f
or eax, 0x60
out 0x71, al
or esi, 0xb
mov eax, esi
out 0x70, al
in al, 0x71
or eax, 0xffffff80
out 0x71, al
mov al, cl
out 0x70, al
in al, 0x71
and eax, 0xffffff8f
or eax, 0x20
out 0x71, al
mov eax, esi
out 0x70, al
in al, 0x71
and eax, 0x7f
out 0x71, al

loc_fffa3c99:
mov dword [edx + 0x3310], 0x10
mov eax, ebx
call fcn_fffc7c9d  ; call 0xfffc7c9d
mov eax, 0xc
call mrc_alloc
test eax, eax
mov esi, eax
je short loc_fffa3d32  ; je 0xfffa3d32
mov edx, 0xc
call mrc_zeromem
mov eax, 0x28
call mrc_alloc
test eax, eax
mov edi, eax
je short loc_fffa3d32  ; je 0xfffa3d32
mov edx, 0x28
call mrc_zeromem
mov ecx, 0x28
mov edx, ref_fffcc8dc  ; mov edx, 0xfffcc8dc
mov eax, edi
call mrc_memcpy
mov dword [esi + 8], edi
mov dword [esi], 0x80000010
mov dword [esi + 4], ref_fffcd534  ; mov dword [esi + 4], 0xfffcd534
push edi
push edi
mov eax, dword [ebx]
push esi
push ebx
call dword [eax + 0x18]  ; ucall
pop eax
pop edx
mov eax, dword [ebx]
push ref_fffcc97c  ; push 0xfffcc97c
push ebx
call dword [eax + 0x18]  ; ucall
pop ecx
pop esi
mov eax, dword [ebx]
push ref_fffcca30  ; push 0xfffcca30
push ebx
call dword [eax + 0x24]  ; ucall
pop edi
pop eax
mov eax, dword [ebx]
push ref_fffcd560  ; push 0xfffcd560
push ebx
call dword [eax + 0x24]  ; ucall
add esp, 0x10

loc_fffa3d32:
push ecx
push 0
push 0
push dword [0xff7d7538]
call fcn_fffb9720  ; call 0xfffb9720
mov dword [esp], ref_fffcc5e7  ; 'System Agent: Initializing PCH (SMBUS)',0x0a,0x00
call mrc_printk  ; call 0xfffa1253
*/
ref_fffc9e38:
dd fcn_fffaea18
dd fcn_fffc5978
dd fcn_fffc5d49
dd fcn_fffc7bc0

struct usb2_port_setting {
	uint16_t length;
	uint8_t enable;
	uint8_t over_current_pin;
	uint8_t location;
} __packed;

struct usb3_port_setting {
	uint8_t enable;
	uint8_t over_current_pin;
} __packed;

struct pei_data
{
  uint32_t pei_version; // 0
  uint32_t mchbar; // 4
  uint32_t dmibar; // 8
  uint32_t epbar; // c
  uint32_t pciexbar; // 0x10
  uint16_t smbusbar; // 0x14
  uint32_t wdbbar; // 0x16
  uint32_t wdbsize; // 0x1a
  uint32_t hpet_address; // 0x1e
  uint32_t rcba; // 0x22
  uint32_t pmbase; // 0x26
  uint32_t gpiobase; // 0x2a
  uint32_t temp_mmio_base; // 0x2e
  uint32_t system_type; // 0x32, 0 Mobile, 1 Desktop/Server
  uint32_t tseg_size; // 0x36
  uint8_t spd_addresses[4]; // 0x3a
  int boot_mode; // 0x3e
  int ec_present; // 0x42
  int gbe_enable; // 0x46
  // 0 = leave channel enabled
  // 1 = disable dimm 0 on channel
  // 2 = disable dimm 1 on channel
  // 3 = disable dimm 0+1 on channel
  int dimm_channel0_disabled; // 0x4a
  int dimm_channel1_disabled; // 0x4e
  /* Enable 2x Refresh Mode */
  int ddr_refresh_2x; // 0x52
  int dq_pins_interleaved; // 0x56
  /* Data read from flash and passed into MRC */
  unsigned char *mrc_input; // 0x5a
  unsigned int mrc_input_len; // 0x5e
  /* Data from MRC that should be saved to flash */
  unsigned char *mrc_output; // 0x62
  unsigned int mrc_output_len; // 0x66
  /*
   * Max frequency DDR3 could be ran at. Could be one of four values: 800,
   * 1067, 1333, 1600
   */
  uint32_t max_ddr3_freq; // 0x6a
  /* Route all USB ports to XHCI controller in resume path */
  int usb_xhci_on_resume; // 0x6e

  // 0x72, 0x77, 0x7c, 0x81, 0x86, 0x8b, 0x90, 0x95
  // 0x9a, 0x9f, 0xa4, 0xa9, 0xae, 0xb3, 0xb8, 0xbd
  struct usb2_port_setting usb2_ports[MAX_USB2_PORTS];

  // 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0
  // 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde, 0xe0
  struct usb3_port_setting usb3_ports[MAX_USB3_PORTS];
  
  uint8_t spd_data[4][256]; // 0xe2, 0x1e2, 0x2e2, 0x3e2
  tx_byte_func tx_byte; // 0x4e2
} __packed;

struct usb2_setting
{
  uint8_t en;
  uint8_t location;
  uint16_t length;
  uint8_t f4;
  uint8_t f5;
};

static *PeiCore; // 0xff7d7538
int __attribute((regparm(1))) do_raminit(struct pei_data *pd)
{
  struct pei_data *pei; // ebp - 0x63c
  edx = 0;
  edi = ebp - 0x5ac;
  esi = ref_fffc9e38;
  ebx = 13;
  ecx = ebx;
  [ebp - 0x63c] = pd;
  zeromem(edi, 13);
  ebx = 0;
  ecx = pei;
  edi = ebp - 0x59f;
  [ebp - 0x5dc] = [ebp - 0x5d8] = [ebp - 0x5d4] = 0;
  [ebp - 0x5d0] = fcn_fffa10c8;
  byte [ebp - 0x60a] = 1;
  eax = pei->hpet_address;
  ecx = 13;
  [ebp - 0x609] = eax;
  zeromem(edi, 13);
  eax = ebp - 0x59f;
  edi = ebp - 0x635;
  [ebp - 0x5c8] = eax;
  cl = 3;
  [ebp - 0x5cc] = 1;
  zeromem(edi, 3);
  edi = ebp - 0x605;
  zeromem(edi, 5);
  eax = pei;
  edi = ebp - 0x508;
  byte [ebp - 0x635] = 2;
  byte [ebp - 0x633] = 1;
  [ebp - 0x664] = pei->ec_present;
  eax = byte [ebp - 0x605] & 0xfffffffe;
  ecx = byte [ebp - 0x664] & 1;
  eax |= ecx;
  ecx = pei;
  byte [ebp - 0x605] = eax;
  ecx = 8;
  [ebp - 0x604] = pei->temp_mmio_base;
  eax = ebx;
  while (ecx--) *edi++ = eax;
  al = 0;
  edi = ebp - 0x403;
  zeromem(edi, 0xc3);
  byte [ebp - 0x403] = 1;
  eax = pei;
  edi = ebp - 0x632;
  
  ecx = pei->usb2_ports[0].enable & 1;
  eax = byte [ebp - 0x402] & 0xfffffffe;
  eax |= ecx;
  byte [ebp - 0x402] = al;
  byte [ebp - 0x401] = pei->usb2_ports[0].location;
  word [ebp - 0x400] = pei->usb2_ports[0].length;
  
  ecx = pei->usb2_ports[1].enable & 1;
  eax = byte [ebp - 0x3fc] & 0xfffffffe;
  eax |= ecx;
  byte [ebp - 0x3fc] = al;
  byte [ebp - 0x3fb] = pei->usb2_ports[1].location;
  word [ebp - 0x3fa] = pei->usb2_ports[1].length;

  /* usb2 [2] */
  [ebp - 0x3f6];
  [ebp - 0x3f5];
  [ebp - 0x3f4];

  /* usb2 [3] */
  [ebp - 0x3f0];
  [ebp - 0x3ef];
  [ebp - 0x3ee];

  /* usb2 [4] */
  [ebp - 0x3ea];
  [ebp - 0x3e9];
  [ebp - 0x3e8];

  /* usb2 [5] */
  [ebp - 0x3e4];
  [ebp - 0x3e3];
  [ebp - 0x3e2];

  /* usb2 [6] */
  [ebp - 0x3de];
  [ebp - 0x3dd];
  [ebp - 0x3dc];

  /* usb2 [7] */
  [ebp - 0x3d8];
  [ebp - 0x3d7];
  [ebp - 0x3d6];

  /* usb2 [8] */
  [ebp - 0x3d2];
  [ebp - 0x3d1];
  [ebp - 0x3d0];

  /* usb2 [9] */
  [ebp - 0x3cc];
  [ebp - 0x3cb];
  [ebp - 0x3ca];

  /* usb2 [10] */
  [ebp - 0x3c6];
  [ebp - 0x3c5];
  [ebp - 0x3c4];

  /* usb2 [11] */
  [ebp - 0x3c0];
  [ebp - 0x3bf];
  [ebp - 0x3be];

  /* usb2 [12] */
  [ebp - 0x3ba];
  [ebp - 0x3b9];
  [ebp - 0x3b8];

  /* usb2 [13] */
  [ebp - 0x3b4];
  [ebp - 0x3b3];
  [ebp - 0x3b2];

  byte [ebp - 0x3ac] = [ebp - 0x3ac] & 0xfffffffc | 2;

  int usb2oc[14]; // @ ebp - 0x397
  for (int i = 0; i < 13; i++)
    usb2oc[i] = pei->usb2_ports[i].over_current_pin;

  int usb3oc[6]; // @ ebp - 0x35f
  for (int i = 0; i < 6; i++)
    usb3oc[i] = pei->usb3_ports[i].over_current_pin;

  /* - 0x346 usb3[0] */
  ecx = pei->usb3_ports[0].enable & 1;
  eax = byte [ebp - 0x346] & 0xfffffffe;
  eax |= ecx;
  byte [ebp - 0x346] = al;

/* usb3[1] [2] [3] */

  byte [ebp - 0x4c0] = 3;
  byte [ebp - 0x4bf] = 0;
  [ebp - 0x4aa] = 0;
  byte [ebp - 0x565] = 4;

  /* usb3 [4] [5] */

  if (pei->gbe_enable != 0)
    [ebp - 0x636] = 1;

  zeromem(ebp - 0x632, 3);

  eax = ebp - 0x632;
  [ebp - 0x61a] = eax;
  edi = ebp - 0x585;

  [ebp - 0x4be] = pei->rcba;
  [ebp - 0x4ba] = pei->pmbase;
  [ebp - 0x4b8] = pei->gpiobase;
  ecx = 4;
  [ebp - 0x4b6] = ebp - 0x636;
  [ebp - 0x4b2] = ebp - 0x61a;
  [ebp - 0x4ae] = ebp - 0x60a;
  [ebp - 0x4a6] = ebp - 0x5cc;
  [ebp - 0x4a2] = ebp - 0x508;
  [ebp - 0x49e] = ebp - 0x635;
  [ebp - 0x49a] = ebp - 0x605;
  [ebp - 0x564] = [ebp - 0x496] = ebp - 0x403;
  byte [ebp - 0x560] = 1;

  while (ecx--) *edi++ = *esi++; // movsd, esi = ref_fffc9e38

  esi = ref_fffc9e48;
  edi = ebp - 0x4e8;
  cl = 10;
  while (cl--) *edi++ = *esi++; // movsd

  al = 0;
  zeromem(ebp - 0x592, 13);

  zeromem(ebp - 0x340, 0x32 * 4);
  [ebp - 0x55f] = 0xe8000000;

  mov dword [ebp - 0x55b], 0x800;
  mov dword [ebp - 0x557], 0xe8100000;
  mov word [ebp - 0x592], 0x800;
  mov word [ebp - 0x590], 2;
  mov byte [ebp - 0x58e], 1;
  mov byte [ebp - 0x58d], 2;
  mov byte [ebp - 0x58c], 3;
  byte [ebp - 0x58b] = 2;

  byte [ebp - 0x316] = pei->dimm_channel0_disabled;
  byte [ebp - 0x315] = pei->dimm_channel1_disabled;

#ifdef ASM
  mov byte [ebp - 0x340], 1
mov byte [ebp - 0x33d], 1
mov byte [ebp - 0x32f], 1
mov byte [ebp - 0x31c], 1
mov byte [ebp - 0x314], 1
mov byte [ebp - 0x312], 1
mov byte [ebp - 0x311], 1
mov byte [ebp - 0x310], 4
mov byte [ebp - 0x30f], 0xc
mov byte [ebp - 0x30d], 1
mov byte [ebp - 0x30c], 1
mov byte [ebp - 0x30b], 1
mov byte [ebp - 0x30a], 1
    mov byte [ebp - 0x308], 1;
#endif

  byte [ebp - 0x2e9] = pei->dq_pins_interleaved;
  byte [ebp - 0x2ca] = byte [ebp - 0x2d4] = pei->ddr_refresh_2x;

  /*
#ifdef ASM
mov byte [ebp - 0x307], 1
mov byte [ebp - 0x306], 1
mov byte [ebp - 0x304], 1
mov byte [ebp - 0x302], 1
mov byte [ebp - 0x300], 1
mov byte [ebp - 0x2ff], 1
mov byte [ebp - 0x2fe], 1
mov byte [ebp - 0x2fd], 1
mov byte [ebp - 0x2fc], 1
mov byte [ebp - 0x2f9], 1
mov byte [ebp - 0x2f8], 1
mov byte [ebp - 0x2f7], 1
mov byte [ebp - 0x2ea], 1
mov byte [ebp - 0x2e6], 1
mov byte [ebp - 0x2e4], 1
mov byte [ebp - 0x2e3], 6
mov byte [ebp - 0x2e2], 0x40
mov byte [ebp - 0x2e1], 1
mov byte [ebp - 0x2e0], 1
mov byte [ebp - 0x2de], 7
mov dword [ebp - 0x2dc], 0x5f5e100
mov byte [ebp - 0x2d6], 1
mov byte [ebp - 0x2d3], 1
mov word [ebp - 0x2d2], 0x30ce
mov byte [ebp - 0x2d0], 1
mov byte [ebp - 0x2cc], 1
mov byte [ebp - 0x2c9], 1
mov byte [ebp - 0x2c6], 3
  mov byte [ebp - 0x2b8], 0xff;
#endif
 */
  
  zeromem(ebp - 0x463, 0x18*4);
  zeromem(ebp - 0x492, 0x2f);

  [ebp - 0x2b7] = 0xff;
  [ebp - 0x2b6] = 0xff;
  [ebp - 0x2b5] = 0xff;
  [ebp - 0x2b4] = 0xff; 
  [ebp - 0x2b3] = 0xff;
  [ebp - 0x2b2] = 0xff;
  [ebp - 0x2b1] = 0xff;
  [ebp - 0x2b0] = 0xff;
  [ebp - 0x2af] = 0xff;

  [ebp - 0x492] = pei->spd_addresses[0];
  [ebp - 0x491] = pei->spd_addresses[1];
  [ebp - 0x490] = pei->spd_addresses[2];
  [ebp - 0x48f] = pei->spd_addresses[3];

  /* TODO: write in C
  mov byte [ebp - 0x2ae], 0xff
mov byte [ebp - 0x2ad], 0xff
mov byte [ebp - 0x2ac], 0xff
mov byte [ebp - 0x2ab], 0xff
mov byte [ebp - 0x2aa], 0xff
mov byte [ebp - 0x2a9], 0xff
mov byte [ebp - 0x294], 1
mov word [ebp - 0x293], 0x200
mov byte [ebp - 0x290], 0x30
mov byte [ebp - 0x28f], 1
mov byte [ebp - 0x28e], 0x40
mov byte [ebp - 0x27e], 1
mov byte [ebp - 0x27d], 1
mov byte [ebp - 0x27b], 1
mov byte [ebp - 0x462], 1
mov byte [ebp - 0x461], 1
mov byte [ebp - 0x460], 1
  */

  [ebp - 0x48e] = pei->mchbar;
  [ebp - 0x48a] = pei->dmibar;
  [ebp - 0x486] = pei->epbar;
  [ebp - 0x482] = pei->pciexbar;
  [ebp - 0x47e] = pei->smbusbar;

  esi = ref_fffc9e70;
  [ebp - 0x47a] = 0xfed84000;

  [ebp - 0x476] = pei->tseg_size;
  byte [ebp - 0x472] = pei->system_type;
  byte [ebp - 0x471] = 1;

  zeromem(ebp - 0x575, 16);
  zeromem(ebp - 0x526, 30);

  [ebp - 0x470] = 0xfed80000;

  [ebp - 0x525] = ebp - 0x492;
  [ebp - 0x521] = ebp - 0x592;
  [ebp - 0x51d] = ebp - 0x340;
  [ebp - 0x519] = ebp - 0x463;
  [ebp - 0x515] = ebp - 0x575;

  [ebp - 0x511] = pei->mrc_input;
  
  edi = ebp - 0x53e;
  ecx = 6;
  memcpy(edi, esi, 6*4); // esi = ref_fffc9e70, 6 function pointers

  edi = ebp - 0x600;
  zeromem(edi, 5);
  /* write them to C
mov dword [ebp - 0x467], 0x400000
mov byte [ebp - 0x526], 0xe
mov dword [ebp - 0x616], fcn_fffa049e  ; mov dword [ebp - 0x616], 0xfffa049e
mov dword [ebp - 0x612], fcn_fffa04c9  ; mov dword [ebp - 0x612], 0xfffa04c9
  */

  edi = ebp - 0x553;
  zeromem(edi, 21);

  [ebp - 0x552] = ebp - 0x600;
  zeromem(ebp - 0x62f, 3);
  zeromem(ebp - 0x278, 0x98*4);

  [ebp - 0x60e] = fcn_fffa04e0;

  [ebp - 0x20c] = pei->boot_mode;
  byte [ebp - 0x553] = 1;
  byte [ebp - 0x62f] = 1;

  [ebp - 0x200] = ebp - 0x5d4;
  [ebp - 0x278] = 0xfeadb00b;
  [ebp - 0x25c] = fcn_fffa2b02;
  [ebp - 0x254] = fcn_fffa2a76;
  [ebp - 0x1f4] = ebp - 0x526;
  [ebp - 0x250] = fcn_fffa043e;
  [ebp - 0x24c] = fcn_fffa041f;
  [ebp - 0x1e8] = ebp - 0x5dc;

  /* write to C 
mov dword [ebp - 0x244], fcn_fffa03fd  ; mov dword [ebp - 0x244], 0xfffa03fd
lea eax, [ebp - 0x4c0]
mov dword [ebp - 0x240], fcn_fffa29ba  ; mov dword [ebp - 0x240], 0xfffa29ba
mov dword [ebp - 0x1dc], eax
mov dword [ebp - 0x230], fcn_fffa04e7  ; mov dword [ebp - 0x230], 0xfffa04e7
lea eax, [ebp - 0x565]
mov dword [ebp - 0x224], memcpy  ; mov dword [ebp - 0x224], 0xfffa1178
mov dword [ebp - 0x1d0], eax
mov dword [ebp - 0x21c], fcn_fffa04ee  ; mov dword [ebp - 0x21c], 0xfffa04ee
lea eax, [ebp - 0x585]
mov dword [ebp - 0x214], ref_fffcc83c  ; mov dword [ebp - 0x214], 0xfffcc83c
mov dword [ebp - 0x204], ref_fffcd4b4  ; mov dword [ebp - 0x204], 0xfffcd4b4
mov dword [ebp - 0x1f8], ref_fffcd4e4  ; mov dword [ebp - 0x1f8], 0xfffcd4e4
mov dword [ebp - 0x1ec], ref_fffcd4d4  ; mov dword [ebp - 0x1ec], 0xfffcd4d4
mov dword [ebp - 0x1e0], ref_fffcca3c  ; mov dword [ebp - 0x1e0], 0xfffcca3c
mov dword [ebp - 0x1d4], ref_fffcc988  ; mov dword [ebp - 0x1d4], 0xfffcc988
mov dword [ebp - 0x1c8], ref_fffcc96c  ; mov dword [ebp - 0x1c8], 0xfffcc96c
mov dword [ebp - 0x1c4], eax
lea eax, [ebp - 0x53e]
mov dword [ebp - 0x1b8], eax
lea eax, [ebp - 0x4e8]
mov dword [ebp - 0x1ac], eax
lea eax, [ebp - 0x5ac]
mov dword [ebp - 0x1a0], eax
lea eax, [ebp - 0x616]
mov dword [ebp - 0x194], eax
lea eax, [ebp - 0x612]
mov dword [ebp - 0x188], eax
lea eax, [ebp - 0x60e]
mov dword [ebp - 0x17c], eax
lea eax, [ebp - 0x553]
mov dword [ebp - 0x170], eax
lea eax, [ebp - 0x62f]
mov dword [ebp - 0x164], eax
lea eax, [ebp - 0x274]
mov dword [ebp - 0x62c], eax
  */

  [0xfffd753c] = pei->tx_byte;

  /* write to C
mov dword [ebp - 0x1bc], ref_fffcd488  ; mov dword [ebp - 0x1bc], 0xfffcd488
mov dword [ebp - 0x1b0], ref_fffcd534  ; mov dword [ebp - 0x1b0], 0xfffcd534
mov dword [ebp - 0x1a4], ref_fffcd524  ; mov dword [ebp - 0x1a4], 0xfffcd524
mov dword [ebp - 0x198], ref_fffcc88c  ; mov dword [ebp - 0x198], 0xfffcc88c
mov dword [ebp - 0x18c], ref_fffcc89c  ; mov dword [ebp - 0x18c], 0xfffcc89c
mov dword [ebp - 0x180], ref_fffcc8ac  ; mov dword [ebp - 0x180], 0xfffcc8ac
mov dword [ebp - 0x174], ref_fffcc8bc  ; mov dword [ebp - 0x174], 0xfffcc8bc
mov dword [ebp - 0x168], ref_fffcc8cc  ; mov dword [ebp - 0x168], 0xfffcc8cc
mov dword [ebp - 0x118], 0xe
mov dword [ebp - 0x1c], edx
   */

  if (pei->pei_version != 0xf)
    return -1; // goto loc_fffa559c;

  [0xff7d7538] = ebp - 0x62c;
  mrc_printk("System Agent: Starting up...\n");

  if ([ebp - 0x20c] == 2) {
    if (pei->mrc_input != NULL) {
      [ebp - 0x20c] = 0x11;
      mrc_printk("System Agent: S3 resume detected\n");
      if (pei->usb_xhci_on_resume) {
	byte [ebp - 0x3ac] = [ebp - 0x3ac] & 0xfffffffc | 5;
	byte [ebp - 0x3ae] &= 0xfe;
	byte [ebp - 0x3ad] &= 0xfe;
      }
    }
  }

  eax = pei->max_ddr3_freq;
  if (eax == 1067) {
    [ebp - 0x33f] = 1067;
  } else if (eax == 800) {
    [ebp - 0x33f] = 800;
  } else if (eax == 1333) {
    [ebp - 0x33f] = 1333;
  } else if (eax == 1600) {
    [ebp - 0x33f] = 1600;
  } else {
    mrc_printk("System Agent: Unsupported DDR3 frequence %d (Supported are 800, 1067, 1333, 1600)\n", eax);
    return -2;
  }

  eax = fcn_fffc5ca7();

  edx = [0xf0000060] & 0xfc000000;
  dx = word [edx + 0xf8002];

  if (eax != 1) {
	  if (eax != 2)
		  goto loc_fffa3ab5;
	  else
		  goto loc_fffa3c1b;
  }

  eax = edx & 0xfffffffd;
  if (ax == 0x8c44 || ax == 0x8c4c)
    goto loc_fffa3aa7;

  if (dx == 0x8c5c)
    cl = 1;
  if (dx == 0x8c50)
    al = 1;
  cl |= al;
  if (cl == 0) {
	  eax = edx & 0xfffffff7;
	  if (ax != 0x8c42)
		  goto loc_fffa3b14;
  }

 loc_fffa3a6d:
 loc_fffa3aa7:
  for (int i = 0; i < fcn_fffc5d89(); i++) {
    eax = &(ebp - 0x402)[i]; /* usb2 {.en, .location, .length, .f4, .f5 } */
    if (eax->location == 0) {
      dx = eax->length;
      eax->f4 = 4;
      if (dx <= 0x7f) {
	eax->f5 = 2;
	continue;
      }
      eax->f5 = 4 - (dx < 0x130);
      continue;
    } else {
      eax->f4 = 3;
      eax->f5 = 2;
      continue;
    }
  }

 loc_fffa3ab5:
  mrc_printk("System Agent: Initializing PCH\n");
  eax = pci_mmio_read_config32(PCI_DEV(0, 0, 0), PCIEXBAR) & 0xfc000000;
  ebx = PeiCore;
  edx = dword [eax + 0xf80f0] & 0xfffffffe;
  word [edx + 0x3424] = 0x10;
  /* write to C
mov eax, dword [edx + 0x3428]
or eax, 1
mov dword [edx + 0x3428], eax
*/

  eax = pci_mmio_read_config32(PCI_DEV(0, 0, 0), PCIEXBAR) & 0xfc000000;
  ax = word [eax + 0xf80a4];
  if ((al & 4) == 0)
	  goto loc_fffa3c99;
  else
	  goto loc_fffa3c2e;

loc_fffa3b14:
  if (dx == 0x8c4f || dx == 0x8c49 || dx == 0x8c41 || dx == 0x8c4b)
	  goto loc_fffa3b4e;
  dx += 0x63bf;
  ebx = 0;
  if (dx > 6)
	  goto loc_fffa3ab5;

loc_fffa3b4e:
  for (int i = 0; i < fcn_fffc5d89(); i++) {
    eax = &(ebp - 0x402)[i]; /* usb2 {.en, .location, .length, .f4, .f5 } */
    dl = eax->location;
    if (dl != 5) {
	    if (dl == 2) {
		    eax->f4 = 4;
		    eax->f5 = 2 - (eax->length < 0x50);
	    } else {
		    dx = eax->length;
		    if (dx <= 0x6f) {
			    eax->f4 = 5;
			    eax->f5 = 2;
		    } else {
			    eax->f4 = 6;
			    if (dx <= 0xff) {
				    eax->f5 = 2;
			    } else {
				    eax->f5 = 3;
			    }
		    }
	    }
    } else {
	    eax->f4 = 5;
	    eax->f5 = 2;
    }
  }
  goto loc_fffa3ab5;

  /* loc_fffa3c1b
loc_fffa3bc0:
imul eax, ebx, 6
lea esi, [ebp + eax - 0x402]
mov al, byte [esi + 1]
cmp al, 3
sete cl
test al, al
sete dl
or cl, dl
je short loc_fffa3bf3
mov ax, word [esi + 2]
cmp ax, 0x6f
ja short loc_fffa3be7
jmp short loc_fffa3c0a

loc_fffa3be7:
cmp ax, 0xff
mov byte [esi + 4], 6
ja short loc_fffa3c14  ; ja 0xfffa3c14
jmp short loc_fffa3c0e  ; jmp 0xfffa3c0e

loc_fffa3bf3:
cmp al, 2
jne short loc_fffa3c0a  ; jne 0xfffa3c0a
cmp word [esi + 2], 0x50
mov byte [esi + 4], 4
sbb eax, eax
add eax, 2
mov byte [esi + 5], al
jmp short loc_fffa3c18

loc_fffa3c0a:
mov byte [esi + 4], 5

loc_fffa3c0e:
mov byte [esi + 5], 2
jmp short loc_fffa3c18  ; jmp 0xfffa3c18

loc_fffa3c14:
mov byte [esi + 5], 3

loc_fffa3c18:
inc ebx
jmp short loc_fffa3c1d  ; jmp 0xfffa3c1d

loc_fffa3c1b:
xor ebx, ebx

loc_fffa3c1d:
call fcn_fffc5d89  ; call 0xfffc5d89
movzx eax, al
cmp ebx, eax
jl short loc_fffa3bc0  ; jl 0xfffa3bc0
jmp near loc_fffa3ab5
*/

loc_fffa3c2e:
  /*
mov eax, dword [edx + 0x3410]
or eax, 0x10
mov dword [edx + 0x3410], eax
mov eax, dword [edx + 0x3410]
in al, 0x70
mov esi, eax
mov eax, dword [edx + 0x3410]
and eax, 0xffffffef
and esi, 0xffffff80
mov dword [edx + 0x3410], eax
mov ecx, esi
mov eax, dword [edx + 0x3410]
or ecx, 0xa
mov al, cl
out 0x70, al
in al, 0x71
and eax, 0xffffff8f
or eax, 0x60
out 0x71, al
or esi, 0xb
mov eax, esi
out 0x70, al
in al, 0x71
or eax, 0xffffff80
out 0x71, al
mov al, cl
out 0x70, al
in al, 0x71
and eax, 0xffffff8f
or eax, 0x20
out 0x71, al
mov eax, esi
out 0x70, al
in al, 0x71
and eax, 0x7f
out 0x71, al
*/
loc_fffa3c99:
  [edx + 0x3310] = 0x10;
  eax = ebx;
  fcn_fffc7c9d();
  esi = eax = mrc_alloc(12);
  if (eax != NULL) {
	  mrc_zeromem(eax, 12);
	  edi = eax = mrc_alloc(0x28);
	  if (eax != NULL) {
		  mrc_zeromem(eax, 0x28);
		  mrc_memcpy(edi, ref_fffcc8dc, 0x28);
		  [esi + 8] = edi;
		  [esi] = 0x80000010;
		  [esi + 4] = ref_fffcd534;

		  PeiCore->[0]->0x18(PeiCore, esi, edi, edi);
		  PeiCore->[0]->0x18(PeiCore, ref_fffcc97c);
		  PeiCore->[0]->0x24 ...;
		  PeiCore->[0]->0x24 ...;
	  }
  }

  fcn_fffb9720(PeiCore, 0, 0, ecx);
  mrc_printk("System Agent: Initializing PCH (SMBUS)\n");
}

do_raminit:
mov eax, 0x10f
mov esi, dword [0xff7d7538]
call mrc_alloc
add esp, 0x10
test eax, eax
mov ebx, eax
je loc_fffa3def  ; je 0xfffa3def
mov edx, eax
mov eax, esi
call fcn_fffc5bf6  ; call 0xfffc5bf6
mov eax, dword [0xf0000060]
and eax, 0xfc000000
mov edx, dword [eax + 0xfb020]
and edx, 0xffe0
or edx, dword [ebx + 0xc]
mov dword [eax + 0xfb020], edx
mov dl, byte [eax + 0xfb004]
or edx, 1
mov byte [eax + 0xfb004], dl
mov dl, byte [eax + 0xfb040]
or edx, 8
mov byte [eax + 0xfb040], dl
mov dl, byte [eax + 0xfb040]
and edx, 0xfffffff8
or edx, 1
mov byte [eax + 0xfb040], dl
mov edx, 0xff
xor eax, eax
call fcn_fffc917f  ; call 0xfffc917f
mov eax, dword [0xff7d7538]
lea ecx, [ebx + 0x10]
push edi
add ebx, 0x2c
push edi
mov edx, dword [eax]
push ecx
push eax
call dword [edx + 0x18]  ; ucall
pop eax
pop edx
mov eax, dword [esi]
push ebx
push esi
call dword [eax + 0x24]  ; ucall
add esp, 0x10

loc_fffa3def:
sub esp, 0xc
push ref_fffcc60f  ; push 0xfffcc60f
call mrc_printk  ; call 0xfffa1253
pop ebx
push dword [0xff7d7538]
call fcn_fffaea18  ; call 0xfffaea18
mov dword [esp], ref_fffcc635  ; mov dword [esp], 0xfffcc635
call mrc_printk  ; call 0xfffa1253
mov edx, dword [0xff7d7538]
mov dword [ebp - 0x640], edx
call haswell_family_model
mov ecx, dword [ebp - 0x640]
lea edx, [ebp - 0x628]
mov dword [ebp - 0x648], eax
mov eax, dword [ecx]
mov dword [esp], edx
push 0
push 0
push ref_fffcd4e4  ; push 0xfffcd4e4
push ecx
call dword [eax + 0x20]  ; ucall
mov ebx, dword [ebp - 0x628]
add esp, 0x20
call haswell_family_model
mov ecx, eax
mov esi, dword [0xf0000060]
and esi, 0xfc000000
xor edx, edx
mov eax, dword [ebx + 1]
mov eax, dword [eax + 4]
or eax, 1
mov dword [esi + 0x48], eax
mov dword [esi + 0x4c], edx
mov eax, dword [ebx + 1]
mov esi, dword [0xf0000060]
and esi, 0xfc000000
xor edx, edx
mov eax, dword [eax + 8]
or eax, 1
mov dword [esi + 0x68], eax
mov dword [esi + 0x6c], edx
mov eax, dword [ebx + 1]
mov esi, dword [0xf0000060]
and esi, 0xfc000000
xor edx, edx
mov eax, dword [eax + 0xc]
or eax, 1
mov dword [esi + 0x40], eax
mov dword [esi + 0x44], edx
mov eax, dword [ebx + 1]
xor edx, edx
mov esi, dword [eax + 4]
mov eax, dword [eax + 0x18]
or eax, 1
cmp ecx, 0x40660
mov dword [esi + 0x5420], eax
mov dword [esi + 0x5424], edx
jne short loc_fffa3eec  ; jne 0xfffa3eec
mov eax, dword [ebx + 1]
xor edx, edx
mov ecx, dword [eax + 4]
mov eax, dword [eax + 0x22]
or eax, 1
mov dword [ecx + 0x5408], eax
mov dword [ecx + 0x540c], edx

loc_fffa3eec:
mov edx, dword [ebp - 0x640]
mov ebx, dword [ebp - 0x628]
mov esi, ref_fffcd4a4  ; mov esi, 0xfffcd4a4
mov eax, dword [edx]
lea edx, [ebp - 0x620]
push edx
push 0x6d
push 4
push dword [ebp - 0x640]
call dword [eax + 0x34]  ; ucall
mov eax, dword [ebp - 0x620]
mov ecx, 4
mov edx, 8
lea edi, [eax + 8]
add eax, 0x18
rep movsd  ; rep movsd dword es:[edi], dword ptr [esi]
call mrc_zeromem
mov eax, dword [ebp - 0x620]
mov edx, 8
add eax, 0x20
call mrc_zeromem
mov eax, dword [ebp - 0x620]
mov edx, 0x1e
add eax, 0x29
call mrc_zeromem
mov eax, dword [ebp - 0x620]
add esp, 0x10
mov byte [eax + 0x28], 0
mov byte [eax + 0x6c], 0
cmp byte [ebx], 1
jbe short loc_fffa3f82  ; jbe 0xfffa3f82
mov edx, dword [ebx + 0xd]
mov dx, word [edx + 0x4a]
mov word [eax + 0x47], dx
mov edx, dword [ebx + 0xd]
mov dl, byte [edx + 0x49]
mov byte [eax + 0x49], dl
jmp short loc_fffa3f8c  ; jmp 0xfffa3f8c

loc_fffa3f82:
mov word [eax + 0x47], 0
mov byte [eax + 0x49], 0

loc_fffa3f8c:
mov ecx, dword [ebp - 0x640]
sub esp, 0xc
lea edx, [ebp - 0x5e8]
mov eax, dword [ecx]
push edx
push 0
push 0
push ref_fffcc8bc  ; push 0xfffcc8bc
push ecx
call dword [eax + 0x20]  ; ucall
mov eax, dword [ebp - 0x620]
add esp, 0x20
mov byte [eax + 0x20], 2
mov edx, dword [ebp - 0x5e8]
mov ecx, dword [edx + 1]
test byte [ecx], 0x10
je short loc_fffa3fd4  ; je 0xfffa3fd4
mov edx, dword [edx + 9]
mov edx, dword [edx]
mov dl, byte [edx + 0x301]
mov byte [eax + 0x21], dl

loc_fffa3fd4:
mov ebx, dword [ebp - 0x628]
call haswell_family_model
mov esi, eax
call haswell_stepping
dec eax
sete dl
cmp esi, 0x306c0
sete al
test dl, al
mov eax, dword [ebx + 1]
je short loc_fffa4009  ; je 0xfffa4009
mov eax, dword [eax + 4]
mov dword [eax + 0x5434], 0x1060100
jmp short loc_fffa4025  ; jmp 0xfffa4025

loc_fffa4009:
movzx edx, byte [ebx]
mov eax, dword [eax + 8]
mov dword [eax + 0x71c], edx
mov eax, dword [ebx + 1]
mov eax, dword [eax + 8]
mov dword [eax + 0x720], 0x1060100

loc_fffa4025:
cmp dword [ebp - 0x648], 0x40660
sete dl
cmp dword [ebp - 0x648], 0x306c0
sete al
or dl, al
je loc_fffa4d64  ; je 0xfffa4d64
mov eax, dword [ebp - 0x628]
mov dword [ebp - 0x660], eax
call haswell_stepping
mov eax, dword [0xf0000060]
sub esp, 0xc
and eax, 0xfc000000
mov edx, dword [eax + 0x48]
mov ecx, dword [eax + 0x4c]
mov dword [ebp - 0x648], edx
mov dword [ebp - 0x644], ecx
mov eax, dword [0xf0000060]
mov ecx, dword [ebp - 0x640]
and eax, 0xfc000000
lea edx, [ebp - 0x5e8]
mov esi, dword [eax + 0x68]
mov edi, dword [eax + 0x6c]
mov eax, dword [ecx]
push edx
push 0
push 0
push ref_fffcca3c  ; push 0xfffcca3c
push ecx
call dword [eax + 0x20]  ; ucall
add esp, 0x20
test eax, eax
js loc_fffa4d64  ; js 0xfffa4d64
mov eax, dword [ebp - 0x648]
mov ebx, esi
and eax, 0xfffffffe
and ebx, 0xfffffffe
mov dword [ebp - 0x648], eax
call haswell_family_model
mov edi, eax
call haswell_stepping
mov edx, 0xa00

loc_fffa40d3:
test ebx, ebx
je short loc_fffa40de  ; je 0xfffa40de
lea esi, [edx + ebx]
mov ecx, dword [esi]
jmp short loc_fffa40fc  ; jmp 0xfffa40fc

loc_fffa40de:
mov esi, dword [0xf0000060]
mov ecx, dword [0xf0000060]
and ecx, 0xfc000000
and esi, 0xfc000000
add ecx, edx
add esi, edx
mov ecx, dword [ecx]

loc_fffa40fc:
and ecx, 0xffffffe0
add edx, 0x10
or ecx, 0xc
cmp edx, 0xa40
mov dword [esi], ecx
jne short loc_fffa40d3  ; jne 0xfffa40d3
dec eax
sete dl
cmp edi, 0x306c0
sete al
and dl, al
mov byte [ebp - 0x658], dl
jne short loc_fffa412c  ; jne 0xfffa412c

loc_fffa4126:
test ebx, ebx
je short loc_fffa4188  ; je 0xfffa4188
jmp short loc_fffa4176  ; jmp 0xfffa4176

loc_fffa412c:
xor eax, eax
lea ecx, [ebx + 0xa04]

loc_fffa4134:
test ebx, ebx
je short loc_fffa413f  ; je 0xfffa413f
lea esi, [ecx + eax]
mov edx, dword [esi]
jmp short loc_fffa4167  ; jmp 0xfffa4167

loc_fffa413f:
mov edx, dword [0xf0000060]
and edx, 0xfc000000
lea esi, [eax + edx + 0xa04]
mov edx, dword [0xf0000060]
and edx, 0xfc000000
lea edx, [eax + edx + 0xa04]
mov edx, dword [edx]

loc_fffa4167:
add eax, 0x10
or dh, 8
cmp eax, 0x40
mov dword [esi], edx
jne short loc_fffa4134  ; jne 0xfffa4134
jmp short loc_fffa4126  ; jmp 0xfffa4126

loc_fffa4176:
cmp byte [ebp - 0x658], 0
jne loc_fffa42c3  ; jne 0xfffa42c3
jmp near loc_fffa4231  ; jmp 0xfffa4231

loc_fffa4188:
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov eax, dword [eax + 0x904]
and eax, 0xffffffe0
or eax, 2
mov dword [edx + 0x904], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x924]
and eax, 0xffffffe0
or eax, 2
mov dword [edx + 0x924], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x904]
and eax, 0xfffffc1f
or eax, 0x60
mov dword [edx + 0x904], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x924]
and eax, 0xfffffc1f
or eax, 0x60
mov dword [edx + 0x924], eax
jmp near loc_fffa4176  ; jmp 0xfffa4176

loc_fffa4231:
test ebx, ebx
jne short loc_fffa4292  ; jne 0xfffa4292

loc_fffa4235:
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov eax, dword [eax + 0x90c]
and eax, 0xfffff81f
or eax, 0x120
mov dword [edx + 0x90c], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x92c]
and eax, 0xfffff81f
or eax, 0x120
mov dword [edx + 0x92c], eax
jmp near loc_fffa43cb  ; jmp 0xfffa43cb

loc_fffa4292:
mov eax, dword [ebx + 0x90c]
and eax, 0xfffff81f
or eax, 0x120
mov dword [ebx + 0x90c], eax
mov eax, dword [ebx + 0x92c]
and eax, 0xfffff81f
or eax, 0x120
mov dword [ebx + 0x92c], eax
jmp near loc_fffa43cb  ; jmp 0xfffa43cb

loc_fffa42c3:
test ebx, ebx
jne loc_fffa4378  ; jne 0xfffa4378
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov edx, dword [edx + 0x904]
and edx, 0xfe3fffff
mov dword [eax + 0x904], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x924]
and edx, 0xfe3fffff
mov dword [eax + 0x924], edx
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x904]
and eax, 0x9fffffff
or eax, 0x20000000
mov dword [edx + 0x904], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x924]
and eax, 0x9fffffff
or eax, 0x20000000
mov dword [edx + 0x924], eax
jmp near loc_fffa4235  ; jmp 0xfffa4235

loc_fffa4378:
mov eax, dword [ebx + 0x904]
and eax, 0xfe3fffff
mov dword [ebx + 0x904], eax
mov eax, dword [ebx + 0x924]
and eax, 0xfe3fffff
mov dword [ebx + 0x924], eax
mov eax, dword [ebx + 0x904]
and eax, 0x9fffffff
or eax, 0x20000000
mov dword [ebx + 0x904], eax
mov eax, dword [ebx + 0x924]
and eax, 0x9fffffff
or eax, 0x20000000
mov dword [ebx + 0x924], eax
jmp near loc_fffa4231  ; jmp 0xfffa4231

loc_fffa43cb:
cmp byte [ebp - 0x658], 0
jne short loc_fffa43e1  ; jne 0xfffa43e1

loc_fffa43d4:
test ebx, ebx
je loc_fffa44ad  ; je 0xfffa44ad
jmp near loc_fffa5681  ; jmp 0xfffa5681

loc_fffa43e1:
test ebx, ebx
jne short loc_fffa4437  ; jne 0xfffa4437
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov edx, dword [edx + 0x90c]
and edx, 0xfff1ffff
mov dword [eax + 0x90c], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x92c]
and edx, 0xfff1ffff
mov dword [eax + 0x92c], edx
jmp short loc_fffa44ad  ; jmp 0xfffa44ad

loc_fffa4437:
mov eax, dword [ebx + 0x90c]
and eax, 0xfff1ffff
mov dword [ebx + 0x90c], eax
mov eax, dword [ebx + 0x92c]
and eax, 0xfff1ffff
mov dword [ebx + 0x92c], eax
jmp near loc_fffa43d4  ; jmp 0xfffa43d4

loc_fffa445e:
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov edx, dword [edx + 0x910]
and dh, 0xc3
mov dword [eax + 0x910], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x930]
and dh, 0xc3
mov dword [eax + 0x930], edx
jmp near loc_fffa4564  ; jmp 0xfffa4564

loc_fffa44ad:
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
xor edi, edi
mov eax, dword [eax + 0x90c]
and eax, 0xfe1fffff
or eax, 0xa00000
mov dword [edx + 0x90c], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x92c]
and eax, 0xfe1fffff
or eax, 0xa00000
mov dword [edx + 0x92c], eax

loc_fffa4507:
mov edx, dword [ebp - 0x660]
mov eax, 0x200
cmp byte [edx], 2
jbe short loc_fffa4522  ; jbe 0xfffa4522
mov eax, dword [edx + 0xd]
movzx eax, byte [eax + edi + 0x54]
shl eax, 6

loc_fffa4522:
mov edx, dword [0xf0000060]
mov ecx, edi
shl ecx, 5
and edx, 0xfc000000
inc edi
lea esi, [ecx + edx + 0x910]
mov edx, dword [0xf0000060]
and edx, 0xfc000000
lea edx, [ecx + edx + 0x910]
mov edx, dword [edx]
and edx, 0xfffffc3f
or edx, eax
cmp edi, 2
mov dword [esi], edx
jne short loc_fffa4507  ; jne 0xfffa4507
jmp near loc_fffa445e  ; jmp 0xfffa445e

loc_fffa4564:
cmp byte [ebp - 0x658], 0
jne loc_fffa45f1  ; jne 0xfffa45f1

loc_fffa4571:
test ebx, ebx
jne short loc_fffa45ca  ; jne 0xfffa45ca

loc_fffa4575:
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov edx, dword [edx + 0x80c]
and edx, 0xffe3ffff
mov dword [eax + 0x80c], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x82c]
and edx, 0xffe3ffff
mov dword [eax + 0x82c], edx
jmp near loc_fffa476b  ; jmp 0xfffa476b

loc_fffa45ca:
mov eax, dword [ebx + 0x80c]
and eax, 0xffe3ffff
mov dword [ebx + 0x80c], eax
mov eax, dword [ebx + 0x82c]
and eax, 0xffe3ffff
mov dword [ebx + 0x82c], eax
jmp near loc_fffa476b  ; jmp 0xfffa476b

loc_fffa45f1:
test ebx, ebx
jne loc_fffa46f4  ; jne 0xfffa46f4
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov eax, dword [eax + 0x910]
and eax, 0x1fffffff
or eax, 0x80000000
mov dword [edx + 0x910], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x930]
and eax, 0x1fffffff
or eax, 0x80000000
mov dword [edx + 0x930], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x80c]
and eax, 0xfffffe7f
or ah, 1
mov dword [edx + 0x80c], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x82c]
and eax, 0xfffffe7f
or ah, 1
mov dword [edx + 0x82c], eax
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x80c]
and dh, 0xcf
mov dword [eax + 0x80c], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x82c]
and dh, 0xcf
mov dword [eax + 0x82c], edx
jmp near loc_fffa4575  ; jmp 0xfffa4575

loc_fffa46f4:
mov eax, dword [ebx + 0x910]
and eax, 0x1fffffff
or eax, 0x80000000
mov dword [ebx + 0x910], eax
mov eax, dword [ebx + 0x930]
and eax, 0x1fffffff
or eax, 0x80000000
mov dword [ebx + 0x930], eax
mov eax, dword [ebx + 0x80c]
and eax, 0xfffffe7f
or ah, 1
mov dword [ebx + 0x80c], eax
mov eax, dword [ebx + 0x82c]
and eax, 0xfffffe7f
or ah, 1
mov dword [ebx + 0x82c], eax
mov eax, dword [ebx + 0x80c]
and ah, 0xcf
mov dword [ebx + 0x80c], eax
mov eax, dword [ebx + 0x82c]
and ah, 0xcf
mov dword [ebx + 0x82c], eax
jmp near loc_fffa4571  ; jmp 0xfffa4571

loc_fffa476b:
cmp byte [ebp - 0x658], 0
je loc_fffa4840  ; je 0xfffa4840
test ebx, ebx
jne short loc_fffa47ce  ; jne 0xfffa47ce
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov edx, dword [edx + 0x80c]
or edx, 0x600000
mov dword [eax + 0x80c], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x82c]
or edx, 0x600000
mov dword [eax + 0x82c], edx
jmp short loc_fffa47f0  ; jmp 0xfffa47f0

loc_fffa47ce:
mov eax, dword [ebx + 0x80c]
or eax, 0x600000
mov dword [ebx + 0x80c], eax
mov eax, dword [ebx + 0x82c]
or eax, 0x600000
mov dword [ebx + 0x82c], eax

loc_fffa47f0:
sub esp, 0xc
mov ecx, 0x22
push 0
mov edx, 0xc008018
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
and ah, 0xe1
mov ecx, 0x23
or ah, 0xc
mov edx, 0xc008018
mov dword [esp], eax
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
mov esi, 0xc008018
add esp, 0x10
mov byte [ebp - 0x65a], 0x23
mov byte [ebp - 0x659], 0x22
jmp short loc_fffa4853  ; jmp 0xfffa4853

loc_fffa4840:
mov byte [ebp - 0x65a], 0x16
mov esi, 0xc008001
mov byte [ebp - 0x659], 0x15

loc_fffa4853:
test ebx, ebx
jne short loc_fffa4894  ; jne 0xfffa4894
sub esp, 0xc
mov edx, esi
push 0
movzx ecx, byte [ebp - 0x659]
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
and eax, 0xc1ffffff
mov edx, esi
movzx ecx, byte [ebp - 0x65a]
or eax, 0x6000000
mov dword [esp], eax
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
add esp, 0x10

loc_fffa4894:
cmp byte [ebp - 0x658], 0
jne loc_fffa55a4  ; jne 0xfffa55a4
mov esi, 0xc0c8001

loc_fffa48a6:
sub esp, 0xc
mov edx, esi
push 0
movzx ecx, byte [ebp - 0x659]
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
and eax, 0xe07fffff
mov edx, esi
movzx ecx, byte [ebp - 0x65a]
mov dword [esp], eax
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
add esp, 0x10
cmp byte [ebp - 0x658], 0
mov edx, 0x13
je short loc_fffa4962  ; je 0xfffa4962
sub esp, 0xc
mov ecx, 0x20
push 0
mov edx, 0xc308803
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
and eax, 0x8ff83fff
mov ecx, 0x21
or eax, 0x40064000
mov edx, 0xc308803
mov dword [esp], eax
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
add esp, 0x10
test ebx, ebx
jne loc_fffa5628  ; jne 0xfffa5628
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov eax, dword [eax + 0xc24]
and eax, 0xffff807f
or ah, 2
mov dword [edx + 0xc24], eax
jmp near loc_fffa5628  ; jmp 0xfffa5628

loc_fffa4962:
test ebx, ebx
je short loc_fffa4979  ; je 0xfffa4979
mov eax, dword [ebx + 0xc28]
and eax, 0xffffffe0
or eax, edx
mov dword [ebx + 0xc28], eax
jmp short loc_fffa49a0  ; jmp 0xfffa49a0

loc_fffa4979:
mov ecx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and eax, 0xfc000000
and ecx, 0xfc000000
mov eax, dword [eax + 0xc28]
and eax, 0xffffffe0
or eax, edx
mov dword [ecx + 0xc28], eax

loc_fffa49a0:
mov al, byte [ebp - 0x658]
shl eax, 0x1f
sar eax, 0x1f
and eax, 0x40
test ebx, ebx
jne loc_fffa4baa  ; jne 0xfffa4baa
mov ecx, dword [0xf0000060]
mov edx, dword [0xf0000060]
and edx, 0xfc000000
and ecx, 0xfc000000
mov dx, word [edx + 0x8c38]
and edx, 0xffffffbf
or edx, eax
mov word [ecx + 0x8c38], dx
mov ecx, dword [0xf0000060]
mov edx, dword [0xf0000060]
and ecx, 0xfc000000
and edx, 0xfc000000
mov dx, word [edx + 0x9c38]
and edx, 0xffffffbf
or edx, eax
mov word [ecx + 0x9c38], dx
mov ecx, dword [0xf0000060]
mov edx, dword [0xf0000060]
and ecx, 0xfc000000
and edx, 0xfc000000
mov dx, word [edx + 0xac38]
and edx, 0xffffffbf
or edx, eax
mov word [ecx + 0xac38], dx
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov ax, word [eax + 0x8260]
and eax, 0xfffffffc
or eax, 2
mov word [edx + 0x8260], ax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov ax, word [eax + 0x9260]
and eax, 0xfffffffc
or eax, 2
mov word [edx + 0x9260], ax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov ax, word [eax + 0xa260]
and eax, 0xfffffffc
or eax, 2
mov word [edx + 0xa260], ax
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x900]
and edx, 0xf3ffffff
mov dword [eax + 0x900], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x920]
and edx, 0xf3ffffff
mov dword [eax + 0x920], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x904]
or dh, 0xc
mov dword [eax + 0x904], edx
mov eax, dword [0xf0000060]
mov edx, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov edx, dword [edx + 0x924]
or dh, 0xc
mov dword [eax + 0x924], edx
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x90c]
and eax, 0xc1ffffff
or eax, 0xe000000
mov dword [edx + 0x90c], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x92c]
and eax, 0xc1ffffff
or eax, 0xe000000
mov dword [edx + 0x92c], eax
jmp short loc_fffa4c0d  ; jmp 0xfffa4c0d

loc_fffa4baa:
mov edx, dword [ebx + 0xc38]
and edx, 0xffffffbf
or edx, eax
mov dword [ebx + 0xc38], edx
mov eax, dword [ebx + 0x260]
and eax, 0xfffffffc
or eax, 2
mov dword [ebx + 0x260], eax
mov eax, dword [ebx + 0x900]
and eax, 0xf3ffffff
mov dword [ebx + 0x900], eax
mov eax, dword [ebx + 0x920]
and eax, 0xf3ffffff
mov dword [ebx + 0x920], eax
mov eax, dword [ebx + 0x904]
or ah, 0xc
mov dword [ebx + 0x904], eax
mov eax, dword [ebx + 0x924]
or ah, 0xc
mov dword [ebx + 0x924], eax

loc_fffa4c0d:
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and eax, 0xfc000000
and edx, 0xfc000000
mov ecx, dword [ebp - 0x660]
mov eax, dword [eax + 0x891c]
and eax, 0xc7ffffff
or eax, 0x28000000
mov dword [edx + 0x891c], eax
mov edx, dword [0xf0000060]
mov eax, dword [0xf0000060]
and edx, 0xfc000000
and eax, 0xfc000000
mov eax, dword [eax + 0x893c]
and eax, 0xc7ffffff
or eax, 0x28000000
mov dword [edx + 0x893c], eax
mov eax, dword [ebx + 0x258]
or eax, 0x20000000
xor edx, edx
mov dword [ebx + 0x258], eax
mov eax, dword [ebx + 0x208]
and eax, 0xfffff800
or eax, 0x6b5
mov dword [ebx + 0x208], eax
mov eax, dword [ebx + 0x22c]
xor ax, ax
or eax, 0x2020
mov dword [ebx + 0x22c], eax
mov eax, dword [ecx + 0xd]
cmp byte [eax + 3], 0
je short loc_fffa4ce2  ; je 0xfffa4ce2
mov eax, dword [ebp - 0x5e8]
mov eax, dword [eax + 2]
mov al, byte [eax + 0x21a4]
and eax, 0xf
dec al
je short loc_fffa4ce2  ; je 0xfffa4ce2
mov eax, dword [0xf0000060]
and eax, 0xfc000000
mov eax, dword [eax + 0xe4]
test eax, 0x400000
je loc_fffa562f  ; je 0xfffa562f

loc_fffa4ce2:
mov ecx, dword [ebx + 0x84]
mov eax, dword [ebx + 0x98]
and eax, 0xfffffff0
and ecx, 0xf
or eax, ecx
mov dword [ebx + 0x98], eax
mov al, byte [ebx + 0x88]
or eax, 0x20
mov byte [ebx + 0x88], al

loc_fffa4d0b:
mov cx, word [ebx + 0x8a]
lea eax, [ebx + 0x8a]
and ch, 8
jne short loc_fffa4d0b  ; jne 0xfffa4d0b
test dl, dl
jne short loc_fffa4d26  ; jne 0xfffa4d26

loc_fffa4d21:
mov ax, word [eax]
jmp short loc_fffa4d64  ; jmp 0xfffa4d64

loc_fffa4d26:
mov dx, word [eax]
and edx, 0xf
cmp dx, 2
jne short loc_fffa4d4b  ; jne 0xfffa4d4b
mov edx, dword [ebp - 0x5e8]
mov edx, dword [edx + 2]
mov dx, word [edx + 0x21aa]
and edx, 0xf
cmp dx, 2
je short loc_fffa4d21  ; je 0xfffa4d21

loc_fffa4d4b:
mov dl, byte [ebx + 0x88]
or edx, 0x20
mov byte [ebx + 0x88], dl

loc_fffa4d5a:
mov dx, word [eax]
and dh, 8
jne short loc_fffa4d5a  ; jne 0xfffa4d5a
jmp short loc_fffa4d21  ; jmp 0xfffa4d21

loc_fffa4d64:
mov eax, dword [ebp - 0x640]
mov edx, dword [ebp - 0x628]
call fcn_fffa0625  ; call 0xfffa0625
mov edi, dword [ebp - 0x628]
mov dword [ebp - 0x624], 0
mov eax, dword [edi + 0x11]
cmp byte [eax + 0xb], 0
jne loc_fffa4e1b  ; jne 0xfffa4e1b

loc_fffa4d92:
mov eax, dword [0xf0000060]
mov esi, dword [ebp - 0x628]
and eax, 0xfc000000
mov edx, dword [eax + 0x4c]
mov eax, dword [eax + 0x48]
mov eax, dword [0xf0000060]
and eax, 0xfc000000
mov edx, dword [eax + 0x6c]
mov eax, dword [eax + 0x68]
mov edi, eax
call haswell_family_model
mov edx, dword [ebp - 0x640]
sub esp, 0xc
mov ebx, eax
and edi, 0xfffffffe
mov eax, dword [edx]
lea edx, [ebp - 0x620]
push edx
push 0
push 0
push ref_fffcc96c  ; push 0xfffcc96c
push dword [ebp - 0x640]
call dword [eax + 0x20]  ; ucall
mov ecx, dword [ebp - 0x640]
add esp, 0x14
lea edx, [ebp - 0x5e8]
mov eax, dword [ecx]
push edx
push 0
push 0
push ref_fffcd534  ; push 0xfffcd534
push ecx
call dword [eax + 0x20]  ; ucall
add esp, 0x20
cmp ebx, 0x40650
jne loc_fffa5349  ; jne 0xfffa5349
jmp near loc_fffa533a  ; jmp 0xfffa533a

loc_fffa4e1b:
mov edx, 7
lea eax, [ebp - 0x5f6]
call mrc_zeromem
mov edx, 7
lea eax, [ebp - 0x5ef]
call mrc_zeromem
mov eax, dword [0xff7d7538]
sub esp, 0xc
lea ecx, [ebp - 0x620]
mov bl, 1
mov edx, dword [eax]
push ecx
push 0
push 0
push ref_fffcd488  ; push 0xfffcd488
push eax
call dword [edx + 0x20]  ; ucall
mov ecx, 0x150
add esp, 0x20
rdmsr
mov dword [ebp - 0x648], eax
mov dword [ebp - 0x644], edx

loc_fffa4e71:
mov al, bl
and eax, 0xfffffffd
dec al
je short loc_fffa4e85  ; je 0xfffa4e85
lea eax, [ebx - 4]
cmp al, 1
ja loc_fffa532b  ; ja 0xfffa532b

loc_fffa4e85:
mov edx, 5
lea eax, [ebp - 0x5fb]
call mrc_zeromem
mov edx, 8
lea eax, [ebp - 0x5b4]
mov byte [ebp - 0x5f7], bl
call mrc_zeromem
mov edx, 8
lea eax, [ebp - 0x5b4]
call mrc_zeromem
mov al, byte [ebp - 0x5f7]
sub esp, 0xc
mov byte [ebp - 0x5af], al
lea eax, [ebp - 0x624]
push eax
mov byte [ebp - 0x5b0], 1
lea ecx, [ebp - 0x5b4]
mov edx, dword [ebp - 0x5b0]
mov eax, 2
mov dword [ebp - 0x5b4], 0
call fcn_fffc8f0f  ; call 0xfffc8f0f
add esp, 0x10
test eax, eax
jne short loc_fffa4f44  ; jne 0xfffa4f44
cmp dword [ebp - 0x624], 0
jne short loc_fffa4f44  ; jne 0xfffa4f44
mov eax, dword [ebp - 0x5b4]
mov edx, eax
mov byte [ebp - 0x5fb], al
and edx, 0x100
shr edx, 8
mov byte [ebp - 0x5fa], dl
mov edx, eax
and edx, 0x200
and eax, 0x400
shr edx, 9
shr eax, 0xa
mov byte [ebp - 0x5f9], dl
mov byte [ebp - 0x5f8], al

loc_fffa4f44:
cmp dword [ebp - 0x624], 0
jne loc_fffa532b  ; jne 0xfffa532b
cmp byte [ebp - 0x5fa], 0
jne short loc_fffa4f70  ; jne 0xfffa4f70
cmp byte [ebp - 0x5f9], 0
jne short loc_fffa4f70  ; jne 0xfffa4f70
cmp byte [ebp - 0x5f8], 0
je loc_fffa532b  ; je 0xfffa532b

loc_fffa4f70:
mov edx, 7
lea eax, [ebp - 0x5f6]
call mrc_zeromem
mov edx, 8
lea eax, [ebp - 0x5b4]
mov byte [ebp - 0x5f0], bl
call mrc_zeromem
mov edx, 8
lea eax, [ebp - 0x5b4]
call mrc_zeromem
mov al, byte [ebp - 0x5f0]
sub esp, 0xc
mov byte [ebp - 0x5af], al
lea eax, [ebp - 0x624]
push eax
mov byte [ebp - 0x5b0], 0x10
lea ecx, [ebp - 0x5b4]
mov edx, dword [ebp - 0x5b0]
mov eax, 2
mov dword [ebp - 0x5b4], 0
call fcn_fffc8f0f  ; call 0xfffc8f0f
add esp, 0x10
test eax, eax
jne loc_fffa532b  ; jne 0xfffa532b
cmp dword [ebp - 0x624], 0
jne short loc_fffa5040  ; jne 0xfffa5040
mov eax, dword [ebp - 0x5b4]
mov ecx, 1
mov edx, eax
mov byte [ebp - 0x5f6], al
and edx, 0x100000
movzx eax, ah
shr edx, 0x14
mov byte [ebp - 0x5f5], dl
lea edx, [ebp - 0x5f4]
call fcn_fffc8dcb  ; call 0xfffc8dcb
mov eax, dword [ebp - 0x5b4]
mov ecx, 1
shr eax, 0x15
lea edx, [ebp - 0x5f2]
call fcn_fffc8d04  ; call 0xfffc8d04

loc_fffa5040:
cmp dword [ebp - 0x624], 0
jne loc_fffa532b  ; jne 0xfffa532b
mov edx, 7
lea eax, [ebp - 0x5ef]
call mrc_zeromem
cmp bl, 1
mov byte [ebp - 0x5e9], bl
jne loc_fffa520e  ; jne 0xfffa520e
mov eax, dword [edi + 0x11]
mov dx, word [eax + 6]
mov byte [ebp - 0x5ef], dl
mov dl, byte [eax + 0xa]
test dl, dl
mov byte [ebp - 0x5ee], dl
jne short loc_fffa508c  ; jne 0xfffa508c
mov dx, word [eax + 4]
jmp short loc_fffa5090  ; jmp 0xfffa5090

loc_fffa508c:
mov dx, word [eax + 2]

loc_fffa5090:
mov word [ebp - 0x5ed], dx
mov ax, word [eax]
mov word [ebp - 0x5eb], ax
xor eax, eax

loc_fffa50a3:
mov dl, byte [ebp + eax - 0x5f6]
cmp byte [ebp + eax - 0x5ef], dl
je loc_fffa51ff  ; je 0xfffa51ff

loc_fffa50b7:
sub esp, 0xc
mov eax, dword [ebp - 0x620]
push 0x3c
call dword [eax]  ; ucall
mov al, byte [ebp - 0x5ee]
mov cl, byte [ebp - 0x5ef]
movsx edx, word [ebp - 0x5eb]
mov byte [ebp - 0x659], al
mov al, byte [ebp - 0x5e9]
mov dword [ebp - 0x658], edx
mov byte [ebp - 0x65a], al
mov edx, 8
lea eax, [ebp - 0x5c4]
mov byte [ebp - 0x668], cl
movzx esi, word [ebp - 0x5ed]
call mrc_zeromem
mov cl, byte [ebp - 0x668]
mov eax, esi
mov byte [ebp - 0x5b4], cl
lea edx, [ebp - 0x5e8]
xor ecx, ecx
mov word [ebp - 0x5e8], 0
call fcn_fffc8dcb  ; call 0xfffc8dcb
movzx edx, word [ebp - 0x5e8]
mov eax, dword [ebp - 0x5b4]
and edx, 0xfff
and eax, 0xfff000ff
shl edx, 8
xor ecx, ecx
or eax, edx
mov dl, byte [ebp - 0x659]
mov dword [ebp - 0x5b4], eax
and edx, 1
mov al, byte [ebp - 0x5b2]
mov word [ebp - 0x5e8], 0
shl edx, 4
and eax, 0xffffffef
or eax, edx
lea edx, [ebp - 0x5e8]
mov byte [ebp - 0x5b2], al
mov eax, dword [ebp - 0x658]
call fcn_fffc8d04  ; call 0xfffc8d04
mov ax, word [ebp - 0x5b2]
mov edx, dword [ebp - 0x5e8]
shl edx, 5
and eax, 0x1f
or eax, edx
mov ecx, 4
mov word [ebp - 0x5b2], ax
lea edx, [ebp - 0x5b4]
lea eax, [ebp - 0x5c4]
call mrc_memcpy
mov dl, byte [ebp - 0x65a]
mov eax, 2
mov byte [ebp - 0x5bf], dl
mov edx, dword [ebp - 0x5c4]
mov byte [ebp - 0x5c0], 0x11
mov dword [ebp - 0x668], edx
mov esi, dword [ebp - 0x5c0]
call fcn_fffc8e6f  ; call 0xfffc8e6f
add esp, 0x10
test eax, eax
mov edx, dword [ebp - 0x668]
jns short loc_fffa5256  ; jns 0xfffa5256
jmp near loc_fffa532b  ; jmp 0xfffa532b

loc_fffa51ff:
inc eax
cmp eax, 7
jne loc_fffa50a3  ; jne 0xfffa50a3
jmp near loc_fffa532b  ; jmp 0xfffa532b

loc_fffa520e:
lea eax, [ebx - 3]
cmp al, 2
ja loc_fffa532b  ; ja 0xfffa532b
cmp bl, 4
mov eax, dword [edi + 0x11]
je short loc_fffa522c  ; je 0xfffa522c
cmp bl, 5
je short loc_fffa5232  ; je 0xfffa5232
mov ax, word [eax + 8]
jmp short loc_fffa5236  ; jmp 0xfffa5236

loc_fffa522c:
mov ax, word [eax + 0xc]
jmp short loc_fffa5236  ; jmp 0xfffa5236

loc_fffa5232:
mov ax, word [eax + 0xe]

loc_fffa5236:
mov word [ebp - 0x5eb], ax
mov cx, word [ebp - 0x5f2]
cmp word [ebp - 0x5eb], cx
jne loc_fffa50b7  ; jne 0xfffa50b7
jmp near loc_fffa532b  ; jmp 0xfffa532b

loc_fffa5256:
mov dword [ebp - 0x5bc], edx
mov ecx, 8
lea edx, [ebp - 0x5bc]
lea eax, [ebp - 0x5e8]
mov dword [ebp - 0x5b8], esi
or byte [ebp - 0x5b5], 0x80
call mrc_memcpy
mov eax, dword [ebp - 0x5e8]
mov edx, dword [ebp - 0x5e4]
mov ecx, 0x150
wrmsr
mov eax, 2
call fcn_fffc8e6f  ; call 0xfffc8e6f
mov eax, dword [ebp - 0x648]
mov edx, dword [ebp - 0x644]
mov ecx, 8
mov dword [ebp - 0x5e8], eax
mov dword [ebp - 0x5e4], edx
lea eax, [ebp - 0x5bc]
lea edx, [ebp - 0x5e8]
call mrc_memcpy
mov eax, 0xa
call fcn_fffc5e98  ; call 0xfffc5e98
mov edx, dword [ebp - 0x648]
mov ecx, dword [ebp - 0x644]
mov dword [ebp - 0x5e8], edx
mov dword [ebp - 0x5e4], ecx
lea edx, [ebp - 0x5e8]
mov ecx, 8
lea eax, [ebp - 0x5b4]
call mrc_memcpy
mov ecx, dword [ebp - 0x5b0]
cmp dword [ebp - 0x5b8], ecx
je short loc_fffa531e  ; je 0xfffa531e
mov eax, dword [ebp - 0x5b4]
cmp dword [ebp - 0x5bc], eax
jne short loc_fffa532b  ; jne 0xfffa532b

loc_fffa531e:
movzx eax, byte [ebp - 0x5b8]
mov dword [ebp - 0x624], eax

loc_fffa532b:
inc ebx
cmp bl, 6
jne loc_fffa4e71  ; jne 0xfffa4e71
jmp near loc_fffa4d92  ; jmp 0xfffa4d92

loc_fffa533a:
mov al, byte [edi + 0xa78]
or eax, 2
mov byte [edi + 0xa78], al

loc_fffa5349:
mov eax, dword [esi + 0xd]
mov edx, dword [ebp - 0x5e8]
mov al, byte [eax]
mov byte [edx + 0x22], al
mov eax, dword [esi + 0xd]
mov al, byte [eax + 1]
mov byte [edx + 0x24], al
mov eax, dword [esi + 0xd]
mov al, byte [eax + 2]
mov byte [edx + 0x26], al
xor eax, eax

loc_fffa536b:
mov edx, dword [ebp - 0x5e8]
mov ecx, dword [edx + eax*4]
cmp ecx, 1
jne short loc_fffa537f  ; jne 0xfffa537f
cmp byte [edx + 0x22], 0
jmp short loc_fffa5393  ; jmp 0xfffa5393

loc_fffa537f:
cmp ecx, 2
jne short loc_fffa538a  ; jne 0xfffa538a
cmp byte [edx + 0x24], 0
jmp short loc_fffa5393  ; jmp 0xfffa5393

loc_fffa538a:
cmp ecx, 3
jne short loc_fffa539c  ; jne 0xfffa539c
cmp byte [edx + 0x26], 0

loc_fffa5393:
jne short loc_fffa539c  ; jne 0xfffa539c
mov dword [edx + eax*4], 0

loc_fffa539c:
inc eax
cmp eax, 8
jne short loc_fffa536b  ; jne 0xfffa536b
mov ebx, dword [ebp - 0x5e8]
mov dword [ebp - 0x5b4], 0
xor ecx, ecx

loc_fffa53b4:
mov eax, dword [ebx + ecx*4]
mov esi, 1
shl esi, cl
inc ecx
mov edx, esi
or byte [ebp + eax - 0x5b4], dl
cmp ecx, 8
jne short loc_fffa53b4  ; jne 0xfffa53b4
xor eax, eax

loc_fffa53cf:
cmp byte [ebx + eax*2 + 0x20], 1
mov dl, al
jne short loc_fffa542d  ; jne 0xfffa542d
movzx ecx, byte [ebx + eax*2 + 0x21]
shl ecx, 0x18
mov dword [ebp - 0x648], ecx
movzx ecx, byte [ebp + eax - 0x5b4]
or ecx, 0x80000000
cmp al, 2
je short loc_fffa540d  ; je 0xfffa540d
cmp al, 3
je short loc_fffa5414  ; je 0xfffa5414
dec dl
mov esi, 0x14
mov edx, 0x20
cmove esi, edx
jmp short loc_fffa5419  ; jmp 0xfffa5419

loc_fffa540d:
mov esi, 0x2c
jmp short loc_fffa5419  ; jmp 0xfffa5419

loc_fffa5414:
mov esi, 0x38

loc_fffa5419:
add esi, edi
mov edx, dword [esi]
and edx, 0xf8ffff01
or edx, dword [ebp - 0x648]
or edx, ecx
mov dword [esi], edx

loc_fffa542d:
inc eax
cmp eax, 4
jne short loc_fffa53cf  ; jne 0xfffa53cf
mov al, byte [edi + 4]
and eax, 0xfffffff8
cmp byte [ebx + 0x22], 1
sete dl
or eax, edx
mov byte [edi + 4], al
sub esp, 0xc
mov eax, dword [ebp - 0x620]
push dword [ebp - 0x640]
mov esi, 0x1a
call dword [eax + 4]  ; ucall
mov ecx, dword [ebp - 0x5e8]
add esp, 0x10
xor eax, eax

loc_fffa5467:
cmp byte [ecx + eax*2 + 0x20], 1
mov dl, al
jne short loc_fffa549a  ; jne 0xfffa549a
cmp al, 2
je short loc_fffa5484  ; je 0xfffa5484
cmp al, 3
je short loc_fffa548b  ; je 0xfffa548b
dec dl
mov ebx, 0x26
cmovne ebx, esi
jmp short loc_fffa5490  ; jmp 0xfffa5490

loc_fffa5484:
mov ebx, 0x32
jmp short loc_fffa5490  ; jmp 0xfffa5490

loc_fffa548b:
mov ebx, 0x3e

loc_fffa5490:
add ebx, edi

loc_fffa5492:
mov dx, word [ebx]
and dl, 2
jne short loc_fffa5492  ; jne 0xfffa5492

loc_fffa549a:
inc eax
cmp eax, 4
jne short loc_fffa5467  ; jne 0xfffa5467
mov eax, dword [ebp - 0x628]
mov eax, dword [eax + 1]
mov edx, dword [eax + 4]
mov eax, dword [edx + 0x5f00]
or eax, 1
mov dword [edx + 0x5f00], eax
mov eax, ref_fffcc904  ; mov eax, 0xfffcc904
call fcn_fffbf91e  ; call 0xfffbf91e
lea eax, [ebp - 0x5e8]
call fcn_fffbf908  ; call 0xfffbf908
test eax, eax
jne short loc_fffa54e7  ; jne 0xfffa54e7
cmp dword [ebp - 0x5e8], 0x11
jne short loc_fffa54e7  ; jne 0xfffa54e7
mov eax, ref_fffcd554  ; mov eax, 0xfffcd554
call fcn_fffbf91e  ; call 0xfffbf91e

loc_fffa54e7:
mov ecx, dword [ebp - 0x640]
push eax
push eax
mov eax, dword [ecx]
push ref_fffcc910  ; push 0xfffcc910
push ecx
call dword [eax + 0x18]  ; ucall
mov dword [esp], ref_fffcc65f  ; mov dword [esp], 0xfffcc65f
call mrc_printk  ; call 0xfffa1253
mov eax, dword [0xff7d7538]
pop edx
pop ecx
mov edx, dword [eax]
push ref_fffcd498  ; push 0xfffcd498
push eax
call dword [edx + 0x18]  ; ucall
mov dword [esp], ref_fffcc688  ; db 'System Agent: Initializing Memory',0x0a,0x00
call mrc_printk  ; call 0xfffa1253
mov eax, dword [0xff7d7538]
call fcn_fffc1b54  ; call 0xfffc1b54
mov edx, 0xfffe
mov eax, ref_fffcd4c4  ; mov eax, 0xfffcd4c4
call fcn_fffa11b3  ; call 0xfffa11b3
add esp, 0x10
test eax, eax
jne short loc_fffa5573  ; jne 0xfffa5573
cmp dword [ebp - 0x20c], 0x11
je short loc_fffa555d  ; je 0xfffa555d
sub esp, 0xc
push ref_fffcc6ab  ; push 0xfffcc6ab
call mrc_printk  ; call 0xfffa1253
add esp, 0x10

loc_fffa555d:
mov eax, dword [ebp - 0x63c]
mov dword [eax + 0x66], 0
mov dword [eax + 0x62], 0
jmp short loc_fffa5585  ; jmp 0xfffa5585

loc_fffa5573:
mov ecx, dword [ebp - 0x63c]
mov edx, dword [eax + 0x18]
add eax, 0x1c
mov dword [ecx + 0x66], edx
mov dword [ecx + 0x62], eax

loc_fffa5585:
sub esp, 0xc
push ref_fffcc6dd  ; push 0xfffcc6dd
call mrc_printk  ; call 0xfffa1253
add esp, 0x10
xor eax, eax
jmp near loc_fffa56a4  ; jmp 0xfffa56a4

loc_fffa559c:
or eax, 0xffffffff
jmp near loc_fffa56a4  ; jmp 0xfffa56a4

loc_fffa55a4:
sub esp, 0xc
mov edx, 0xc088018
push 0
movzx esi, byte [ebp - 0x659]
mov eax, dword [ebp - 0x648]
mov ecx, esi
call fcn_fffa0516  ; call 0xfffa0516
and eax, 0x81ffffff
mov edx, 0xc088018
movzx edi, byte [ebp - 0x65a]
or eax, 0x10000000
mov dword [esp], eax
mov ecx, edi
mov eax, dword [ebp - 0x648]
call fcn_fffa0516  ; call 0xfffa0516
mov ecx, esi
mov edx, 0xc0c8018
mov eax, dword [ebp - 0x648]
mov dword [esp], 0
call fcn_fffa0516  ; call 0xfffa0516
and eax, 0xffefffff
mov ecx, edi
mov dword [esp], eax
mov edx, 0xc0c8018
mov eax, dword [ebp - 0x648]
mov esi, 0xc0c8018
call fcn_fffa0516  ; call 0xfffa0516
add esp, 0x10
jmp near loc_fffa48a6  ; jmp 0xfffa48a6

loc_fffa5628:
xor edx, edx
jmp near loc_fffa4962  ; jmp 0xfffa4962

loc_fffa562f:
mov edx, dword [ebp - 0x640]
sub esp, 0xc
mov eax, dword [edx]
lea edx, [ebp - 0x620]
push edx
push 0
push 0
push ref_fffcc96c  ; push 0xfffcc96c
push dword [ebp - 0x640]
call dword [eax + 0x20]  ; ucall
mov eax, dword [ebp - 0x620]
add esp, 0x14
push dword [ebp - 0x640]
call dword [eax + 8]  ; ucall
mov eax, dword [ebx + 0x84]
and eax, 0xfffffff0
or eax, 2
mov dword [ebx + 0x84], eax
mov dl, 1
add esp, 0x10
jmp near loc_fffa4ce2  ; jmp 0xfffa4ce2

loc_fffa5681:
mov eax, dword [ebx + 0x910]
and ah, 0xc3
mov dword [ebx + 0x910], eax
mov eax, dword [ebx + 0x930]
and ah, 0xc3
mov dword [ebx + 0x930], eax
jmp near loc_fffa4564  ; jmp 0xfffa4564

loc_fffa56a4:
lea esp, [ebp - 0xc]
pop ebx
pop esi
pop edi
pop ebp
ret
