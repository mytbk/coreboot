#include <stdint.h>
#include "Smbus.h"

#define MRCABI __attribute((regparm(3)))

int dummy_func(void);
void dmi_check_link(void);
void __attribute((regparm(2))) rtc_wait(void *, uint16_t);
uint8_t __attribute((regparm(1))) pci_setup_bridge(uint8_t bus);
int MRCABI do_smbus_op(EFI_SMBUS_OPERATION op, u32 addr_desc, void *buf, int *retcode);
