TARGET = gdkGBA.wasm
CC=clang --target=wasm32 --sysroot=../../wasmlite/libc -nodefaultlibs
CFLAGS = -std=c99 -Wall
LDFLAGS = -Wl,--allow-undefined -Wl,--export-table -Wl,--export=malloc

ifeq ($(DEBUG),0)
CFLAGS += -Oz -ffast-math -flto
LIBS = -lc
else
CFLAGS += -g
LIBS = -lc-dbg
endif

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS += $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h) $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@
ifeq ($(DEBUG),0)
	wasm-opt $@ -o $@ -Oz && wasm-strip $@
else
	../../emscripten/tools/wasm-sourcemap.py $@ -w $@ -p $(CURDIR) -s -u ./$@.map -o $@.map --dwarfdump=/usr/bin/llvm-dwarfdump
endif

clean:
	-rm -f *.o
	-rm -f $(TARGET)

