# === Configuration ===

CROSS_PREFIX = i686-elf-
AS = $(CROSS_PREFIX)as
CC = $(CROSS_PREFIX)gcc
LD = $(CROSS_PREFIX)ld
OBJCOPY = $(CROSS_PREFIX)objcopy

CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

BUILD_DIR = build

# === Fichiers source ===

BOOT_SRC = boot/bootloader.s
KERNEL_SRC = kernel/kernel.c

BOOT_OBJ = $(BUILD_DIR)/bootloader.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
KERNEL_ELF = $(BUILD_DIR)/kernel.elf
KERNEL_BIN = $(BUILD_DIR)/kernel.bin

# === Règles ===

all: $(KERNEL_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Assemble le bootloader
$(BOOT_OBJ): $(BOOT_SRC) | $(BUILD_DIR)
	$(AS) -32 -o $@ $<

# Compile le kernel C
$(KERNEL_OBJ): $(KERNEL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Link les deux en un fichier ELF
$(KERNEL_ELF): $(BOOT_OBJ) $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Convertit en binaire brut
$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

# Nettoyage
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
