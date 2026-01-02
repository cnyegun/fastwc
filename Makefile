CC      := gcc
CFLAGS  := -O3 -march=native -flto -fno-plt
LDFLAGS := -flto

TARGET  := fastwc
SRC     := fastwc.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)
