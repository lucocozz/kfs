NAME = kfs
BIN = $(NAME).bin
ISO = $(NAME).iso
BUILD_DIR = .build-x86
CROSS_FILE = config/x86_64-x86.ini



define check_multiboot
	@echo "Checking multiboot..."
	@grub-file --is-x86-multiboot $(BUILD_DIR)/$(BIN) || (echo "$(NAME) is not multiboot ❌" && exit 1)
	@echo "Multiboot check passed ✅"
endef


define create_iso
	@echo "Creating iso image..."
	@mkdir -p $(BUILD_DIR)/iso/boot/grub
	@cp $(BUILD_DIR)/$(BIN) $(BUILD_DIR)/iso/boot/$(BIN)
	@cp config/grub.cfg $(BUILD_DIR)/iso/boot/grub/grub.cfg
	@grub-mkrescue -o $(BUILD_DIR)/$(ISO) $(BUILD_DIR)/iso
	@ln -sf $(BUILD_DIR)/$(ISO) $(ISO)
	@echo "Iso image created ✅"
endef


all: build compile image

build:
	meson setup --cross-file $(CROSS_FILE) $(BUILD_DIR)

reconfigure:
	meson setup --reconfigure --cross-file $(CROSS_FILE) $(BUILD_DIR)

wipe:
	meson setup --wipe $(BUILD_DIR)

compile:
	meson compile -C $(BUILD_DIR)
	@ln -sf $(BUILD_DIR)/$(BIN) $(BIN)
	$(call check_multiboot)

image:
	$(call create_iso)

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Build directory cleaned ✅"

fclean: clean
	@rm -rf $(BIN)
	@rm -rf $(ISO)
	@echo "Executable removed ✅"

re: reconfigure compile image

help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all          - build, compile and create iso image"
	@echo "  build        - build project"
	@echo "  reconfigure  - reconfigure project"
	@echo "  wipe         - wipe build directory"
	@echo "  compile      - compile project"
	@echo "  image        - create iso image"
	@echo "  clean        - clean build directory"
	@echo "  fclean       - clean build directory and remove executable"
	@echo "  re           - reconfigure and compile"
	@echo "  help         - print this message"


.PHONY: all build compile clean fclean re reconfigure wipe help image 