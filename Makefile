include makefile.rules

.PHONY: all clean distclean doc dist check

all:
	gcc ${SDLFLAGS} ${FLAGS} ${FILE} -Iinclude -L./libs -lSDL_image -lSDL_ttf -o ${EXE}
	gcc ${SDLFLAGS} ${FLAGS} ${FILE2} -Iinclude -L./libs -lSDL_image -lSDL_ttf -lm -o ${EXE2}

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	find . -name "*.o" -delete
	find . -name "*~" -delete
	find . -name "*.a" -delete
	find . -name "*#*" -delete
	find . -name "*.log" -delete
	find . -name "*.out" -delete
	find . -name "game"  -delete
	find . -name "map"  -delete
	find . -name "makefile.rules" -delete
	make clean -C src/

distclean: clean
	make distclean -C src/
	rm -rf doc/
	rm -rf el-kam_y-jeuvideo.tar.bz2

doc:
	mkdir doc
	doxygen ./doc/Doxyfile

dist: distclean
