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
INCLUDE_FLAGS:= $(addprefix -I,$(INC_DIRS)) -I$(GLM) -I$(GLFW_INC) -I$(VENDORS) -I$(VULKAN_INCLUDE) -I$(VULKAN_LIB)
LINKER_FLAGS:= -lvulkan -L$(GLFW_LIB) -lglfw3 -framework Cocoa -framework IOKit -framework CoreFoundation
SRC_FILES:= $(shell find $(SRC_DIR) -type f \( -name "*.cpp" \))


.PHONY: build
build:
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(COMPILER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(INCLUDE_FLAGS) $(LINKER_FLAGS)
	@echo build successful at [$(BUILD_DIR)/$(APP_NAME)]

debug:
	@echo $(INC_DIRS)