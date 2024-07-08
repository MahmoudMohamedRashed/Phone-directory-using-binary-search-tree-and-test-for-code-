# these variables are system dependend 
# set then yourself
CXX = g++
LD = g++
# maybe you want to remove that -Werror flag
# it makes the build fail if it finds any warnings
# -fstack-protector (in my experience: produces segfault)
CXXFLAGS = -fpic -pipe -Wall -Werror
LDFLAGS = $(CXXFLAGS)

OUTPUT_OPTION = -MMD -MP -o $(BUILDDIR)/$*.o  -MF $(BUILDDIR)/$*.d

BUILDDIR = ./build
# the name of the executable file
TARGET = $(BUILDDIR)/main
# the root of the src code
SRCDIR = .
# directory of test files
TESTDIR = ./tests

# search recursivly for source files
SRCS := $(wildcard $(SRCDIR)/**/*.cpp)
SRCS += $(wildcard $(SRCDIR)/*.cpp)

TESTS = $(wildcard $(TESTDIR)/*.in)
sol_name = $(patsubst %.in,%.sol,$(1))
out_name = $(patsubst %.in,%.out,$(1))
out_to_in = $(patsubst %.out,%.in,$(1))
out_to_sol = $(patsubst %.out,%.sol,$(1))
test_name = $(patsubst %.out,%,$(1))
TESTS_SOL = $(foreach test,$(TESTS),$(call sol_name))
TESTS_OUT = $(foreach test,$(TESTS),$(call out_name))

%.out: %.in $(TARGET)
	cat $(call out_to_in,$@) | $(TARGET) > $@
	@diff --color $@ $(call out_to_sol,$@) && echo "$(call test_name,$@) passed" >> test.grader || echo "$(call test_name,$@) failed" >> test.grader

TESTS_SOL = $(wildcard $(TESTDIR/*.sol))
TESTS_OUT = $(patsubst %.in,%.out,$(TESTS))


ifdef DEBUG
	CXXFLAGS += -g -DDEBUG_VERBOSE
endif
ifdef RELEASE
	CXXFLAGS += -O3 -flto
endif
ifdef FULL_CAP
	CXXFLAGS += -DFULL_CAP
endif

DEPS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.d,$(SRCS))
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
-include $(DEPS)

all: build test

build: $(TARGET)

$(TARGET): $(OBJS)
	@echo LD $@ && $(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILDDIR)/%.o: %.cpp
	@if ! [ -d $(dir $@) ]; then  \
	  echo MKDIR $(dir $@) && mkdir -p $(dir $@); \
	fi;
	-@echo CXX $@ && $(CXX) $(CXXFLAGS) -c $< $(OUTPUT_OPTION)

.phony: clean
clean:
	-rm -r $(TARGET) $(OBJS) $(DEPS) test.grader

run: $(TARGET)
	$(TARGET)

.phony: test
test: $(TARGET) $(TESTS_SOL) $(TESTS) $(TESTS_OUT)
	@cat test.grader
	@echo $$(cat test.grader | grep -o passed | wc -w) tests passed
	@grep "failed" test.grader || true # get rid of the non-zero exit code of grep
	@rm test.grader
	