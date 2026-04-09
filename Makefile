


# 1. Configuration
CC       := gcc
CFLAGS   := -Wall -Wextra -g -Iinclude

# 2. Directories
SRCDIR   := src
OBJDIR   := obj
BINDIR   := bin

# 3. Source Files
SRCS        := $(wildcard $(SRCDIR)/*.c)

SERVER_SRC  := $(SRCDIR)/server.c
CLIENT_SRC  := $(SRCDIR)/client.c

# Exclude server.c and client.c from common sources
COMMON_SRCS := $(filter-out $(SERVER_SRC) $(CLIENT_SRC), $(SRCS))

# Object files
COMMON_OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(COMMON_SRCS))
SERVER_OBJ  := $(OBJDIR)/server.o
CLIENT_OBJ  := $(OBJDIR)/client.o

# Targets
SERVER := $(BINDIR)/server
CLIENT := $(BINDIR)/client

# 4. Build Rules
all: $(SERVER) $(CLIENT)

# Link server
$(SERVER): $(SERVER_OBJ) $(COMMON_OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Link client
$(CLIENT): $(CLIENT_OBJ) $(COMMON_OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 5. Helper Rules
$(BINDIR) $(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
