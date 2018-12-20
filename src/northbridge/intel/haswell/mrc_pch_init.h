#include <stdint.h>

typedef struct {
	uint32_t address;
	uint32_t andv;
	uint32_t orv;
} iobp_upd_st;

static const iobp_upd_st iobp0_0[] = {
	{ 0xea008008, 0x00ffffff, 0x1c000000 },
	{ 0xea00800c, 0xffff8000, 0x00002b50 },
	{ 0xea0024a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0026a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0008a4, 0xffcf00ff, 0x00308300 },
	{ 0xea000aa4, 0xffcf00ff, 0x00308300 },
	{ 0xea0024ac, 0xffffffcf, 0x00000020 },
	{ 0xea0026ac, 0xffffffcf, 0x00000020 },
	{ 0xea0008ac, 0xffffffcf, 0x00000020 },
	{ 0xea000aac, 0xffffffcf, 0x00000020 },
	{ 0xea002488, 0xffff00ff, 0x00008000 },
	{ 0xea002688, 0xffff00ff, 0x00008000 },
	{ 0xea000888, 0xffff00ff, 0x00008000 },
	{ 0xea000a88, 0xffff00ff, 0x00008000 },
	{ 0xea002494, 0x7fffffff, 0x80000000 },
	{ 0xea002694, 0x7fffffff, 0x80000000 },
	{ 0xea000894, 0x7fffffff, 0x80000000 },
	{ 0xea000a94, 0x7fffffff, 0x80000000 },
	{ 0xea002540, 0xff000000, 0x00180918 },
	{ 0xea002740, 0xff000000, 0x00180918 },
	{ 0xea000940, 0xff000000, 0x00180918 },
	{ 0xea000b40, 0xff000000, 0x00180918 },
	{ 0xea002544, 0xff000000, 0x00140918 },
	{ 0xea002744, 0xff000000, 0x00140918 },
	{ 0xea000944, 0xff000000, 0x00140918 },
	{ 0xea000b44, 0xff000000, 0x00140918 },
	{ 0xea002548, 0xff000000, 0x00140918 },
	{ 0xea002748, 0xff000000, 0x00140918 },
	{ 0xea000948, 0xff000000, 0x00140918 },
	{ 0xea000b48, 0xff000000, 0x00140918 },
	{ 0xea002550, 0xc0ffffff, 0x02000000 },
	{ 0xea002750, 0xc0ffffff, 0x02000000 },
	{ 0xea000950, 0xc0ffffff, 0x02000000 },
	{ 0xea000b50, 0xc0ffffff, 0x02000000 },
	{ 0xea002554, 0xffc0ffff, 0x00020000 },
	{ 0xea002754, 0xffc0ffff, 0x00020000 },
	{ 0xea000954, 0xffc0ffff, 0x00020000 },
	{ 0xea000b54, 0xffc0ffff, 0x00020000 },
	{ 0xea002410, 0x0000ffff, 0x0d510000 },
	{ 0xea002610, 0x0000ffff, 0x0d510000 },
	{ 0xea000810, 0x0000ffff, 0x0d510000 },
	{ 0xea000a10, 0x0000ffff, 0x0d510000 },
	{ 0xea002400, 0x30fcffff, 0xcf030000 },
	{ 0xea002600, 0x30fcffff, 0xcf030000 },
	{ 0xea000800, 0x30fcffff, 0xcf030000 },
	{ 0xea000a00, 0x30fcffff, 0xcf030000 },
	{ 0xea002408, 0x00039ef7, 0xea6c6108 },
	{ 0xea002608, 0x00039ef7, 0xea6c6108 },
	{ 0xea000808, 0x00039ef7, 0xea6c6108 },
	{ 0xea000a08, 0x00039ef7, 0xea6c6108 },
	{ 0xea002418, 0x0000fcff, 0x38250100 },
	{ 0xea002618, 0x0000fcff, 0x38250100 },
	{ 0xea000818, 0x0000fcff, 0x38250100 },
	{ 0xea000a18, 0x0000fcff, 0x38250100 },
	{ 0xea002428, 0x00e0ffff, 0x580e0000 },
	{ 0xea002628, 0x00e0ffff, 0x580e0000 },
	{ 0xea000828, 0x00e0ffff, 0x580e0000 },
	{ 0xea000a28, 0x00e0ffff, 0x580e0000 },
	{ 0xea002438, 0xfffffff0, 0x0000000d },
	{ 0xea002638, 0xfffffff0, 0x0000000d },
	{ 0xea000838, 0xfffffff0, 0x0000000d },
	{ 0xea000a38, 0xfffffff0, 0x0000000d },
	{ 0xea002440, 0xe0ffffff, 0x01000000 },
	{ 0xea002640, 0xe0ffffff, 0x01000000 },
	{ 0xea000840, 0xe0ffffff, 0x01000000 },
	{ 0xea000a40, 0xe0ffffff, 0x01000000 },
	{ 0xea00242c, 0xfffdffff, 0x00020000 },
	{ 0xea00262c, 0xfffdffff, 0x00020000 },
	{ 0xea00082c, 0xfffdffff, 0x00020000 },
	{ 0xea000a2c, 0xfffdffff, 0x00020000 },
	{ 0xea00241c, 0xffff83ff, 0x00002400 },
	{ 0xea00261c, 0xffff83ff, 0x00002400 },
	{ 0xea00081c, 0xffff83ff, 0x00002400 },
	{ 0xea000a1c, 0xffff83ff, 0x00002400 },
	{ 0xea002500, 0xffff1fc1, 0x00004008 },
	{ 0xea002700, 0xffff1fc1, 0x00004008 },
	{ 0xea000900, 0xffff1fc1, 0x00004008 },
	{ 0xea000b00, 0xffff1fc1, 0x00004008 },
	{ 0xea00257c, 0xfff0c0ff, 0x00003f00 },
	{ 0xea00277c, 0xfff0c0ff, 0x00003f00 },
	{ 0xea00097c, 0xfff0c0ff, 0x00003f00 },
	{ 0xea000b7c, 0xfff0c0ff, 0x00003f00 },
};
static const iobp_upd_st iobp0_1[] = {
	{ 0xea008008, 0x00ffffff, 0x1c000000 },
	{ 0xea002408, 0x00039ef7, 0xea6c6108 },
	{ 0xea002608, 0x00039ef7, 0xea6c6108 },
	{ 0xea000808, 0x00039ef7, 0xea6c6108 },
	{ 0xea000a08, 0x00039ef7, 0xea6c6108 },
	{ 0xea002438, 0xfffffff0, 0x0000000d },
	{ 0xea002638, 0xfffffff0, 0x0000000d },
	{ 0xea000838, 0xfffffff0, 0x0000000d },
	{ 0xea000a38, 0xfffffff0, 0x0000000d },
	{ 0xea002440, 0xe0ffffff, 0x01000000 },
	{ 0xea002640, 0xe0ffffff, 0x01000000 },
	{ 0xea000840, 0xe0ffffff, 0x01000000 },
	{ 0xea000a40, 0xe0ffffff, 0x01000000 },
	{ 0xea002410, 0x0000ffff, 0x0d510000 },
	{ 0xea002610, 0x0000ffff, 0x0d510000 },
	{ 0xea000810, 0x0000ffff, 0x0d510000 },
	{ 0xea000a10, 0x0000ffff, 0x0d510000 },
	{ 0xea00242c, 0xfffdf7ff, 0x00020000 },
	{ 0xea00262c, 0xfffdf7ff, 0x00020000 },
	{ 0xea00082c, 0xfffdf7ff, 0x00020000 },
	{ 0xea000a2c, 0xfffdf7ff, 0x00020000 },
	{ 0xea002418, 0x0000fcff, 0x38250100 },
	{ 0xea002618, 0x0000fcff, 0x38250100 },
	{ 0xea000818, 0x0000fcff, 0x38250100 },
	{ 0xea000a18, 0x0000fcff, 0x38250100 },
	{ 0xea002400, 0x30fcffff, 0xcf030000 },
	{ 0xea002600, 0x30fcffff, 0xcf030000 },
	{ 0xea000800, 0x30fcffff, 0xcf030000 },
	{ 0xea000a00, 0x30fcffff, 0xcf030000 },
	{ 0xea002428, 0x00e0ffff, 0x580e0000 },
	{ 0xea002628, 0x00e0ffff, 0x580e0000 },
	{ 0xea000828, 0x00e0ffff, 0x580e0000 },
	{ 0xea000a28, 0x00e0ffff, 0x580e0000 },
	{ 0xea00241c, 0xffff83ff, 0x00002400 },
	{ 0xea00261c, 0xffff83ff, 0x00002400 },
	{ 0xea00081c, 0xffff83ff, 0x00002400 },
	{ 0xea000a1c, 0xffff83ff, 0x00002400 },
	{ 0xea00248c, 0xff00ffff, 0x00800000 },
	{ 0xea00268c, 0xff00ffff, 0x00800000 },
	{ 0xea00088c, 0xff00ffff, 0x00800000 },
	{ 0xea000a8c, 0xff00ffff, 0x00800000 },
	{ 0xea0024a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0026a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0008a4, 0xffcf00ff, 0x00308300 },
	{ 0xea000aa4, 0xffcf00ff, 0x00308300 },
	{ 0xea0024ac, 0xffffffcf, 0x00000020 },
	{ 0xea0026ac, 0xffffffcf, 0x00000020 },
	{ 0xea0008ac, 0xffffffcf, 0x00000020 },
	{ 0xea000aac, 0xffffffcf, 0x00000020 },
	{ 0xea002540, 0xff000000, 0x00140718 },
	{ 0xea002740, 0xff000000, 0x00140718 },
	{ 0xea000940, 0xff000000, 0x00140718 },
	{ 0xea000b40, 0xff000000, 0x00140718 },
	{ 0xea002544, 0xff000000, 0x0014091b },
	{ 0xea002744, 0xff000000, 0x0014091b },
	{ 0xea000944, 0xff000000, 0x0014091b },
	{ 0xea000b44, 0xff000000, 0x0014091b },
	{ 0xea002548, 0xff000000, 0x00140918 },
	{ 0xea002748, 0xff000000, 0x00140918 },
	{ 0xea000948, 0xff000000, 0x00140918 },
	{ 0xea000b48, 0xff000000, 0x00140918 },
	{ 0xea00257c, 0xfcffffff, 0x03000000 },
	{ 0xea00277c, 0xfcffffff, 0x03000000 },
	{ 0xea00097c, 0xfcffffff, 0x03000000 },
	{ 0xea000b7c, 0xfcffffff, 0x03000000 },
	{ 0xea002578, 0xffffe0ff, 0x00001800 },
	{ 0xea002778, 0xffffe0ff, 0x00001800 },
	{ 0xea000978, 0xffffe0ff, 0x00001800 },
	{ 0xea000b78, 0xffffe0ff, 0x00001800 },
};
static const iobp_upd_st * iobp0_ref[] = { iobp0_0, iobp0_1, iobp0_1, iobp0_1 }; // ref_fffcc330
static const uint8_t iobp0_sz[] = { 82, 69, 69, 69 }; // ref_fffcc32c

