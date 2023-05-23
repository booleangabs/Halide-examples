CXX = g++
CXX_FLAGS = -std=c++2a -fno-rtti -O3

INCLUDES = -I$(HALIDE_ROOT)/include -I$(HALIDE_ROOT)/tools
LIBS = -L$(HALIDE_ROOT)/lib 
LIB_FLAGS = -lHalide -lpthread -ldl -lz -ltinfo
IMAGE_IO_FLAGS = -ljpeg `libpng-config --cflags --ldflags`

ifndef IMAGE_FILENAME
	IMAGE_FILENAME = pattern.png
endif

all: run_pattern_generation

clean:
	@rm -rf bin outputs

bin/%: src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $^ $(CXX_FLAGS) $(INCLUDES) $(LIBS) $(LIB_FLAGS) $(IMAGE_IO_FLAGS) -o $@

run_%: bin/%
	@mkdir -p outputs
	@$^ outputs/$(IMAGE_FILENAME)
	@echo "Saved result to outputs/"$(IMAGE_FILENAME)

.PHONY: all clean
.PRECIOUS: bin/%
