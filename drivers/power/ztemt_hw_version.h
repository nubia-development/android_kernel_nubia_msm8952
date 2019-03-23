#ifndef __ZTEMT_HW_VERSION_H__
#define __ZTEMT_HW_VERSION_H__

#define PCB_VER_LENGTH 12
#define RF_BAND_LENGTH 12
#define WIFI_STRING_LENGTH 15
#define CONFIG_STRING_LENGTH 8
#define ANT_VER_LENGTH 12

typedef enum
{
	HW_A,
	HW_B,
	HW_C,
	HW_D,
	HW_E,
	HW_F,
	HW_G,
	HW_H,
	HW_I,
	HW_UNKNOW// unknow, fail read
}hw_pcb_type;

enum ztemt_gpio_status {
 ZTE_GPIO_PULL_DOWN = 0,//gpio pull down
 ZTE_GPIO_FLOAT,//gpio float
 ZTE_GPIO_PULL_UP,//gpio pull up
 ZTE_GPIO_UNKNOWN,
};

#ifdef CONFIG_ZTEMT_HW_VER_BY_ADC
struct hw_pcb_adc_map_str{
	int low_mv;
	int high_mv;
	hw_pcb_type pcb_type;
	char pcb_ver[PCB_VER_LENGTH];
};
#else
struct hw_pcb_gpio_map_str{
	int gpio_A;
	int gpio_B;
	hw_pcb_type pcb_type;
	char pcb_ver[PCB_VER_LENGTH];
};
#endif

struct hw_rf_band_gpio_map_str{
	int gpio_A;
	int gpio_B;
	char rf_band[RF_BAND_LENGTH];
};

#ifdef CONFIG_ZTEMT_HW_CONFIG_BY_GPIO
struct hw_config_gpio_map_st{
	int gpio_A;
	int gpio_B;
	char wifi_type[WIFI_STRING_LENGTH];
	char config_type[CONFIG_STRING_LENGTH];
};
#else
struct hw_config_adc_map_st{
	int low_mv;
	int high_mv;
	char wifi_type[WIFI_STRING_LENGTH];
	char config_type[CONFIG_STRING_LENGTH];
};
#endif

//antenna 
#ifdef CONFIG_ZTEMT_ANT_VER_BY_GPIO
struct hw_ant_gpio_map_str{
	int gpio_A;
	hw_pcb_type pcb_type;
	char ant_ver[ANT_VER_LENGTH];
};
#endif

//noraml is by gpio to read pcb
#ifdef CONFIG_ZTEMT_HW_VER_BY_ADC
static const struct hw_pcb_adc_map_str hw_pcb_adc_map[] = {
	{0,     80,	    HW_A,  "MB_A"},
	{80,    220,	HW_B,  "MB_B"},
	{220,   380,    HW_C,  "MB_C"},
	{390,   510,    HW_D,  "MB_D"},
	{520,   650,    HW_E,  "MB_E"},
	{660,   770,    HW_F,  "MB_F"},
};
#else
/*HW_PCB_VESION 1.1*/
static const struct hw_pcb_gpio_map_str hw_pcb_gpio_map[] = {
	{ZTE_GPIO_PULL_DOWN, ZTE_GPIO_PULL_DOWN,	HW_A,  "MB_A"},
	{ZTE_GPIO_PULL_DOWN, ZTE_GPIO_PULL_UP,	    HW_B,  "MB_B"},
	{ZTE_GPIO_PULL_UP,   ZTE_GPIO_PULL_DOWN,    HW_C,  "MB_C"},
	{ZTE_GPIO_PULL_UP,   ZTE_GPIO_PULL_UP,      HW_D,  "MB_D"},
	{ZTE_GPIO_PULL_DOWN, ZTE_GPIO_FLOAT,        HW_E,  "MB_E"},
	{ZTE_GPIO_FLOAT,     ZTE_GPIO_PULL_DOWN,    HW_F,  "MB_F"},
	{ZTE_GPIO_PULL_UP,     ZTE_GPIO_FLOAT,          HW_G,  "MB_G"},
	{ZTE_GPIO_FLOAT,     ZTE_GPIO_PULL_UP,          HW_H,  "MB_H"},
	{ZTE_GPIO_FLOAT,     ZTE_GPIO_FLOAT,		   HW_I, "MB_I"},
};
#endif

//read rf band
static const struct hw_rf_band_gpio_map_str hw_rf_band_gpio_map[] = {
	{ZTE_GPIO_PULL_DOWN, ZTE_GPIO_PULL_DOWN,	"COMMON"},
};

//read config issue
#ifdef CONFIG_ZTEMT_HW_CONFIG_BY_GPIO
static const struct hw_config_gpio_map_st hw_config_gpio_map[] = {
	{ZTE_GPIO_PULL_DOWN, ZTE_GPIO_PULL_DOWN,    "v1", "V1"},	//529J_V1
	{ZTE_GPIO_PULL_DOWN, ZTE_GPIO_PULL_UP,    "v3", "V3"},	//529J_V3
};
#else
static const struct hw_config_adc_map_st hw_config_adc_map[] = {
	{0,   80,  "wifi_samsung"    "SC"},
};
#endif

//antenna set
#ifdef CONFIG_ZTEMT_ANT_VER_BY_GPIO
static const struct hw_ant_gpio_map_str hw_ant_gpio_map[]={
	{ZTE_GPIO_PULL_DOWN, 	HW_A,	"global"},
	{ZTE_GPIO_FLOAT,	HW_B,	"china"},
	{ZTE_GPIO_PULL_UP,	HW_C,	"unknow"},
};
#endif

#endif