static const iobp_upd_st iobp1_0[] = {
	{ 0xea0020a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0022a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0020ac, 0xffffffcf, 0x00000020 },
	{ 0xea0022ac, 0xffffffcf, 0x00000020 },
	{ 0xea002088, 0xffff00ff, 0x00008000 },
	{ 0xea002288, 0xffff00ff, 0x00008000 },
	{ 0xea002094, 0x7fffffff, 0x80000000 },
	{ 0xea002294, 0x7fffffff, 0x80000000 },
	{ 0xea002140, 0xff000000, 0x00180918 },
	{ 0xea002340, 0xff000000, 0x00180918 },
	{ 0xea002144, 0xff000000, 0x00140918 },
	{ 0xea002344, 0xff000000, 0x00140918 },
	{ 0xea002148, 0xff000000, 0x00140918 },
	{ 0xea002348, 0xff000000, 0x00140918 },
	{ 0xea002150, 0xc0ffffff, 0x02000000 },
	{ 0xea002350, 0xc0ffffff, 0x02000000 },
	{ 0xea002154, 0xffc0ffff, 0x00020000 },
	{ 0xea002354, 0xffc0ffff, 0x00020000 },
	{ 0xea002010, 0x0000ffff, 0x0d510000 },
	{ 0xea002210, 0x0000ffff, 0x0d510000 },
	{ 0xea002000, 0x30fcffff, 0xcf030000 },
	{ 0xea002200, 0x30fcffff, 0xcf030000 },
	{ 0xea002008, 0x00039ef7, 0xea6c6108 },
	{ 0xea002208, 0x00039ef7, 0xea6c6108 },
	{ 0xea002018, 0x0000fcff, 0x38250100 },
	{ 0xea002218, 0x0000fcff, 0x38250100 },
	{ 0xea002028, 0x00e0ffff, 0x580e0000 },
	{ 0xea002228, 0x00e0ffff, 0x580e0000 },
	{ 0xea002038, 0xfffffff0, 0x0000000d },
	{ 0xea002238, 0xfffffff0, 0x0000000d },
	{ 0xea002040, 0xe0ffffff, 0x01000000 },
	{ 0xea002240, 0xe0ffffff, 0x01000000 },
	{ 0xea00202c, 0xfffdf8ff, 0x00020100 },
	{ 0xea00222c, 0xfffdf8ff, 0x00020100 },
	{ 0xea00201c, 0xffff83ff, 0x00002400 },
	{ 0xea00221c, 0xffff83ff, 0x00002400 },
	{ 0xea002100, 0xffff1fc1, 0x00004008 },
	{ 0xea002300, 0xffff1fc1, 0x00004008 },
	{ 0xea00217c, 0xfff0c0ff, 0x00003f00 },
	{ 0xea00237c, 0xfff0c0ff, 0x00003f00 },
};
static const iobp_upd_st iobp1_1[] = {
	{ 0xea002008, 0x00039ef7, 0xea6c6108 },
	{ 0xea002208, 0x00039ef7, 0xea6c6108 },
	{ 0xea002038, 0xfffffff0, 0x0000000d },
	{ 0xea002238, 0xfffffff0, 0x0000000d },
	{ 0xea00202c, 0xfffdf0ff, 0x00020100 },
	{ 0xea00222c, 0xfffdf0ff, 0x00020100 },
	{ 0xea002040, 0xe0ffffff, 0x01000000 },
	{ 0xea002240, 0xe0ffffff, 0x01000000 },
	{ 0xea002010, 0x0000ffff, 0x0d510000 },
	{ 0xea002210, 0x0000ffff, 0x0d510000 },
	{ 0xea002018, 0x0000fcff, 0x38250100 },
	{ 0xea002218, 0x0000fcff, 0x38250100 },
	{ 0xea002000, 0x30fcffff, 0xcf030000 },
	{ 0xea002200, 0x30fcffff, 0xcf030000 },
	{ 0xea002028, 0x00e0ffff, 0x580e0000 },
	{ 0xea002228, 0x00e0ffff, 0x580e0000 },
	{ 0xea00201c, 0xffff83ff, 0x00002400 },
	{ 0xea00221c, 0xffff83ff, 0x00002400 },
	{ 0xea00208c, 0xff00ffff, 0x00800000 },
	{ 0xea00228c, 0xff00ffff, 0x00800000 },
	{ 0xea0020a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0022a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0020ac, 0xffffffcf, 0x00000020 },
	{ 0xea0022ac, 0xffffffcf, 0x00000020 },
	{ 0xea002140, 0xff000000, 0x00140718 },
	{ 0xea002340, 0xff000000, 0x00140718 },
	{ 0xea002144, 0xff000000, 0x0014091b },
	{ 0xea002344, 0xff000000, 0x0014091b },
	{ 0xea002148, 0xff000000, 0x00140918 },
	{ 0xea002348, 0xff000000, 0x00140918 },
	{ 0xea00217c, 0xfcffffff, 0x03000000 },
	{ 0xea00237c, 0xfcffffff, 0x03000000 },
	{ 0xea002178, 0xffffe0ff, 0x00001800 },
	{ 0xea002378, 0xffffe0ff, 0x00001800 },
};
static const iobp_upd_st iobp1_2[] = {
	{ 0xea008008, 0x00ffffff, 0x1c000000 },
	{ 0xea002008, 0x00039ef7, 0xea6c6108 },
	{ 0xea002208, 0x00039ef7, 0xea6c6108 },
	{ 0xea002408, 0x00039ef7, 0xea6c6108 },
	{ 0xea002608, 0x00039ef7, 0xea6c6108 },
	{ 0xea002038, 0xfffffff0, 0x0000000d },
	{ 0xea002238, 0xfffffff0, 0x0000000d },
	{ 0xea002438, 0xfffffff0, 0x0000000d },
	{ 0xea002638, 0xfffffff0, 0x0000000d },
	{ 0xea00202c, 0xfffdf0ff, 0x00020100 },
	{ 0xea00222c, 0xfffdf0ff, 0x00020100 },
	{ 0xea00242c, 0xfffdf0ff, 0x00020100 },
	{ 0xea00262c, 0xfffdf0ff, 0x00020100 },
	{ 0xea002040, 0xe0ffffff, 0x01000000 },
	{ 0xea002240, 0xe0ffffff, 0x01000000 },
	{ 0xea002440, 0xe0ffffff, 0x01000000 },
	{ 0xea002640, 0xe0ffffff, 0x01000000 },
	{ 0xea002010, 0x0000ffff, 0x55510000 },
	{ 0xea002210, 0x0000ffff, 0x55510000 },
	{ 0xea002410, 0x0000ffff, 0x55510000 },
	{ 0xea002610, 0x0000ffff, 0x55510000 },
	{ 0xea002150, 0xc0ffffff, 0x02000000 },
	{ 0xea002350, 0xc0ffffff, 0x02000000 },
	{ 0xea002550, 0xc0ffffff, 0x02000000 },
	{ 0xea002750, 0xc0ffffff, 0x02000000 },
	{ 0xea002154, 0xffc0ffff, 0x00020000 },
	{ 0xea002354, 0xffc0ffff, 0x00020000 },
	{ 0xea002554, 0xffc0ffff, 0x00020000 },
	{ 0xea002754, 0xffc0ffff, 0x00020000 },
	{ 0xea002140, 0xff000000, 0x00140718 },
	{ 0xea002340, 0xff000000, 0x00140718 },
	{ 0xea002540, 0xff000000, 0x00140718 },
	{ 0xea002740, 0xff000000, 0x00140718 },
	{ 0xea002144, 0xff000000, 0x0014091b },
	{ 0xea002344, 0xff000000, 0x0014091b },
	{ 0xea002544, 0xff000000, 0x0014091b },
	{ 0xea002744, 0xff000000, 0x0014091b },
	{ 0xea002148, 0xff000000, 0x00140918 },
	{ 0xea002348, 0xff000000, 0x00140918 },
	{ 0xea002548, 0xff000000, 0x00140918 },
	{ 0xea002748, 0xff000000, 0x00140918 },
	{ 0xea00217c, 0xfcffffff, 0x03000000 },
	{ 0xea00237c, 0xfcffffff, 0x03000000 },
	{ 0xea00257c, 0xfcffffff, 0x03000000 },
	{ 0xea00277c, 0xfcffffff, 0x03000000 },
	{ 0xea00208c, 0xff00ffff, 0x00800000 },
	{ 0xea00228c, 0xff00ffff, 0x00800000 },
	{ 0xea00248c, 0xff00ffff, 0x00800000 },
	{ 0xea00268c, 0xff00ffff, 0x00800000 },
	{ 0xea0020a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0022a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0024a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0026a4, 0xffcf00ff, 0x00308300 },
	{ 0xea0020ac, 0xffffffcf, 0x00000020 },
	{ 0xea0022ac, 0xffffffcf, 0x00000020 },
	{ 0xea0024ac, 0xffffffcf, 0x00000020 },
	{ 0xea0026ac, 0xffffffcf, 0x00000020 },
	{ 0xea002018, 0x0000fcff, 0x38250100 },
	{ 0xea002218, 0x0000fcff, 0x38250100 },
	{ 0xea002418, 0x0000fcff, 0x38250100 },
	{ 0xea002618, 0x0000fcff, 0x38250100 },
	{ 0xea002000, 0x30fcffff, 0xcf030000 },
	{ 0xea002200, 0x30fcffff, 0xcf030000 },
	{ 0xea002400, 0x30fcffff, 0xcf030000 },
	{ 0xea002600, 0x30fcffff, 0xcf030000 },
	{ 0xea002028, 0x00e0ffff, 0x580e0000 },
	{ 0xea002228, 0x00e0ffff, 0x580e0000 },
	{ 0xea002428, 0x00e0ffff, 0x580e0000 },
	{ 0xea002628, 0x00e0ffff, 0x580e0000 },
	{ 0xea00201c, 0xffff83ff, 0x00002400 },
	{ 0xea00221c, 0xffff83ff, 0x00002400 },
	{ 0xea00241c, 0xffff83ff, 0x00002400 },
	{ 0xea00261c, 0xffff83ff, 0x00002400 },
	{ 0xea002178, 0xffffe0ff, 0x00001800 },
	{ 0xea002378, 0xffffe0ff, 0x00001800 },
	{ 0xea002578, 0xffffe0ff, 0x00001800 },
	{ 0xea002778, 0xffffe0ff, 0x00001800 },
};
static const iobp_upd_st * iobp1_ref[] = { iobp1_0, iobp1_1, iobp1_1, iobp1_1, iobp1_2, iobp1_2, iobp1_2 }; // ref_fffcc348
static const uint8_t iobp1_sz[] = { 40, 34, 34, 34, 77, 77, 77 }; // ref_fffcc340

