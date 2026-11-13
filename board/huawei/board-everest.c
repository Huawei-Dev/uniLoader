// SPDX-License-Identifier: GPL-2.0-only
/*
 * Board support for Huawei Mate 20 X (Everest)
 * HiSilicon Kirin 980
 */

#include <board.h>
#include <util.h>
#include <drivers/framework.h>
#include <lib/simplefb.h>

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
	.devices = everest_devices,
	.num_devices = ARRAY_SIZE(everest_devices),
	.quirks = 0,
};
