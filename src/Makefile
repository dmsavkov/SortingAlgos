include ../Makefile.inc

release : main.r.o 
	$(LD) -o $@ $^

debug   : main.d.o 
	$(LD) -o $@ $^

utest   : test_sorting.d.o 
	$(LD)  -o $@ $^ $(GTEST_LIBS)

run_utest : utest
	./$^

run_itest : debug
	echo "Integration tests..."
	./$^

include Makefile.hdrdep

.PHONY: release debug utest run_utest run_itest
