# Generic makefile
# Works for any well structured c++ project

.PHONY: build clean run format

OUT_DIR ?= obj/
SRC_DIR ?= src/
DEPS_DIR ?= deps/
INC_DIR ?= include/
EXEC_NAME ?= gaming
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

CPP := g++
OPTI ?= -O2
CPPFLAGS := $(OPTI) -std=c++11 -Wall -Wextra -I $(INC_DIR)

define CPP_OBJ
mkdir -p $(@D) $(dir $(DEPS_DIR)$*)
$(CPP) $(CPPFLAGS) -c $< -MMD -MT $@ -MF $(DEPS_DIR)$*.d -o $@
endef

OBJECTS := $(patsubst $(SRC_DIR)%.cpp,$(OUT_DIR)%.o,$(shell find $(SRC_DIR) | grep '.cpp$$'))

build: $(EXEC_NAME)

run: $(EXEC_NAME)
	./$(EXEC_NAME)

clean:
	rm -rf $(OUT_DIR) $(DEPS_DIR) $(EXEC_NAME)

format:
	clang-format $(find src | grep .cpp) $(find include | grep .hpp) -style=file -i

$(EXEC_NAME): $(OBJECTS)
	$(CPP) $(CPPFLAGS) -o $@ $+ $(LIBS)

$(OUT_DIR)%.o: $(SRC_DIR)%.cpp
	$(CPP_OBJ)

ALL_DEPS := $(shell find $(DEPS_DIR) | grep '.d$$')

-include $(ALL_DEPS)
