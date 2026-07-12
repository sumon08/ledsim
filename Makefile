include Make.defs

ifeq ($(V),1)
Q :=
else
Q := @
endif

ECHO_CC = @printf "  CC: %s\n" "$<"
ECHO_CXX = @printf "  CXX: %s\n" "$<"
ECHO_LD = @printf "  LD: %s\n" "$@"

TARGET := build/bin/ledsim

SRCS := src/main.cpp
SRCS += src/Application.cpp



#glad source files
SRCS += libs/glad/src/gl.c

OBJS := $(SRCS)
OBJS := $(OBJS:.cpp=.o)
OBJS := $(OBJS:.c=.o)
OBJS := $(addprefix build/obj/,$(OBJS))

DEPS := $(OBJS:build/obj/%.o=build/dep/%.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(ECHO_LD)
	$(Q)$(CXX) $(OBJS) -o $@ $(LDFLAGS)

build/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst build/obj/%,build/dep/%,$(dir $@))
	$(ECHO_CXX)
	$(Q)$(CXX) $(CXXFLAGS) -MMD -MP \
	    -MF build/dep/$*.d \
	    -c $< -o $@

build/obj/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst build/obj/%,build/dep/%,$(dir $@))
	$(ECHO_CC)
	$(Q)$(CC) $(CFLAGS) -MMD -MP \
	    -MF build/dep/$*.d \
	    -c $< -o $@

clean:
	rm -rf build

-include $(DEPS)