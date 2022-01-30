## See LICENSE file for copyright and license details.

PROGRAM = net

CC  = gcc
CPP = g++
CCFLAGS = -std=c++20 -O2 -g -Wall -Wextra -Wpedantic
LDFLAGS = -flto
LIBS    = -lm

V =

ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

ifeq ($(uname_S),Linux)
	DEFINES = -DAUTOCONF -DPOSIX -DUSG -D_XOPEN_SOURCE=600 -D_GNU_SOURCE
endif
ifeq ($(uname_S),FreeBSD)
	DEFINES = -DAUTOCONF -DPOSIX -DSYSV -D_FREEBSD_C_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_XOPEN_SOURCE=600
endif
ifeq ($(uname_S),Darwin)
	DEFINES = -DAUTOCONF -DPOSIX -DSYSV -D_DARWIN_C_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_XOPEN_SOURCE=600
endif

SRC  = $(shell find src -name "*.cpp")
OBJ  = $(SRC:.cpp=.o)
BIN  = bin

all: dirs build

fmt:
	$(E) "  FMT"
	$(Q) clang-format -i $(SRC)

dirs:
	$(E) "  DIRS"
	$(Q) mkdir -p ./$(BIN)

run: build
	$(E) "  RUN"
	$(E)
	$(BIN)/$(PROGRAM) input.csv

build: dirs $(OBJ)
	$(E) "  LINK  " $(BIN)/$(PROGRAM)
	$(Q) $(CPP) -o $(BIN)/$(PROGRAM) $(filter %.o,$^) $(LDFLAGS) $(DEFINES)

%.o: %.cpp
	$(E) "  CPP   " $@
	$(Q) $(CPP) -o $@ -c $< $(CCFLAGS)

clean:
	$(E) "  CLEAN"
	$(Q) rm -rf $(BIN) $(OBJ)
