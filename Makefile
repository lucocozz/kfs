NAME = kfs-1
BUILD_DIR = .build-x86
CROSS_FILE = x86_64-x86.ini


all: build compile

build:
	meson setup --cross-file $(CROSS_FILE) $(BUILD_DIR)

reconfigure:
	meson setup --reconfigure --cross-file $(CROSS_FILE) $(BUILD_DIR)

wipe:
	meson setup --wipe $(BUILD_DIR)

compile:
	meson compile -C $(BUILD_DIR)
	ln -sf $(BUILD_DIR)/$(NAME) $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: reconfigure compile

help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all          - build and compile"
	@echo "  build        - build project"
	@echo "  compile      - compile project"
	@echo "  clean        - clean build directory"
	@echo "  fclean       - clean build directory and remove executable"
	@echo "  re           - reconfigure and compile"
	@echo "  reconfigure  - reconfigure project"
	@echo "  wipe         - wipe build directory"


.PHONY: all build compile clean fclean re reconfigure wipe help