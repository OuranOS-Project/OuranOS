# === Configuration ===

CROSS_PREFIX = i686-elf-
AS = nasm
CC = $(CROSS_PREFIX)gcc
LD = $(CROSS_PREFIX)ld
OBJCOPY = $(CROSS_PREFIX)objcopy

CFLAGS = -ffreestanding -m32 -O2 -Wall -Wextra -fno-stack-protector -fomit-frame-pointer
LDFLAGS = -T linker.ld -nostdlib

BUILD_DIR = build

# === Fichiers source ===

BOOT_SRC = boot/bootloader.s
KERNEL_SRC = kernel/kernel.c kernel/screen.c

BOOT_BIN = $(BUILD_DIR)/bootloader.bin
KERNEL_OBJ = $(KERNEL_SRC:kernel/%.c=$(BUILD_DIR)/%.o)
KERNEL_ELF = $(BUILD_DIR)/kernel.elf
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
OS_IMAGE = $(BUILD_DIR)/os.img

# === Règles ===

all: $(OS_IMAGE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Assemble bootloader
$(BOOT_BIN): $(BOOT_SRC) | $(BUILD_DIR)
	$(AS) -f bin $< -o $@

# Compile kernel objects
$(BUILD_DIR)/%.o: kernel/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Link kernel
$(KERNEL_ELF): $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Convert to raw binary
$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

# Créer une image disque valide avec bootloader et kernel
$(OS_IMAGE): $(BOOT_BIN) $(KERNEL_BIN)
	dd if=/dev/zero of=$@ bs=512 count=2880          # Créer une image vide 1.44MB
	dd if=$(BOOT_BIN) of=$@ conv=notrunc            # Écrire le bootloader
	dd if=$(KERNEL_BIN) of=$@ bs=512 seek=1 conv=notrunc  # Écrire le kernel à partir du secteur 2

run: $(OS_IMAGE)
	qemu-system-i386 -fda $(OS_IMAGE)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run
