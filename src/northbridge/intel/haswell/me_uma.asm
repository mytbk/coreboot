global PchMeUmaDesc
global gPchMeUmaPpiGuid

extern get_uma_size
extern fcn_fffbe070
extern fcn_fffbe14d
extern fcn_fffbe110
extern fcn_fffbdf70

PchMeUmaDesc:
dd 0x80000010
dd gPchMeUmaPpiGuid
dd ref_fffcd514

gPchMeUmaPpiGuid:
dd 0x8c376010
dd 0x4d7d2400
dd 0x859d7bb4
dd 0xd1c9f31d

ref_fffcd514:
dd get_uma_size
dd fcn_fffbe070
dd fcn_fffbe14d
dd fcn_fffbe110
