TCLSH = tclsh
CC = $(LLVM_TOOLCHAIN)/clang
LLVM_AS = $(GRAALVM_HOME)/lib/llvm/bin/llvm-as

POLYGLOT_C = export_polyglot_eval_puts
POLYGLOT_TCL = polyglot-puts
POLYGLOT_TCL2 = require
POLYGLOT_C2 = polyglot-eval
POLYGLOT_JAVA = PolyglotEval
LOWER_POLYGLOT_JAVA = $(shell echo $(POLYGLOT_JAVA) | tr A-Z a-z)

BUILD_FOLDER = build

.PHONY: all
all: $(BUILD_FOLDER)/pkgIndex.tcl $(BUILD_FOLDER)/$(POLYGLOT_TCL2).tcl $(BUILD_FOLDER)/$(POLYGLOT_C2) $(BUILD_FOLDER)/$(POLYGLOT_JAVA).class

$(BUILD_FOLDER)/$(POLYGLOT_C).c: ../$(POLYGLOT_C).c
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_TCL).tcl: ../$(POLYGLOT_TCL).tcl
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_TCL2).tcl: ../$(POLYGLOT_TCL2).tcl
	mkdir -p $(BUILD_FOLDER)/ && cat $^ | sed -e 's/POLYGLOT_C/$(POLYGLOT_C)/g' > $@

$(BUILD_FOLDER)/$(POLYGLOT_C2).c: ../$(POLYGLOT_C2).c
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_JAVA).java: ../$(POLYGLOT_JAVA).java
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_C).o: $(BUILD_FOLDER)/$(POLYGLOT_C).c $(BUILD_FOLDER)/$(POLYGLOT_TCL).tcl
	cd $(BUILD_FOLDER)/ && $(CC) -O3 -c $(POLYGLOT_C).c -DPOLYGLOT_C=\"$(POLYGLOT_C)\" -DPOLYGLOT_TCL=\"$(POLYGLOT_TCL).tcl\" -o $(POLYGLOT_C).o

$(BUILD_FOLDER)/lib$(POLYGLOT_C).so: $(BUILD_FOLDER)/$(POLYGLOT_C).o
	cd $(BUILD_FOLDER)/ && $(CC) -O3 -shared $(POLYGLOT_C).o -ltcl -o lib$(POLYGLOT_C).so

$(BUILD_FOLDER)/pkgIndex.tcl: $(BUILD_FOLDER)/lib$(POLYGLOT_C).so
	cd $(BUILD_FOLDER)/ && printf "pkg_mkIndex ." | tclsh && printf "load lib$(POLYGLOT_C).so $(POLYGLOT_C)" | tclsh

$(BUILD_FOLDER)/$(POLYGLOT_C2).ll: $(BUILD_FOLDER)/$(POLYGLOT_C2).c $(BUILD_FOLDER)/$(POLYGLOT_TCL2).tcl
	cd $(BUILD_FOLDER)/ && $(CC) -O3 -S $(POLYGLOT_C2).c -emit-llvm -DPOLYGLOT_TCL=\"$(POLYGLOT_TCL2).tcl\" -o $(POLYGLOT_C2).ll

$(BUILD_FOLDER)/$(POLYGLOT_C2).bc: $(BUILD_FOLDER)/$(POLYGLOT_C2).ll
	cd $(BUILD_FOLDER)/ && $(LLVM_AS) $(POLYGLOT_C2).ll -o $(POLYGLOT_C2).bc

$(BUILD_FOLDER)/$(POLYGLOT_C2): $(BUILD_FOLDER)/$(POLYGLOT_C2).bc
	cd $(BUILD_FOLDER)/ && $(CC) -O3 $(POLYGLOT_C2).bc -ltcl -o $(POLYGLOT_C2)

$(BUILD_FOLDER)/$(POLYGLOT_JAVA).class: $(BUILD_FOLDER)/$(POLYGLOT_JAVA).java
	cd $(BUILD_FOLDER)/ && javac $(POLYGLOT_JAVA).java

$(BUILD_FOLDER)/$(LOWER_POLYGLOT_JAVA): $(BUILD_FOLDER)/$(POLYGLOT_JAVA).class
	cd $(BUILD_FOLDER)/ && native-image $(POLYGLOT_JAVA)

.PHONY: clean
clean:
	rm -r $(BUILD_FOLDER)

.PHONY: start
start: all
	cd $(BUILD_FOLDER)/ && $(TCLSH) $(POLYGLOT_TCL2).tcl

.PHONY: time
time: all
	cd $(BUILD_FOLDER)/ && sh -c "time $(TCLSH) $(POLYGLOT_TCL2).tcl" && sh -c "time ./$(POLYGLOT_C2)" && sh -c "time lli $(POLYGLOT_C2)" && sh -c "time java $(POLYGLOT_JAVA) $(POLYGLOT_C2)"
