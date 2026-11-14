// SPDX-License-Identifier: GPL-2.0-only
#ifndef EVEREST_FDT_H_
#define EVEREST_FDT_H_

/* Replace the embedded EMUI10 FDT with a validated, adapted workspace. */
int everest_patch_dtb(void **dt, const void *bootloader_fdt);

#endif /* EVEREST_FDT_H_ */
