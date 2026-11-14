obj-y := boot.o main.o

# Everest has its own FDT workspace and must not invoke the generic
# initrd patcher (CONFIG_RAMDISK_NO_COPY / Huawei SAR).
ifeq ($(CONFIG_HUAWEI_EVEREST),y)
obj-$(CONFIG_LIBFDT) += everest-fdt.o
else
obj-$(CONFIG_LIBFDT) += boot-fdt.o
endif
