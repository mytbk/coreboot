#include "mrc_sku.h"

uint8_t nb_usb2_ports(void)
{
	int t = mrc_sku_type();
	if (t > 2)
		return 0;
	if (t == 1) /* t = 1, not low power */
		return 14;
	else /* t = 2, low power */
		return 8;
}

uint8_t nb_usb3_ports(void)
{
	int t = mrc_sku_type();
	if (t > 2)
		return 0;
	if (t == 1)
		return 8;
	else
		return 6;
}
