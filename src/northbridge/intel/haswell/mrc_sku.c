#include <stdint.h>

int mrc_sku_type(void);

uint8_t mrc_sku_5d89(void);
uint8_t mrc_sku_5da5(void);

uint8_t mrc_sku_5d89(void)
{
	int t = mrc_sku_type();
	if (t > 2)
		return 0;
	if (t == 1)
		return 0x0e;
	else
		return 8;
}

uint8_t mrc_sku_5da5(void)
{
	int t = mrc_sku_type();
	if (t > 2)
		return 0;
	if (t == 1)
		return 8;
	else
		return 6;
}
