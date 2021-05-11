JAVAC = $(GRAALVM_HOME)/bin/javac
JAVA = $(GRAALVM_HOME)/bin/java

POLYGLOT_JAVA = PolyglotFor
LOWER_POLYGLOT_JAVA = $(shell echo $(POLYGLOT_JAVA) | tr A-Z a-z)

#NB_ITERATIONS = 1000000

BUILD_FOLDER = build

.PHONY: all
all: $(BUILD_FOLDER)/$(POLYGLOT_JAVA).class

$(BUILD_FOLDER)/$(POLYGLOT_JAVA).java: ../$(POLYGLOT_JAVA).java
	mkdir -p $(BUILD_FOLDER)/ && cat $^ | sed -e 's/NB_ITERATIONS/$(NB_ITERATIONS)/g' > $@

$(BUILD_FOLDER)/$(POLYGLOT_JAVA).class: $(BUILD_FOLDER)/$(POLYGLOT_JAVA).java
	cd $(BUILD_FOLDER)/ && javac $(POLYGLOT_JAVA).java

$(BUILD_FOLDER)/$(LOWER_POLYGLOT_JAVA): all
	cd $(BUILD_FOLDER)/ && native-image $(POLYGLOT_JAVA)

.PHONY: clean
clean:
	rm -r $(BUILD_FOLDER)

.PHONY: start-java
start-java: all
	cd $(BUILD_FOLDER)/ && java $(POLYGLOT_JAVA)

.PHONY: start-native-image
start-native-image: $(BUILD_FOLDER)/$(LOWER_POLYGLOT_JAVA)
	cd $(BUILD_FOLDER)/ && ./$(LOWER_POLYGLOT_JAVA)

.PHONY: start
start: start-java

.PHONY: time-java
time-java: all
	cd $(BUILD_FOLDER)/ && sh -c "time java $(POLYGLOT_JAVA)"

.PHONY: time-native-image
time-native-image: $(BUILD_FOLDER)/$(LOWER_POLYGLOT_JAVA)
	cd $(BUILD_FOLDER)/ && sh -c "time ./$(LOWER_POLYGLOT_JAVA)"

.PHONY: time
time: time-java
