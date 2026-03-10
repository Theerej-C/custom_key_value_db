# 1. Configuration
CC       := gcc
CFLAGS   := -Wall -Wextra -g -Iinclude
TARGET   := bin/my_program

# 2. Directories
SRCDIR   := src
OBJDIR   := obj
BINDIR   := bin

# 3. Files
# Find all .c files in src/
SRCS     := $(wildcard $(SRCDIR)/*.c)
# Convert src/*.c paths to obj/*.o paths
OBJS     := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# 4. Main Build Rules
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 5. Helper Rules
# Create directories if they don't exist
$(BINDIR) $(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
