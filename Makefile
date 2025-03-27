TARGET = DemaxNet
PREF_SRC = ./src/
CSRC := $(wildcard $(PREF_SRC)*.c)
COBJ := $(patsubst %.c, %.o, $(CSRC))
COBJ := $(subst src,build, $(COBJ))

DIR := ${CURDIR}

FLAGS := -I$(DIR)\include

CC = gcc $(FLAGS)
LD = gcc

build: $(TARGET)
	@echo sources = $(CSRC)
	@echo objects = $(COBJ)
	rm build/*.o
$(TARGET): $(COBJ)
	$(LD) $(COBJ) -o $(TARGET).exe
%.o:
	$(CC) -c $(subst .o,.c,$(subst build,src, $@)) -o $@
debug:
	@echo sources = $(CSRC)
	@echo objects = $(COBJ)