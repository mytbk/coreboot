struct _PEI_EHCI {
	uint8_t enable;
	uint8_t location;
	uint16_t length;
	uint8_t f4;
	uint8_t f5;
} __packed;

typedef struct _PEI_EHCI PEI_EHCI;

struct _PEI_USB
{
	uint8_t v0; // 0x0
	PEI_EHCI ehci_settings[14]; // 0x1
	uint8_t xhci_resume_info[23]; // 0x55
	uint32_t ehci_oc[14]; // 0x6c
	uint32_t xhci_oc[6]; // 0xa4
	uint8_t unk;
	uint8_t xhci_en[6]; // 0xbd
} __packed;

typedef struct _PEI_USB PEI_USB;

struct _EFI_USB_PPI
{
	uint8_t v0;
	PEI_USB *usb_pei_data;
	uint8_t v1;
	uint32_t ehci_bar0;
	uint32_t port;
	uint32_t ehci_bar1;
} __packed;
typedef struct _EFI_USB_PPI EFI_USB_PPI;
