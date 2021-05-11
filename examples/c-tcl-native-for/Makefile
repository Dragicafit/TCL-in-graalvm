CC = $(LLVM_TOOLCHAIN)/clang

POLYGLOT_C = export_for
POLYGLOT_TCL = require-for

#NB_ITERATIONS = 1000000

BUILD_FOLDER = build

.PHONY: all
all: $(BUILD_FOLDER)/pkgIndex.tcl $(BUILD_FOLDER)/$(POLYGLOT_TCL).tcl

$(BUILD_FOLDER)/$(POLYGLOT_C).c: ../$(POLYGLOT_C).c
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_TCL).tcl: ../$(POLYGLOT_TCL).tcl
	mkdir -p $(BUILD_FOLDER)/ && cat $^ | sed -e 's/POLYGLOT_C/$(POLYGLOT_C)/g' -e 's/NB_ITERATIONS/$(NB_ITERATIONS)/g' > $@

$(BUILD_FOLDER)/$(POLYGLOT_C).o: $(BUILD_FOLDER)/$(POLYGLOT_C).c
	cd $(BUILD_FOLDER)/ && $(CC) -O3 -c $(POLYGLOT_C).c -DPOLYGLOT_C=\"$(POLYGLOT_C)\" -o $(POLYGLOT_C).o

$(BUILD_FOLDER)/lib$(POLYGLOT_C).so: $(BUILD_FOLDER)/$(POLYGLOT_C).o
	cd $(BUILD_FOLDER)/ && $(CC) -O3 -shared $(POLYGLOT_C).o -o lib$(POLYGLOT_C).so

$(BUILD_FOLDER)/pkgIndex.tcl: $(BUILD_FOLDER)/lib$(POLYGLOT_C).so
	cd $(BUILD_FOLDER)/ && printf "pkg_mkIndex ." | tclsh && printf "load lib$(POLYGLOT_C).so $(POLYGLOT_C)" | tclsh

.PHONY: clean
clean:
	rm -r $(BUILD_FOLDER)

.PHONY: start
start: all
	cd $(BUILD_FOLDER)/ && tclsh $(POLYGLOT_TCL).tcl

.PHONY: time-start
time-start: all
	sh -c "time make start"

.PHONY: time
time: time-start
