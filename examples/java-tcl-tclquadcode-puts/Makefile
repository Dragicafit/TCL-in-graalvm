CC = $(LLVM_TOOLCHAIN)/clang
TCLC = tclsh
LLVM_AS = $(GRAALVM_HOME)/lib/llvm/bin/llvm-as

POLYGLOT_TCL = java-tcl-native-puts
POLYGLOT_JAVA = HelloPolyglot

all: ELF class

llvm:
	$(TCLC) $(POLYGLOT_TCL).tcl > $(POLYGLOT_TCL).ll

bitecode: llvm
	$(LLVM_AS) $(POLYGLOT_TCL).ll

ELF: bitecode
	$(CC) $(POLYGLOT_TCL).bc -ltcl -o $(POLYGLOT_TCL)

class:
	javac $(POLYGLOT_JAVA).java

clean:
	rm *.ll *.class *.bc $(POLYGLOT_TCL)

start:
	java $(POLYGLOT_JAVA) $(POLYGLOT_TCL)