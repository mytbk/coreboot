#include <stdint.h>

int dummy_func(void);
void dmi_check_link(void);
void __attribute((regparm(2))) rtc_wait(void *, uint16_t);
