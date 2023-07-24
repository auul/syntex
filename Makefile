BIN=syntex
LDFLAGS=-lm -lSDL2 -lSDL2_image
INCDIRS=. ./include
SRCDIRS=. ./src

CC=cc
OPT=-O0
DEPFLAGS=-MP -MD
WFLAGS=-Wall -Wextra
INCFLAGS=$(foreach D,$(INCDIRS),-I$(D))
CFLAGS=$(WFLAGS) $(INCFLAGS) $(OPT) $(DEPFLAGS)

INCFILES=$(foreach D,$(INCDIRS),$(wildcard $(D)/*.h))
SRCFILES=$(foreach D,$(SRCDIRS),$(wildcard $(D)/*.c))
OBJFILES=$(patsubst %.c,%.o,$(SRCFILES))
DEPFILES=$(patsubst %.c,%.d,$(SRCFILES))

all:$(BIN)

$(BIN): $(OBJFILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(BIN)

%.o: %.c $(INCFILES) makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) $(OBJFILES) $(DEPFILES)

test: $(BIN)
	./$(BIN)

.PHONY:
	all clean test
