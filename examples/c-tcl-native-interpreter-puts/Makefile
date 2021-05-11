CC = $(LLVM_TOOLCHAIN)/clang

POLYGLOT_C = export_polyglot_eval_puts
POLYGLOT_TCL = polyglot-puts
POLYGLOT_TCL2 = require

BUILD_FOLDER = build

.PHONY: all
all: $(BUILD_FOLDER)/pkgIndex.tcl $(BUILD_FOLDER)/$(POLYGLOT_TCL2).tcl

$(BUILD_FOLDER)/$(POLYGLOT_C).c: ../$(POLYGLOT_C).c
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_TCL).tcl: ../$(POLYGLOT_TCL).tcl
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_TCL2).tcl: ../$(POLYGLOT_TCL2).tcl
	mkdir -p $(BUILD_FOLDER)/ && cat $^ | sed -e 's/POLYGLOT_C/$(POLYGLOT_C)/g' > $@

$(BUILD_FOLDER)/$(POLYGLOT_C).o: $(BUILD_FOLDER)/$(POLYGLOT_C).c $(BUILD_FOLDER)/$(POLYGLOT_TCL).tcl
	cd $(BUILD_FOLDER)/ && $(CC) -O3 -c $(POLYGLOT_C).c -DPOLYGLOT_C=\"$(POLYGLOT_C)\" -DPOLYGLOT_TCL=\"$(POLYGLOT_TCL).tcl\" -o $(POLYGLOT_C).o

$(BUILD_FOLDER)/lib$(POLYGLOT_C).so: $(BUILD_FOLDER)/$(POLYGLOT_C).o
	cd $(BUILD_FOLDER)/ && $(CC) -O3 -shared $(POLYGLOT_C).o -o lib$(POLYGLOT_C).so

$(BUILD_FOLDER)/pkgIndex.tcl: $(BUILD_FOLDER)/lib$(POLYGLOT_C).so
	cd $(BUILD_FOLDER)/ && printf "pkg_mkIndex ." | tclsh && printf "load lib$(POLYGLOT_C).so $(POLYGLOT_C)" | tclsh

.PHONY: clean
clean:
	rm -r $(BUILD_FOLDER)

.PHONY: start
start: all
	cd $(BUILD_FOLDER)/ && tclsh $(POLYGLOT_TCL2).tcl

.PHONY: time-start
time-start: all
	sh -c "time make start"

.PHONY: time
time: time-start
