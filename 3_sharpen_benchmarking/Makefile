CXX = g++
CXX_FLAGS = -std=c++20 -fno-rtti

GENERATOR_DEPS = ${HALIDE_ROOT}/tools/GenGen.cpp
GENERATOR_OUTPUTS = o,h,schedule,stmt_html,stmt
INCLUDES = -I$(HALIDE_ROOT)/include -I$(HALIDE_ROOT)/tools -Iinclude -Ibin
LIBS = -L$(HALIDE_ROOT)/lib 
LIB_FLAGS = -lHalide -lpthread -ldl -lz -ltinfo
IMAGE_IO_FLAGS = -ljpeg `libpng-config --cflags --ldflags`

ifndef PATH_IN
	PATH_IN=../inputs/camera.png
endif

ifndef PATH_OUT_SIMPLE
	PATH_OUT_SIMPLE=../outputs/camera_sharpen_simple.png
endif

ifndef PATH_OUT_FULL
	PATH_OUT_FULL=../outputs/camera_sharpen_full.png
endif

TARGET=host
ifdef PROFILE
	ifeq ($(PROFILE), true)
		TARGET=host-profile
	endif
endif

ifndef AUTO_SCHEDULE
	AUTO_SCHEDULE=true
endif
ifeq ($(AUTO_SCHEDULE), true)
	ifndef AUTO_SCHEDULER
		AUTO_SCHEDULER=Mullapudi2016
		AUTO_SCHEDULER_PATH=$(HALIDE_ROOT)/lib/libautoschedule_mullapudi2016.so
	endif
	AUTO_SCHEDULER_PARS=autoscheduler=$(AUTO_SCHEDULER) -p $(AUTO_SCHEDULER_PATH)
	ifdef MACHINE_PARAMS
		AUTO_SCHEDULER_PARS+=machine_params=$(MACHINE_PARAMS)
	endif
endif

all: run_sharpen

clean:
	@rm -rf bin/* ../outputs/*

bin/sharpen.generator: src/generators/HalideSharpen.cpp
	@mkdir -p $(@D)
	@$(CXX) $^ $(GENERATOR_DEPS) $(CXX_FLAGS) $(INCLUDES) $(LIBS) $(LIB_FLAGS) -o $@

bin/sharpen_simple.o: bin/sharpen.generator
	@$^ -e $(GENERATOR_OUTPUTS) -o $(@D) -f sharpen_simple -g sharpen target=$(TARGET) mode=simple $(AUTO_SCHEDULER_PARS) 

bin/sharpen_full.o: bin/sharpen.generator
	@$^ -e $(GENERATOR_OUTPUTS) -o $(@D) -f sharpen_full -g sharpen target=$(TARGET) mode=full $(AUTO_SCHEDULER_PARS) 

bin/main: src/main.cpp bin/sharpen_simple.o bin/sharpen_full.o
	@$(CXX) $^ $(CXX_FLAGS) $(INCLUDES) $(LIBS) $(LIB_FLAGS) $(IMAGE_IO_FLAGS) -o $@

run_sharpen: bin/main
	@mkdir -p ../outputs
	@$^ $(PATH_IN) $(PATH_OUT_SIMPLE) $(PATH_OUT_FULL)
	@echo "Saved result to "$(PATH_OUT_SIMPLE)" and "$(PATH_OUT_FULL)

.PHONY: all clean
.PRECIOUS: bin/%
