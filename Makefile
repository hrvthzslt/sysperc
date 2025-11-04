.PHONY: build
build:
	gcc -Wall -Wextra -c src/sysperc.c -o build/sysperc.o
	gcc -Wall -Wextra -c src/modules/common.c -o build/modules/common.o
	gcc -Wall -Wextra -c src/modules/cpu.c -o build/modules/cpu.o
	gcc -Wall -Wextra -c src/modules/memory.c -o build/modules/memory.o
	gcc -Wall -Wextra -c src/modules/disk.c -o build/modules/disk.o
	gcc -Wall -Wextra -c src/modules/battery.c -o build/modules/battery.o
	gcc build/*.o build/modules/*.o -o sysperc -lm
	chmod +x sysperc

CMDS = cpup memp batp dskp

install: build
	for cmd in $(CMDS); do ln -sf $(CURDIR)/sysperc /usr/local/bin/$$cmd; done

uninstall:
	for cmd in $(CMDS); do rm -f /usr/local/bin/$$cmd; done
	rm -f sysperc

clean:
	rm -f build/*.o build/modules/*.o

format:
	find . -name "*.c" -o -name "*.h" | xargs clang-format -i
