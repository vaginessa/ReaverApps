CC=clang++
LD=clang++
CFLAGS=-c -Os -Wall -Wextra -Werror -pedantic -std=c++1y -stdlib=libc++ -g -MD -pthread
LDFLAGS=-stdlib=libc++ -lc++abi -lc++ -lboost_system -lboost_program_options -lboost_filesystem
SOURCES=$(shell find . -type f -name "*.cpp" ! -path "*-old")
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=raf

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) -lreaver

install: $(EXECUTABLE)
	cp $(EXECUTABLE) /usr/local/bin/

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	@find . -name "*.o" -delete
	@find . -name "*.d" -delete
	@rm -rf $(EXECUTABLE)

-include $(SOURCES:.cpp=.d)
