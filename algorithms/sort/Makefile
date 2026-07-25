CC = gcc
CFLAGS = -Wall -Wextra -I. -pthread

SORTS = bubble insertion selection counter

TARGETS = $(SORTS)

all: $(TARGETS)

debug: CFLAGS += -g -O0
debug: all

define SORT_RULE
$(1): main.o src/$(1)/$(1).o
	$$(CC) $$(CFLAGS) -o $$@ $$^
endef

$(foreach sort,$(SORTS),$(eval $(call SORT_RULE,$(sort))))

main.o: main.c sort.h
	$(CC) $(CFLAGS) -c main.c

src/%.o: src/%.c sort.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS) main.o src/*/*.o

.PHONY: all clean