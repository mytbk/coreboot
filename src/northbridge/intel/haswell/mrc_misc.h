#include <stdint.h>
#include "Smbus.h"

#define MRCABI __attribute((regparm(3)))

int dummy_func(void);
void dmi_check_link(void);
void __attribute((regparm(2))) rtc_wait(void *, uint16_t);
uint8_t __attribute((regparm(1))) pci_setup_bridge(uint8_t bus);
int MRCABI do_smbus_op(EFI_SMBUS_OPERATION op, u32 addr_desc, void *buf, int *retcode);
uint64_t MRCABI
fcn_fffb5038(void *ram_data,uint32_t *param_2,uint8_t *param_3,uint32_t *param_4);
uint64_t udiv64(uint64_t, uint64_t);

int fcn_fffaa6af(void *ram_data);
int fcn_fffa78a0(void *ramdata);
