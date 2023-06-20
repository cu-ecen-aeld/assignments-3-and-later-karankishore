ifeq ($(CROSS_COMPILE),)
	CC := gcc
else
	CC := $(CROSS_COMPILE)gcc
endif

CFLAGS = -Wall -Wextra -std=c11

APP = writer

all: $(APP)

$(APP): writer.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(APP)

.PHONY: all clean