static const iobp_upd_st iobp2_0[] = {
	{ 0xea002490, 0xffff0000, 0x00004c5a },
	{ 0xea002690, 0xffff0000, 0x00004c5a },
	{ 0xea000890, 0xffff0000, 0x00004c5a },
	{ 0xea000a90, 0xffff0000, 0x00004c5a },
	{ 0xea00248c, 0xff00ffff, 0x00800000 },
	{ 0xea00268c, 0xff00ffff, 0x00800000 },
	{ 0xea00088c, 0xff00ffff, 0x00800000 },
	{ 0xea000a8c, 0xff00ffff, 0x00800000 },
};
static const iobp_upd_st iobp2_1[] = {
	{ 0xea002550, 0xc0ffffff, 0x02000000 },
	{ 0xea002750, 0xc0ffffff, 0x02000000 },
	{ 0xea000950, 0xc0ffffff, 0x02000000 },
	{ 0xea000b50, 0xc0ffffff, 0x02000000 },
	{ 0xea002554, 0xffc0ffff, 0x00020000 },
	{ 0xea002754, 0xffc0ffff, 0x00020000 },
	{ 0xea000954, 0xffc0ffff, 0x00020000 },
	{ 0xea000b54, 0xffc0ffff, 0x00020000 },
	{ 0xea002490, 0xffff0000, 0x00004c5a },
	{ 0xea002690, 0xffff0000, 0x00004c5a },
	{ 0xea000890, 0xffff0000, 0x00004c5a },
	{ 0xea000a90, 0xffff0000, 0x00004c5a },
};
static const iobp_upd_st * iobp2_ref[] = { iobp2_0, iobp2_1, iobp2_1, iobp2_1 } // ref_fffcc368
static const uint8_t iobp2_sz[] = { 8, 12, 12, 12 }; // ref_fffcc364


