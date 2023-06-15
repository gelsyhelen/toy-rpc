CC := gcc

PACKAGES := \
	drmollineda.so \
	gelsyhelen.so

%.so: proc_%.c
	$(CC) -shared -fpic -o $@ $^ -lm

all: ${PACKAGES}

clean:
	rm -rf *.o *.so
