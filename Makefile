# -----------------------------------------------------------------------------
# Spatial Memory Lab — convenience Makefile
# -----------------------------------------------------------------------------
# CMake remains the source of truth (see root CMakeLists.txt).
# This file only groups common tasks: configure, compile, clean, run the
# desktop app. Run `make help` to list targets.
#
# Typical usage:
#   make            or   make help
#   make build
#   make run
#
# Clean slate (delete the build tree and reconfigure):
#   make distclean && make build
# -----------------------------------------------------------------------------

# Directory where CMake generates build files and places binaries (gitignored).
BUILD_DIR        ?= build

# Build type: Debug | Release | RelWithDebInfo | MinSizeRel
CMAKE_BUILD_TYPE ?= Debug

# CMake generator (empty = system default, usually "Unix Makefiles" on macOS/Linux).
# Example Ninja:  make configure CMAKE_GENERATOR=Ninja
CMAKE_GENERATOR  ?=

# Compile parallelism (--parallel with no value uses available cores).
JOBS             ?=

# Which app under apps/ to run. Override on the command line:
#   make run APP=other_app
APP              ?= desktop_app

# Executable path inferred from APP (apps/<APP>/<APP> under the build directory).
APP_BIN          := $(BUILD_DIR)/apps/$(APP)/$(APP)

# Base cmake command (extra flags: make configure CMAKE_FLAGS="-DFOO=ON")
CMAKE            ?= cmake
CMAKE_FLAGS      ?=

.PHONY: help configure build all clean distclean rebuild run

.DEFAULT_GOAL := help

# -----------------------------------------------------------------------------
# help — print targets and useful variables
# -----------------------------------------------------------------------------
help:
	@echo "Spatial Memory Lab — Make targets"
	@echo ""
	@echo "  make configure   Run CMake (-S . -B $(BUILD_DIR))"
	@echo "  make build       Compile (configures automatically if build/ is missing)"
	@echo "  make all         Same as: configure + build"
	@echo "  make run         Build and run \$$(APP) (default: $(APP))"
	@echo "  make clean       Remove build artifacts (keeps CMake cache)"
	@echo "  make distclean   Delete the entire $(BUILD_DIR) directory"
	@echo "  make rebuild     clean + build"
	@echo ""
	@echo "Variables (e.g. make run APP=desktop_app CMAKE_BUILD_TYPE=Release JOBS=8):"
	@echo "  APP=$(APP) — which app under apps/ to run"
	@echo "  BUILD_DIR=$(BUILD_DIR)"
	@echo "  CMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)"
	@echo "  CMAKE_GENERATOR=<empty or Ninja, Xcode, etc.>"
	@echo "  JOBS=<empty or number> — forwarded as --parallel to cmake --build"
	@echo "  CMAKE_FLAGS=<extra flags passed at configure time>"

# -----------------------------------------------------------------------------
# configure — generate build files in BUILD_DIR
# -----------------------------------------------------------------------------
configure:
	@$(CMAKE) -S . -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		$(if $(CMAKE_GENERATOR),-G "$(CMAKE_GENERATOR)",) \
		$(CMAKE_FLAGS)

# -----------------------------------------------------------------------------
# build — compile; reconfigures if the build directory is not set up yet
# -----------------------------------------------------------------------------
build: $(BUILD_DIR)/CMakeCache.txt
	@$(CMAKE) --build $(BUILD_DIR) $(if $(JOBS),--parallel $(JOBS),--parallel)

$(BUILD_DIR)/CMakeCache.txt:
	@$(MAKE) configure

# -----------------------------------------------------------------------------
# all — explicit configure then build
# -----------------------------------------------------------------------------
all: configure build

# -----------------------------------------------------------------------------
# clean — remove generated objects/libs; keeps CMakeCache (faster rebuilds)
# -----------------------------------------------------------------------------
clean:
	@if [ -f $(BUILD_DIR)/CMakeCache.txt ]; then \
		$(CMAKE) --build $(BUILD_DIR) --target clean; \
	else \
		echo "make clean: nothing to do ($(BUILD_DIR) not configured)"; \
	fi

# -----------------------------------------------------------------------------
# distclean — remove the whole build directory (after generator/toolchain changes)
# -----------------------------------------------------------------------------
distclean:
	rm -rf $(BUILD_DIR)

# -----------------------------------------------------------------------------
# rebuild — CMake clean target + full build
# -----------------------------------------------------------------------------
rebuild: clean build

# -----------------------------------------------------------------------------
# run — build and run apps/$(APP)/$(APP)
#   make run                 # runs the default app ($(APP))
#   make run APP=other_app   # runs apps/other_app/other_app
# -----------------------------------------------------------------------------
run: build
	@test -f $(APP_BIN) || { echo "Binary not found: $(APP_BIN) (is APP=$(APP) correct?)"; exit 1; }
	@$(APP_BIN)