static const iobp_upd_st iobp3_0[] = {
	{ 0xea002090, 0xffff0000, 0x00004c5a },
	{ 0xea002290, 0xffff0000, 0x00004c5a },
	{ 0xea00208c, 0xff00ffff, 0x00800000 },
	{ 0xea00228c, 0xff00ffff, 0x00800000 },
};
static const iobp_upd_st iobp3_1[] = {
	{ 0xea002150, 0xc0ffffff, 0x02000000 },
	{ 0xea002350, 0xc0ffffff, 0x02000000 },
	{ 0xea002154, 0xffc0ffff, 0x00020000 },
	{ 0xea002354, 0xffc0ffff, 0x00020000 },
	{ 0xea002090, 0xffff0000, 0x00004c5a },
	{ 0xea002290, 0xffff0000, 0x00004c5a },
};
static const iobp_upd_st iobp3_2[] = {
	{ 0xea002090, 0xffff0000, 0x00004c5a },
	{ 0xea002290, 0xffff0000, 0x00004c5a },
	{ 0xea002490, 0xffff0000, 0x00004c5a },
	{ 0xea002690, 0xffff0000, 0x00004c5a },
};
static const iobp_upd_st * iobp3_ref[] = { iobp3_0, iobp3_1, iobp3_1, iobp3_1, iobp3_2, iobp3_2, iobp3_2 } // ref_fffcc380
static const uint8_t iobp3_sz[] = { 4, 6, 6, 6, 4, 4, 4 }; // ref_fffcc378


