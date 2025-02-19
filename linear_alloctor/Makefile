CC = g++
CFLAGS = -Wall -std=c++17 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations   \
		 -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy     \
		 -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2     \
		 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith       \
		 -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo           \
		 -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef   \
		 -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range 			     \
		 -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast 			 \
		 -Wno-varargs -Wstack-protector -Wsuggest-override -Wbounds-attributes-redundant \
		 -Wlong-long -Wopenmp -fcheck-new -fsized-deallocation -fstack-protector 		 \
		 -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-protector  \
		 -fPIE -Werror=vla

LDFLAGS =

SOURCES = src/linear_allocator.cpp
BUILD_DIR = ../build
INCLUDE_DIRS = include ../common
LIN_ALLOC_DIR = linear_allocator
LIBS_DIR = ../build/libs

OBJECTS = $(addprefix $(BUILD_DIR)/$(LIN_ALLOC_DIR)/, $(SOURCES:%.cpp=%.o))
DEPS = $(OBJECTS:%.o=%.d)

CFLAGS += $(addprefix -I, $(INCLUDE_DIRS))
LDFLAGS = -L$(LIBS_DIR) -lcommon

.PHONY: all lib

all: lib

OUT = ../build/libs/liblinear_allocator.a

lib: $(OUT)

$(OUT):$(OBJECTS)
	@ar rcs $(OUT) $(OBJECTS)

$(OBJECTS): $(BUILD_DIR)/$(LIN_ALLOC_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MP -MMD -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE)

echo:
	echo $(CFLAGS)

NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif
