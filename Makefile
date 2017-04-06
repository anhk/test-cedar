

all: cedar.so test

INC ?= -I /usr/local/LuaJit/LuaJIT-2.1.0-beta2/include/luajit-2.1/


cedar.so: cedar.cc
	g++ -g -o $@ $^ ${INC} -fPIC -shared

test: test.cc
	g++ -g -o $@ $^

clean:
	rm -fr cedar.so test
