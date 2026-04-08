include ../Makefile

BUILD_DIR = ../build

all: release debug utest

release : $(BUILD_DIR)/release
debug   : $(BUILD_DIR)/debug
utest   : $(BUILD_DIR)/utest

$(BUILD_DIR)/release : main.r.o 
	mkdir -p "$(BUILD_DIR)"
	$(LD) -o $@ $^

$(BUILD_DIR)/debug : main.d.o 
	mkdir -p "$(BUILD_DIR)"
	$(LD) -o $@ $^

$(BUILD_DIR)/utest : test_sorting.d.o 
	mkdir -p "$(BUILD_DIR)"
	$(LD) -o $@ $^ $(GTEST_LIBS)

run_utest : utest
	$(BUILD_DIR)/utest

run_itest : debug
	@echo "Integration tests..."
	$(BUILD_DIR)/debug

include Makefile.hdrdep

.PHONY: all release debug utest run_utest run_itest
