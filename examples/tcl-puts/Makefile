TCLSH = tclsh
CC = $(LLVM_TOOLCHAIN)/clang
LLVM_AS = $(GRAALVM_HOME)/lib/llvm/bin/llvm-as

POLYGLOT_TCL = puts
POLYGLOT_C = polyglot-eval
POLYGLOT_JAVA = PolyglotEval
LOWER_POLYGLOT_JAVA = $(shell echo $(POLYGLOT_JAVA) | tr A-Z a-z)

BUILD_FOLDER = build

.PHONY: all
all: $(BUILD_FOLDER)/$(POLYGLOT_C) $(BUILD_FOLDER)/$(POLYGLOT_JAVA).class

$(BUILD_FOLDER)/$(POLYGLOT_TCL).tcl: ../$(POLYGLOT_TCL).tcl
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_C).c: ../$(POLYGLOT_C).c
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_JAVA).java: ../$(POLYGLOT_JAVA).java
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_C).ll: $(BUILD_FOLDER)/$(POLYGLOT_C).c $(BUILD_FOLDER)/$(POLYGLOT_TCL).tcl
	cd $(BUILD_FOLDER)/ && $(CC) -O3 -S $(POLYGLOT_C).c -emit-llvm -DPOLYGLOT_TCL=\"$(POLYGLOT_TCL).tcl\" -o $(POLYGLOT_C).ll

$(BUILD_FOLDER)/$(POLYGLOT_C).bc: $(BUILD_FOLDER)/$(POLYGLOT_C).ll
	cd $(BUILD_FOLDER)/ && $(LLVM_AS) $(POLYGLOT_C).ll -o $(POLYGLOT_C).bc

$(BUILD_FOLDER)/$(POLYGLOT_C): $(BUILD_FOLDER)/$(POLYGLOT_C).bc
	cd $(BUILD_FOLDER)/ && $(CC) -O3 $(POLYGLOT_C).bc -ltcl -o $(POLYGLOT_C)

$(BUILD_FOLDER)/$(POLYGLOT_JAVA).class: $(BUILD_FOLDER)/$(POLYGLOT_JAVA).java
	cd $(BUILD_FOLDER)/ && javac $(POLYGLOT_JAVA).java

$(BUILD_FOLDER)/$(LOWER_POLYGLOT_JAVA): $(BUILD_FOLDER)/$(POLYGLOT_JAVA).class
	cd $(BUILD_FOLDER)/ && native-image $(POLYGLOT_JAVA)

.PHONY: clean
clean:
	rm -r $(BUILD_FOLDER)

.PHONY: start
start: all
	cd $(BUILD_FOLDER)/ && $(TCLSH) $(POLYGLOT_TCL).tcl

.PHONY: time
time: all
	cd $(BUILD_FOLDER)/ && sh -c "time $(TCLSH) $(POLYGLOT_TCL).tcl" && sh -c "time ./$(POLYGLOT_C)" && sh -c "time lli $(POLYGLOT_C)" && sh -c "time java $(POLYGLOT_JAVA) $(POLYGLOT_C)"
