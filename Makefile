
C_SRC := $(wildcard *.c)
ASM_SRC = example_5.S

BINS := $(patsubst %.c, %.bin, $(C_SRC))

all : $(BINS)

%.bin : %.c
	gcc -o $(@) $^

5_example.bin : $(ASM_SRC)
	gcc -c $^
	ld -o eg_5.bin example_5.o
	gcc -o $(@) 5_example.c 

clean:
	rm -rf $(BINS) eg_5.bin example_5.o
