PREFIX=/usr/local

all: electrotest-standalone

electrotest-standalone:
	gcc electrotest-standalone.c -o electrotest-standalone -lm

#install: src/electrotest-standalone
	cp -f electrotest-standalone /usr/local/bin

clean:
	rm -f electrotest-standalone electrotest-standalone.o

#distclean: clean

uninstall:
	rm -rf /usr/local/bin/electrotest-standalone

.PHONY: all install clean distclean uninstall
