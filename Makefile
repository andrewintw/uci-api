CC := $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Iinc -MMD
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEP = $(OBJ:.o=.d)
TARGET = $(BINDIR)/uci_program

all: clean $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) -g $(CFLAGS) $^ -o $@ -luci

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -g $(CFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: clean

