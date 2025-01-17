CC = g++

SRCDIR = src
INCDIR = include
TESTDIR = tests
BINDIR = bin
LINKDIR = tests/linker

SOURCES = src/exprtreenode.cpp src/symnode.cpp src/symtable.cpp src/eppcompiler.cpp src/heapnode.cpp src/minheap.cpp src/parser.cpp
MAIN_SOURCE = $(TESTDIR)/main.cpp

CFLAGS = -I$(INCDIR) -Wall -std=c++17 -g

TARGET = $(BINDIR)/e++
TESTER = $(BINDIR)/tester

$(TARGET): $(SOURCES) $(MAIN_SOURCE)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Compiler Built Successfully !!"

clean:
	rm -f $(TARGET)

.PHONY: clean

Unix_OS := $(shell uname -s)
ifeq ($(Unix_OS),Darwin)
	TESTER_LINKER := $(LINKDIR)/macos/tester_dep.o
else
	TESTER_LINKER := $(LINKDIR)/linux/tester_dep.o
endif
tester: $(SOURCES) $(TESTER_LINKER)
	@$(CC) $(CFLAGS) -w -o $(TESTER) $^
	@echo "Tester Built Successfully !!"
