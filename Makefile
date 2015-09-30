##################################################

# Project name
TARGET   = colorist

# Compiler and flags
CC       = g++
CFLAGS   = -Wall -g -std=c++14

# Linker and flags
LINKER   = g++ -o
LFLAGS   = -Wall -g -std=c++14

# Project directories
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

##################################################

SOURCES  := $(wildcard $(SRCDIR)/*.cxx)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LIBS)
	echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	$(CC) $(CFLAGS) -c $< -o $@ #$(LIBS)
	echo "Compiled "$<" successfully!"

.PHONEY: clean
clean: remove
	$(rm) $(OBJECTS)
	echo "Cleanup complete!"

.PHONEY: remove
remove:
	$(rm) $(BINDIR)/$(TARGET)
	echo "Executable removed!"
