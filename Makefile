FLAGS = -Werror -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wstrict-prototypes -Wmissing-prototypes -Wformat=2 -D_FORTIFY_SOURCE=2

.PHONY: build
build:
	gcc $(FLAGS) -c src/sysperc.c -o build/sysperc.o
	gcc $(FLAGS) -c src/modules/common.c -o build/modules/common.o
	gcc $(FLAGS) -c src/modules/cpu.c -o build/modules/cpu.o
	gcc $(FLAGS) -c src/modules/memory.c -o build/modules/memory.o
	gcc $(FLAGS) -c src/modules/disk.c -o build/modules/disk.o
	gcc $(FLAGS) -c src/modules/battery.c -o build/modules/battery.o
	gcc build/*.o build/modules/*.o -o sysperc -lm
	chmod +x sysperc

CMDS = cpup memp batp dskp

install: build
	for cmd in $(CMDS); do ln -sf $(CURDIR)/sysperc /usr/local/bin/$$cmd; done

install-local: build
	for cmd in $(CMDS); do ln -sf $(CURDIR)/sysperc $(HOME)/.local/bin/$$cmd; done

uninstall:
	for cmd in $(CMDS); do rm -f /usr/local/bin/$$cmd; done
	rm -f sysperc

uninstall-local:
	for cmd in $(CMDS); do rm -f $(HOME)/.local/bin/$$cmd; done
	rm -f sysperc

clean:
	rm -f build/*.o build/modules/*.o

format:
	find . -name "*.c" -o -name "*.h" | xargs clang-format -i
