// SPDX-License-Identifier: GPL-2.0-only
/*
 * Board support for Huawei Mate 20 X (Everest)
 * HiSilicon Kirin 980
 */

#include <board.h>
#include <util.h>
#include <drivers/framework.h>
#include <lib/simplefb.h>
#include <string.h>

/*
 * ARM SP805 watchdog.
 * Base address confirmed in Everest DTB.
 */
#define EVEREST_WDT_BASE  0xE8A06000UL

/*
 * Framebuffer initialized by Huawei bootloader.
 * Resolution: 1080 x 2244, ARGB8888.
 */
#define EVEREST_FB_BASE   0x36500000UL

/*
 * Enable LDI frame updates disabled by Huawei firmware.
 *
 * Clear bit 0: allow frame updates.
 * Set bit 0:   enable LDI.
 */
#define EVEREST_DSS_BASE          0xE8600000UL
#define EVEREST_DSS_LDI0_OFFSET   0x7D000UL

#define EVEREST_LDI_CTRL \
	(EVEREST_DSS_BASE + EVEREST_DSS_LDI0_OFFSET + 0x0024UL)

#define EVEREST_LDI_FRM_MSK \
	(EVEREST_DSS_BASE + EVEREST_DSS_LDI0_OFFSET + 0x0044UL)

static int everest_early_init(void)
{
	/*
	 * Restore LDI frame updates disabled by Huawei firmware
	 * before handing control to the kernel.
	 *
	 * Clear bit 0: allow frame updates.
	 * Set bit 0:   enable LDI.
	 */
	writel(readl((volatile uint32_t *)EVEREST_LDI_FRM_MSK) & ~1U,
	       (void *)EVEREST_LDI_FRM_MSK);

	writel(readl((volatile uint32_t *)EVEREST_LDI_CTRL) | 1U,
	       (void *)EVEREST_LDI_CTRL);

	return 0;
}

static struct video_info everest_fb = {
	.format  = FB_FORMAT_ARGB8888,
	.width   = 1080,
	.height  = 2244,
	.stride  = 4,
	.scale   = 2,
	.address = (void *)EVEREST_FB_BASE,
};

static const struct device everest_devices[] = {
	{ "arm,sp805-wdt", (void *)EVEREST_WDT_BASE, "wdt0" },
	{ "simplefb", &everest_fb, "fb" },
};

struct board_data board_ops = {
	.name = "huawei-everest",
	.ops = {
		.early_init = everest_early_init,
	},
	.devices = everest_devices,
	.num_devices = ARRAY_SIZE(everest_devices),
	.quirks = 0,
};
