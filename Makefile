include Make.defs

ifeq ($(V),1)
Q :=
else
Q := @
endif

ECHO_CC = @printf "  CXX     %s\n" "$<"
ECHO_LD = @printf "  LINK    %s\n" "$@"

TARGET := build/bin/ledsim

SRCS := src/main.cpp

OBJS := $(patsubst %.cpp,build/obj/%.o,$(SRCS))
DEPS := $(patsubst %.cpp,build/dep/%.d,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(ECHO_LD)
	$(Q)$(CXX) $(OBJS) -o $@ $(LDFLAGS)

build/obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst build/obj/%,build/dep/%,$(dir $@))
	$(ECHO_CC)
	$(Q)$(CXX) $(CXXFLAGS) -MMD -MP \
	    -MF build/dep/$*.d \
	    -c $< -o $@

clean:
	rm -rf build

-include $(DEPS)