# Dossiers
BOOT_DIR = boot
KERNEL_DIR = kernel
BUILD_DIR = build

# Fichiers sources
BOOT_SRC = $(BOOT_DIR)/boot.s
KERNEL_SRC = $(KERNEL_DIR)/kernel.c

# Fichiers objets
BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o

# Binaire final
BIN = $(BUILD_DIR)/monos.bin

all: $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BOOT_OBJ): $(BOOT_SRC) | $(BUILD_DIR)
	nasm -f elf32 $< -o $@

$(KERNEL_OBJ): $(KERNEL_SRC) | $(BUILD_DIR)
	gcc -m32 -ffreestanding -c $< -o $@

$(BIN): $(BOOT_OBJ) $(KERNEL_OBJ)
	ld -m elf_i386 -T linker.ld -o $@ $^

clean:
	rm -rf $(BUILD_DIR)
