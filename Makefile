SRCS:=$(shell ls src/*)
OBJS:=$(patsubst src/%.cpp,obj/%.o, $(SRCS))
OBJDIRS:=$(ls $(OBJS))
INC=./include
LIB:=-pthread
DYLIB:=./lib/Effie.dylib

run: $(DYLIB)
	g++ -DDEBUG $(LIB) -I./include -o a.out -std=c++14 -O3 main.cpp $(DYLIB)
	./a.out

test: $(DYLIB)
	g++ $(DYLIB) test/test.cpp -std=c++14 -o test.out -g -pthread -lgtest_main -lgtest -I./include
	./test.out

$(DYLIB): $(OBJDIRS) $(OBJS)
	g++ -dynamiclib  -std=c++14 -o $(DYLIB) $(OBJS)

obj/%.o: $(OBJDIRS) src/%.cpp
	g++ -DDEBUG $(LIB) -I./include -c $+ -std=c++14 -O3 -o $@

$(OBJDIRS):
	mkdir -p $@

clean:
	rm -rf obj lib a.out test.out test.out.*
	mkdir obj
	mkdir lib
