ROOT_DIR:= $(realpath $(shell dirname $(firstword $(MAKEFILE_LIST))))
SRC_DIR:= src
BUILD_DIR:= bin
APP_NAME:= app
CXX:= g++


#includes
VENDORS:= vendors
GLFW_DIR:= $(VENDORS)/glfw-3.4.bin.MACOS
GLFW_INC:= $(GLFW_DIR)/include
GLFW_LIB:= $(GLFW_DIR)/lib-arm64
GLM:= $(VENDORS)/glm
VULKAN_INCLUDE:= $(VULKAN_SDK)/include
VULKAN_LIB:= $(VULKAN_SDK)/lib


#flags
COMPILER_FLAGS:= -std=c++17
INC_DIRS := $(shell find $(SRC_DIR) -type d)
INCLUDE_FLAGS:= -I$(ROOT_DIR) $(addprefix -I$(ROOT_DIR)/,$(INC_DIRS)) -I$(GLM) -I$(GLFW_INC) -I$(VENDORS) -I$(VULKAN_INCLUDE) -I$(VULKAN_LIB)
LINKER_FLAGS:= -lvulkan -L$(GLFW_LIB) -lglfw3 -framework Cocoa -framework IOKit -framework CoreFoundation
SRC_FILES:= $(shell find $(SRC_DIR) -type f \( -name "*.cpp" \))


#release build
RELEASE_BUILD_DIR:= $(BUILD_DIR)/release


#debug build
DEBUG_BUILD_DIR:= $(BUILD_DIR)/debug
DEBUG_BUILD_PREPROCCESTOR_FLAGS:= -D DEBUG


.PHONY: build
build: compile_shaders
	@mkdir -p $(RELEASE_BUILD_DIR)
	@$(CXX) $(COMPILER_FLAGS) $(SRC_FILES) -o $(RELEASE_BUILD_DIR)/$(APP_NAME) $(INCLUDE_FLAGS) $(LINKER_FLAGS)
	@echo [RELEASE] build successful at [$(RELEASE_BUILD_DIR)/$(APP_NAME)]

debug: compile_shaders
	@mkdir -p $(DEBUG_BUILD_DIR)
	@$(CXX) $(COMPILER_FLAGS) $(SRC_FILES) -o $(DEBUG_BUILD_DIR)/$(APP_NAME) $(INCLUDE_FLAGS) $(LINKER_FLAGS) $(DEBUG_BUILD_PREPROCCESTOR_FLAGS)
	@echo [DEBUG] build successful at [$(DEBUG_BUILD_DIR)/$(APP_NAME)]

compile_shaders:
	@sh bats/shader_compiler.sh
	@echo shaders are compiled successfully!