static const iobp_upd_st iobp4_0[] = {
	{ 0xea002490, 0xffff0000, 0x00003e67 },
	{ 0xea002690, 0xffff0000, 0x00003e67 },
	{ 0xea000890, 0xffff0000, 0x00003e67 },
	{ 0xea000a90, 0xffff0000, 0x00003e67 },
	{ 0xea00248c, 0xff00ffff, 0x00800000 },
	{ 0xea00268c, 0xff00ffff, 0x00800000 },
	{ 0xea00088c, 0xff00ffff, 0x00800000 },
	{ 0xea000a8c, 0xff00ffff, 0x00800000 },
};
static const iobp_upd_st iobp4_1[] = {
	{ 0xea002550, 0xc0ffffff, 0x02000000 },
	{ 0xea002750, 0xc0ffffff, 0x02000000 },
	{ 0xea000950, 0xc0ffffff, 0x02000000 },
	{ 0xea000b50, 0xc0ffffff, 0x02000000 },
	{ 0xea002554, 0xffc0ffff, 0x00020000 },
	{ 0xea002754, 0xffc0ffff, 0x00020000 },
	{ 0xea000954, 0xffc0ffff, 0x00020000 },
	{ 0xea000b54, 0xffc0ffff, 0x00020000 },
	{ 0xea002490, 0xffff0000, 0x00003e67 },
	{ 0xea002690, 0xffff0000, 0x00003e67 },
	{ 0xea000890, 0xffff0000, 0x00003e67 },
	{ 0xea000a90, 0xffff0000, 0x00003e67 },
};
static const iobp_upd_st * iobp4_ref[] = { iobp4_0, iobp4_1, iobp4_1, iobp4_1 } // ref_fffcc3a0
static const uint8_t iobp4_sz[] = { 8, 12, 12, 12 }; // ref_fffcc39c

