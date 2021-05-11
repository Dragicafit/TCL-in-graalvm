CC = $(LLVM_TOOLCHAIN)/clang
LLVM_AS = $(GRAALVM_HOME)/lib/llvm/bin/llvm-as

POLYGLOT_C = for
POLYGLOT_JAVA = PolyglotEval
LOWER_POLYGLOT_JAVA = $(shell echo $(POLYGLOT_JAVA) | tr A-Z a-z)

#NB_ITERATIONS = 1000000

BUILD_FOLDER = build

.PHONY: all
all: $(BUILD_FOLDER)/$(POLYGLOT_C).so $(BUILD_FOLDER)/$(POLYGLOT_JAVA).class

$(BUILD_FOLDER)/$(POLYGLOT_C).c: ../$(POLYGLOT_C).c
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_JAVA).java: ../$(POLYGLOT_JAVA).java
	mkdir -p $(BUILD_FOLDER)/ && cp $^ $$_

$(BUILD_FOLDER)/$(POLYGLOT_C).so: $(BUILD_FOLDER)/$(POLYGLOT_C).c
	cd $(BUILD_FOLDER)/ && $(CC) -shared $(POLYGLOT_C).c -lgraalvm-llvm -DNB_ITERATIONS=$(NB_ITERATIONS) -o $(POLYGLOT_C).so

$(BUILD_FOLDER)/$(POLYGLOT_JAVA).class: $(BUILD_FOLDER)/$(POLYGLOT_JAVA).java
	cd $(BUILD_FOLDER)/ && javac $(POLYGLOT_JAVA).java

$(BUILD_FOLDER)/$(LOWER_POLYGLOT_JAVA): $(BUILD_FOLDER)/$(POLYGLOT_JAVA).class
	cd $(BUILD_FOLDER)/ && native-image $(POLYGLOT_JAVA)

.PHONY: clean
clean:
	rm -r $(BUILD_FOLDER)

.PHONY: start
start: all
	cd $(BUILD_FOLDER)/ && lli $(POLYGLOT_C).so

.PHONY: time
time: all
	cd $(BUILD_FOLDER)/ && sh -c "time lli $(POLYGLOT_C).so" && sh -c "time java $(POLYGLOT_JAVA) $(POLYGLOT_C).so"
