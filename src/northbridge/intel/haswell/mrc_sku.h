#include <stdint.h>

int mrc_sku_type(void);
uint8_t nb_usb2_ports(void);
uint8_t nb_usb3_ports(void);
uint8_t mrc_pch_revision(void);
int is_desktop_pch(uint16_t did);
int is_mobile_pch(uint16_t did);