static const iobp_upd_st iobp5_0[] = {
	{ 0xea002090, 0xffff0000, 0x00003e67 },
	{ 0xea002290, 0xffff0000, 0x00003e67 },
	{ 0xea00208c, 0xff00ffff, 0x00800000 },
	{ 0xea00228c, 0xff00ffff, 0x00800000 },
};
static const iobp_upd_st iobp5_1[] = {
	{ 0xea002150, 0xc0ffffff, 0x02000000 },
	{ 0xea002350, 0xc0ffffff, 0x02000000 },
	{ 0xea002154, 0xffc0ffff, 0x00020000 },
	{ 0xea002354, 0xffc0ffff, 0x00020000 },
	{ 0xea002090, 0xffff0000, 0x00003e67 },
	{ 0xea002290, 0xffff0000, 0x00003e67 },
};
static const iobp_upd_st iobp5_2[] = {
	{ 0xea002090, 0xffff0000, 0x00003e67 },
	{ 0xea002290, 0xffff0000, 0x00003e67 },
	{ 0xea002490, 0xffff0000, 0x00003e67 },
	{ 0xea002690, 0xffff0000, 0x00003e67 },
};
static const iobp_upd_st * iobp5_ref[] = { iobp5_0, iobp5_1, iobp5_1, iobp5_1, iobp5_2, iobp5_2, iobp5_2 } // ref_fffcc3b8
static const uint8_t iobp5_sz[] = { 4, 6, 6, 6, 4, 4, 4 }; // ref_fffcc3b0
