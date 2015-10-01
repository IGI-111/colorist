##################################################

# Project name
TARGET   = colorist

# Compiler and flags
CC       = g++
CFLAGS   = -Wall -g -std=c++14

# Catch unit testing
CATCHFLAGS = -r compact

# Project directories
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TESTDIR  = src/test

##################################################

rm       = rm -f

SOURCES  := $(wildcard $(SRCDIR)/*.cxx)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)

TEST_SOURCES  := $(wildcard $(TESTDIR)/*.cxx) $(filter-out $(SRCDIR)/main.cxx,$(SOURCES))
TEST_OBJECTS  := $(TEST_SOURCES:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)

all: $(BINDIR)/$(TARGET) test

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(CC) -o $@ $(CFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(sort $(TEST_OBJECTS) $(OBJECTS)): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: test
test: $(BINDIR)/test
	@./$(BINDIR)/test $(CATCHFLAGS)

$(BINDIR)/test : $(TEST_OBJECTS)
	@$(CC) -o $@ $(CFLAGS) $(TEST_OBJECTS)

.PHONEY: clean
clean:
	@$(rm) $(wildcard $(OBJDIR)/*.o $(OBJDIR)/test/*.o) $(BINDIR)/$(TARGET) $(BINDIR)/test
	@echo "Cleanup complete!"
