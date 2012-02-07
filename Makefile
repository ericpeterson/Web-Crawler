CFLAGS = -c -g -Wall -I
LFLAGS = -L lib/ -l cs240utils

LIBOBJ = utils/obj
LIBOBJ_FILES = $(LIBOBJ)/StringUtil.o $(LIBOBJ)/URLInputStream.o \
  $(LIBOBJ)/FileInputStream.o $(LIBOBJ)/HTTPInputStream.o \
  $(LIBOBJ)/CommandRunner.o $(LIBOBJ)/FileSystem.o $(LIBOBJ)/HTMLToken.o \
  $(LIBOBJ)/HTMLTokenizer.o


bin: bin/crawler 
lib: lib/libcs240utils.a
test: bin/testdriver run-test
clean: 
	- rm -f bin/* lib/*.a obj/* $(LIBOBJ)/*
run-test:
	bin/testdriver


.PHONY: bin lib test clean run-test 


bin/crawler: obj/helloMake.o lib/libcs240utils.a
	g++ -o bin/crawler obj/helloMake.o $(LFLAGS)

bin/testdriver: obj/testDriver.o lib/libcs240utils.a
	g++ -o bin/testdriver obj/testDriver.o $(LFLAGS) 

lib/libcs240utils.a: $(LIBOBJ_FILES)
	ar r lib/libcs240utils.a $(LIBOBJ_FILES)

obj/helloMake.o: src/helloMake.cpp
	g++ -o obj/helloMake.o $(CFLAGS) inc/ src/helloMake.cpp 

obj/testDriver.o: src/testDriver.cpp
	g++ -o obj/testDriver.o $(CFLAGS) inc/ src/testDriver.cpp

$(LIBOBJ)/StringUtil.o: utils/src/StringUtil.cpp utils/include/StringUtil.h
	g++ -o $(LIBOBJ)/StringUtil.o $(CFLAGS) utils/include/ utils/src/StringUtil.cpp

$(LIBOBJ)/URLInputStream.o: utils/src/URLInputStream.cpp utils/include/URLInputStream.h
	g++ -o $(LIBOBJ)/URLInputStream.o $(CFLAGS) utils/include/ utils/src/URLInputStream.cpp

$(LIBOBJ)/FileInputStream.o: utils/src/FileInputStream.cpp utils/include/FileInputStream.h
	g++ -o $(LIBOBJ)/FileInputStream.o $(CFLAGS) utils/include/ utils/src/FileInputStream.cpp
	
$(LIBOBJ)/HTTPInputStream.o: utils/src/HTTPInputStream.cpp utils/include/HTTPInputStream.h
	g++ -o $(LIBOBJ)/HTTPInputStream.o $(CFLAGS) utils/include/ utils/src/HTTPInputStream.cpp

$(LIBOBJ)/CommandRunner.o: utils/src/CommandRunner.cpp utils/include/CommandRunner.h
	g++ -o $(LIBOBJ)/CommandRunner.o $(CFLAGS) utils/include/ utils/src/CommandRunner.cpp

$(LIBOBJ)/FileSystem.o: utils/src/FileSystem.cpp utils/include/FileSystem.h
	g++ -o $(LIBOBJ)/FileSystem.o $(CFLAGS) utils/include/ utils/src/FileSystem.cpp

$(LIBOBJ)/HTMLToken.o: utils/src/HTMLToken.cpp utils/include/HTMLToken.h
	g++ -o $(LIBOBJ)/HTMLToken.o $(CFLAGS) utils/include/ utils/src/HTMLToken.cpp

$(LIBOBJ)/HTMLTokenizer.o: utils/src/HTMLTokenizer.cpp utils/include/HTMLTokenizer.h
	g++ -o $(LIBOBJ)/HTMLTokenizer.o $(CFLAGS) utils/include/ utils/src/HTMLTokenizer.cpp

