OUT=nagaram

FILES_COMPILE=*.cpp
FILES_DEPEND=$(FILES_COMPILE) Makefile *.hpp

CC_FLAGS=--std=c++17 -lssl -lcrypto -Wall -Wextra -O2 -march=native -g -fsanitize=address

$(OUT): $(FILES_DEPEND)
	clang++ $(FILES_COMPILE) -o $(OUT) $(CC_FLAGS)
	#strip -s $(OUT)

.PHONY: clean run

clean:
	-rm $(OUT)

run: $(OUT)
	./$(OUT)
