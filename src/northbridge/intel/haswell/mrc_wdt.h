typedef struct
{
	int (*wdt_f0)(uint32_t);
	int (*wdt_f1)(void);
	void (*wdt_f2)(void);
	void (*wdt_f3)(void);
	int (*wdt_f4)(void);
	int (*wdt_f5)(void);
} PEI_WDT_PPI;
