int __attribute((regparm(3))) mrc_pch_iobp_read(u32 rcba, u32 addr, u32 *data);
int __attribute((regparm(3))) mrc_pch_iobp_update(u32 rcba, u32 addr, u32 andv, u32 orv);
