SRC_DIR:= src
BUILD_DIR:= bin
APP_NAME:= app
CXX:= g++


VENDORS:= vendors


ifeq ($(OS),Windows_NT)
	ROOT_DIR = $(shell cd)
	MK_DIR = powershell -Command "if (!(Test-Path $(1))) {New-Item -Path $(1) -ItemType Directory}"
	find_dirs = $(1) $(foreach dir,$(wildcard $(1)/*),$(if $(wildcard $(dir)/.),$(call find_dirs,$(dir))))
	INC_DIRS = $(call find_dirs,$(SRC_DIR))
	INC_DIRS_FLAG = $(addprefix -I,$(subst /,\,$(addprefix $(ROOT_DIR)/,$(INC_DIRS))))
	find_files = $(foreach file,$(wildcard $(1)/*.cpp),$(file))$(foreach file,$(wildcard $(1)/*),$(call find_files,$(file)))
	SRC_FILES = $(call find_files,$(SRC_DIR))
	GLFW_DIR = $(VENDORS)/glfw-3.3.8.bin.WIN64
	GLFW_LIB = $(GLFW_DIR)/lib-mingw-w64
	VULKAN_LIB = $(VULKAN_SDK)/Lib
	EXTRA_LINKER_FLAGS = -lgdi32
	PREPROCESSORS = -D WINDOWS
	SHADER_COMPILER = bats\shader_compiler.bat
	EXECUTE = $(1)
else
	ROOT_DIR = $(realpath $(shell dirname $(firstword $(MAKEFILE_LIST))))
	MK_DIR = mkdir -p $(1)
	INC_DIRS = $(shell find $(SRC_DIR) -type d)
	INC_DIRS_FLAG = $(addprefix -I$(ROOT_DIR)/,$(INC_DIRS))
	SRC_FILES = $(shell find $(SRC_DIR) -type f \( -name "*.cpp" \))
	GLFW_DIR = $(VENDORS)/glfw-3.4.bin.MACOS
	GLFW_LIB = $(GLFW_DIR)/lib-arm64
	VULKAN_LIB = $(VULKAN_SDK)/lib
	EXTRA_LINKER_FLAGS = -framework Cocoa -framework IOKit -framework CoreFoundation
	PREPROCESSORS = -D MACOS
	SHADER_COMPILER = sh bats/shader_compiler.sh
	EXECUTE = DYLD_LIBRARY_PATH=$(VULKAN_LIB) $(1)
endif


#includes
GLFW_INC:= $(GLFW_DIR)/include
GLM:= $(VENDORS)/glm
VULKAN_INCLUDE:= $(VULKAN_SDK)/include


#flags
COMPILER_FLAGS:= -std=c++17
INCLUDE_FLAGS:= -I$(ROOT_DIR) $(INC_DIRS_FLAG) -I$(GLM) -I$(GLFW_INC) -I$(VENDORS) -I$(VULKAN_INCLUDE)
LINKER_FLAGS:= -L$(VULKAN_LIB) -lvulkan -L$(GLFW_LIB) -lglfw3 $(EXTRA_LINKER_FLAGS)


#release build
RELEASE_BUILD_DIR:= $(BUILD_DIR)/release


#debug build
DEBUG_BUILD_DIR:= $(BUILD_DIR)/debug
DEBUG_BUILD_COMPILER_FLAGS:= -g
DEBUG_BUILD_PREPROCCESTOR_FLAGS:= -D DEBUG


.PHONY: build
build: compile_shaders
	@$(call MK_DIR,$(RELEASE_BUILD_DIR))
	@$(CXX) $(COMPILER_FLAGS) $(SRC_FILES) -o $(RELEASE_BUILD_DIR)/$(APP_NAME) $(INCLUDE_FLAGS) $(LINKER_FLAGS) $(PREPROCESSORS)
	@echo [RELEASE] build successful at [$(RELEASE_BUILD_DIR)/$(APP_NAME)]
	@$(call EXECUTE,$(RELEASE_BUILD_DIR)/$(APP_NAME))

debug: compile_shaders
	@$(call MK_DIR,$(DEBUG_BUILD_DIR))
	@$(CXX) $(COMPILER_FLAGS) $(DEBUG_BUILD_COMPILER_FLAGS) $(SRC_FILES) -o $(DEBUG_BUILD_DIR)/$(APP_NAME) $(INCLUDE_FLAGS) $(LINKER_FLAGS) $(PREPROCESSORS) $(DEBUG_BUILD_PREPROCCESTOR_FLAGS)
	@echo [DEBUG] build successful at [$(DEBUG_BUILD_DIR)/$(APP_NAME)]
	@$(call EXECUTE,$(DEBUG_BUILD_DIR)/$(APP_NAME))

compile_shaders:
	@$(SHADER_COMPILER)
	@echo shaders are compiled successfully!
