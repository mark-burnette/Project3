SOURCE_FILES = $(wildcard *.cpp)
HEADER_FILES = $(wildcard *.h)

main: $(SOURCE_FILES) $(HEADER_FILES)
	g++ -std=c++14 -Werror -Wuninitialized -o bin $(SOURCE_FILES)
