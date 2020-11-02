/* SPDX-License-Identifier: GPL-2.0-only */

#include <string.h>
#include <acpi/acpi.h>
#include <cbmem.h>
#include <console/console.h>
#include <console/streams.h>
#include <program_loading.h>
#include <rmodule.h>
#include <stage_cache.h>
#include <soc/pei_data.h>
#include <soc/pei_wrapper.h>
#include <soc/pm.h>
#include <soc/ramstage.h>

void broadwell_run_reference_code(void)
{
	int ret, dummy;
	struct pei_data pei_data;

	memset(&pei_data, 0, sizeof(pei_data));
	mainboard_fill_pei_data(&pei_data);
	broadwell_fill_pei_data(&pei_data);

	pei_data.boot_mode = acpi_is_wakeup_s3() ? ACPI_S3 : 0;
	pei_data.saved_data = (void *) &dummy;

	extern int ABI_X86 refcode_entry(struct pei_data *pei_data);

	/* Call into reference code. */
	ret = refcode_entry(&pei_data);
	if (ret != 0) {
		printk(BIOS_ERR, "Reference code returned %d\n", ret);
		return;
	}
}
