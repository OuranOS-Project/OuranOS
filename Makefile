# === Configuration ===

CROSS_PREFIX = i686-elf-
AS = $(CROSS_PREFIX)as
CC = $(CROSS_PREFIX)gcc
LD = $(CROSS_PREFIX)ld
OBJCOPY = $(CROSS_PREFIX)objcopy

CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

BUILD_DIR = build
ISO_DIR = iso

# === Fichiers source ===

KERNEL_SRC = kernel/kernel.c
BOOT_SRC = boot/boot.s

KERNEL_OBJ = $(BUILD_DIR)/kernel.o
BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_ELF = $(BUILD_DIR)/kernel.elf
KERNEL_BIN = $(BUILD_DIR)/kernel.bin

ISO_IMAGE = $(BUILD_DIR)/OuranOS.iso

# === Règles ===

all: $(ISO_IMAGE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Assembler
$(BOOT_OBJ): $(BOOT_SRC) | $(BUILD_DIR)
	$(AS) -32 -o $@ $<

# Compiler
$(KERNEL_OBJ): $(KERNEL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Linker
$(KERNEL_ELF): $(KERNEL_OBJ) $(BOOT_OBJ)
	$(LD) $(LDFLAGS) -o $@ $(BOOT_OBJ) $(KERNEL_OBJ)

# Convert to flat binary
$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

# ISO image with GRUB (optionnel)
$(ISO_IMAGE): $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/kernel.bin
	echo 'set timeout=0' > $(ISO_DIR)/boot/grub/grub.cfg
	echo 'set default=0' >> $(ISO_DIR)/boot/grub/grub.cfg
	echo 'menuentry "OuranOS" { multiboot /boot/kernel.bin }' >> $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(ISO_DIR)

# Nettoyage
clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR)

.PHONY: all clean
