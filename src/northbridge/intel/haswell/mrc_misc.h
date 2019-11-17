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

typedef int (*callback_t)(void *);
typedef int (*callback3_t)(void *, void *, void *);

#define DECL_CB1(f) int f(void *)
#define DECL_CB3(f) int f(void *, void *, void *)

DECL_CB3(fcn_fffbd356);
DECL_CB3(fcn_fffbd30a);
DECL_CB3(fcn_fffbd1e7);
DECL_CB3(fcn_fffbd184);
DECL_CB3(fcn_fffbd1b3);
DECL_CB3(fcn_fffbd106);
DECL_CB3(fcn_fffbd29a);
DECL_CB3(fcn_fffbd213);
DECL_CB3(fcn_fffbd0e4);
DECL_CB3(fcn_fffbd0c8);
DECL_CB3(fcn_fffbd046);
DECL_CB3(fcn_fffbd01d);

DECL_CB1(fcn_fffbce60);
DECL_CB1(fcn_fffb73ef);
DECL_CB1(fcn_fffb6f52);
DECL_CB1(fcn_fffbcc31);
DECL_CB1(fcn_fffbc869);
DECL_CB1(fcn_fffbc643);
DECL_CB1(fcn_fffbc441);
DECL_CB1(fcn_fffb7633);
DECL_CB1(fcn_fffbc277);
DECL_CB1(fcn_fffbc075);
DECL_CB1(fcn_fffbbe9c);
DECL_CB1(fcn_fffbca4d);
DECL_CB1(fcn_fffbbcd4);
DECL_CB1(fcn_fffbbb0c);
DECL_CB1(fcn_fffb7e5c);
DECL_CB1(fcn_fffb7c94);
DECL_CB1(fcn_fffb7acc);
DECL_CB1(fcn_fffb7866);

int fcn_fffb8689(void *ramdata);
int fcn_fffa7a1c(void *ramdata);
int fcn_fffc7720(void *ramdata);
int MRCABI wait_5030(void *ramdata);
int MRCABI wait_5084(void *ramdata);
int fcn_fffa7e78(void *ramdata);
int fcn_fffa948c(void *ramdata);
