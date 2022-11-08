# Generic makefile
# Works for any well structured c++ project

.PHONY: build clean

OUT_DIR ?= obj/
SRC_DIR ?= src/
DEPS_DIR ?= deps/
INC_DIR ?= include/
EXEC_NAME ?= program

CXX := g++
CXXFLAGS ?= -O2
CXXFLAGS := $(CXXFLAGS) -std=c++11 -Wall -Wextra -I $(INC_DIR)

define COMPILE_COMMAND
mkdir -p $(@D) $(dir $(DEPS_DIR)$*)
$(CXX) $(CXXFLAGS) -c "$<" -MMD -MT "$@" -MF "$(DEPS_DIR)$*.d" -o "$@"
endef

LDFLAGS ?= -O2
LDFLAGS := $(LDFLAGS) -std=c++11 -I $(INC_DIR)
LDLIBS := 

OBJECTS := $(patsubst $(SRC_DIR)%.cpp,$(OUT_DIR)%.o,$(shell find $(SRC_DIR) | grep '.cpp$$'))

build: $(EXEC_NAME)

clean:
	rm -rf $(OUT_DIR) $(DEPS_DIR) $(EXEC_NAME)

$(EXEC_NAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o "$@" $+ $(LDLIBS)

$(OUT_DIR)%.o: $(SRC_DIR)%.cpp
	$(COMPILE_COMMAND)

-include $(DEPS_DIR)*.d
