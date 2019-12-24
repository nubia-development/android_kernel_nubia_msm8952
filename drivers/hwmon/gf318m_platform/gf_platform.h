#ifndef __GF_PLATFORM_H__
#define __GF_PLATFORM_H__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/of_gpio.h>
#include <linux/input.h>
#include <linux/wakelock.h>
#include <linux/pinctrl/consumer.h>
#include <linux/clk.h>
#include <soc/qcom/scm.h>
#ifdef CONFIG_FB
#include <linux/notifier.h>
#include <linux/fb.h>
#endif
#include "gf_log.h"

/********************GF Mapping**********************/
#define GF_BASE             (0x8000)
#define GF_OFFSET(x)        (GF_BASE + x)

#define GF_VERSION	        GF_OFFSET(0)
#define GF_CONFIG_DATA      GF_OFFSET(0x40)
#define GF_CFG_ADDR	        GF_OFFSET(0x47)
#define GF_MODE_STATUS      GF_OFFSET(0x043)
#define GF_BUFFER_STATUS	GF_OFFSET(0x140)
#define GF_KEY_DATA         GF_OFFSET(0x142)
#define GF_NOISE_DATA       GF_OFFSET(0x144)
#define GF_LONG_PRESS_STDP  GF_OFFSET(0x146)
#define GF_BUFFER_DATA      GF_OFFSET(0x141)

#define GF_BUF_STA_MASK     (0x1 << 7)
#define	GF_BUF_STA_READY	(0x1 << 7)
#define	GF_BUF_STA_BUSY     (0x0 << 7)

#define	GF_IMAGE_MASK       (0x1 << 6)
#define	GF_IMAGE_ENABLE     (0x1)
#define	GF_IMAGE_DISABLE	(0x0)

#define	GF_KEY_MASK	        (GF_HOME_KEY_MASK | \
                             GF_MENU_KEY_MASK | \
                             GF_BACK_KEY_MASK )

/* home key */
#define	GF_HOME_KEY_MASK	(0x1 << 5)
#define	GF_HOME_KEY_ENABL   (0x1)
#define	GF_HOME_KEY_DISABLE (0x0)
#define	GF_HOME_KEY_STA     (0x1 << 4)

/* menu key */
#define	GF_MENU_KEY_MASK    (0x1 << 3)
#define	GF_MENU_KEY_ENABLE	(0x1)
#define	GF_MENU_KEY_DISABLE	(0x0)
#define	GF_MENU_KEY_STA	    (0x1 << 2)

/* back key */
#define	GF_BACK_KEY_MASK    (0x1 << 1)
#define	GF_BACK_KEY_ENABLE  (0x1)
#define	GF_BACK_KEY_DISABLE (0x0)
#define	GF_BACK_KEY_STA     (0x1 << 0)

#define	GF_IMAGE_MODE       (0x00)
#define	GF_KEY_MODE	        (0x01)
#define GF_SLEEP_MODE       (0x02)
#define GF_FF_MODE		    (0x03)
#define GF_DEBUG_MODE       (0x56)

/**********************GF ops****************************/
#define GF_W                0xF0
#define GF_R                0xF1
#define GF_WDATA_OFFSET     (0x3)
#define GF_RDATA_OFFSET     (0x5)
#define GF_CFG_LEN          (249)   /*config data length*/

#define GF_FASYNC 		    1

/*************************************************************/
#define PLATFORM_DEV_NAME   "gf318m"
#define DEV_NAME            "goodix_fp"

#define GF_PID              "GFx18M"
#define GF_PID_LEN          6
#define GF_INPUT_MENU_KEY   KEY_MENU
#define GF_INPUT_BACK_KEY   KEY_BACK
#define GF_INPUT_HOME_KEY   KEY_HOME
#define GF_FF_KEY           KEY_F11
#define GF_POWER_KEY        KEY_POWER

#define	CHRD_DRIVER_NAME	"goodix"
#define	CLASS_NAME			"goodix-spi"
#define PLATFORMDEV_MAJOR	154	/* assigned */
#define N_PLATFORM_MINORS	32	/* ... up to 256 */

#define GF_INT_ENABLE       1
#define GF_INT_DISABLE      0

/*************************************************************/
struct gf_pinctrl_info {
	struct pinctrl *pinctrl;
	struct pinctrl_state *gpio_state_active;
	struct pinctrl_state *gpio_state_suspend;
	struct pinctrl_state *gpio_enable_active;
	struct pinctrl_state *gpio_int_active;
	struct pinctrl_state *gpio_rst_active;
};

struct gf_dev {
	struct platform_device *pdev;

	dev_t devt;
	spinlock_t platform_lock;
	struct list_head device_entry;

	struct input_dev *input;

#ifdef CONFIG_FB
	struct notifier_block fb_notifier;
#endif

	unsigned users;	

#ifdef GF_FASYNC
	struct	fasync_struct *async;
#endif

    int reset_gpio;
	int enable_gpio;

	int irq_gpio;
	int	irq;

	bool wake_up;

	struct gf_pinctrl_info gf_pctrl;

	char device_available;
	char fb_black;
	struct wake_lock wake_lock;
};

struct gf_key {
	unsigned int key;
	int value;
};

/*************************IO Magic**************************/
#define  GF_IOC_TEE_MAGIC         'G'
#define  GF_IOC_TEE_DISABLE_IRQ	_IO(GF_IOC_TEE_MAGIC, 0)
#define  GF_IOC_TEE_ENABLE_IRQ	_IO(GF_IOC_TEE_MAGIC, 1)
#define  GF_IOC_TEE_SETSPEED    _IOW(GF_IOC_TEE_MAGIC, 2, unsigned int)
#define  GF_IOC_TEE_RESET       _IO(GF_IOC_TEE_MAGIC, 3)
#define  GF_IOC_TEE_COOLBOOT    _IO(GF_IOC_TEE_MAGIC, 4)
#define  GF_IOC_TEE_SENDKEY     _IOW(GF_IOC_TEE_MAGIC, 5, struct gf_key)
#define  GF_IOC_TEE_CLK_READY   _IO(GF_IOC_TEE_MAGIC, 6)
#define  GF_IOC_TEE_CLK_UNREADY _IO(GF_IOC_TEE_MAGIC, 7)
#define  GF_IOC_TEE_PM_FBCABCK  _IO(GF_IOC_TEE_MAGIC, 8)
#define  GF_IOC_TEE_POWER_ON    _IO(GF_IOC_TEE_MAGIC, 9)
#define  GF_IOC_TEE_POWER_OFF   _IO(GF_IOC_TEE_MAGIC, 10)
#define  GF_IOC_TEE_MAXNR       11

/**********************function prototype****************************/
int gf_parse_dts(struct gf_dev *gf_dev);
int gf_init_gpio(struct gf_dev *gf_dev);
int gf_init_pinctrl(struct gf_dev *gf_dev, struct device *dev);
int gf_pinctrl_set(struct gf_dev *gf_dev, bool active);
void gf_reset(struct gf_dev *gf_dev);
int gf_sys_init(void);

#endif
