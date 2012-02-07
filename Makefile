CFLAGS = -c -g -Wall
LFLAGS = -L lib/ -l cs240utils

LIBOBJ = utils/obj
LIBOBJ_FILES = $(LIBOBJ)/StringUtil.o $(LIBOBJ)/URLInputStream.o \
  $(LIBOBJ)/FileInputStream.o $(LIBOBJ)/HTTPInputStream.o \
  $(LIBOBJ)/CommandRunner.o $(LIBOBJ)/FileSystem.o $(LIBOBJ)/HTMLToken.o \
  $(LIBOBJ)/HTMLTokenizer.o

INCLUDE = inc
LIB_INCLUDE = utils/include

LIB_SRC = utils/src

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
	g++ -o obj/helloMake.o $(CFLAGS) src/helloMake.cpp

obj/testDriver.o: src/testDriver.cpp
	g++ -o obj/testDriver.o $(CFLAGS) src/testDriver.cpp

$(LIBOBJ)/StringUtil.o: $(LIB_SRC)/StringUtil.cpp $(LIB_INCLUDE)/StringUtil.h
	g++ -o $(LIBOBJ)/StringUtil.o $(CFLAGS) -I $(LIB_INCLUDE) $(LIB_SRC)/StringUtil.cpp

$(LIBOBJ)/URLInputStream.o: $(LIB_SRC)/URLInputStream.cpp $(LIB_INCLUDE)/StringUtil.h \
  $(LIB_INCLUDE)/CS240Exception.h $(LIB_INCLUDE)/HTTPInputStream.h \
  $(LIB_INCLUDE)/InputStream.h $(LIB_INCLUDE)/FileInputStream.h \
  $(LIB_INCLUDE)/URLInputStream.h
	g++ -o $(LIBOBJ)/URLInputStream.o $(CFLAGS) -I $(LIB_INCLUDE) $(LIB_SRC)/URLInputStream.cpp

$(LIBOBJ)/FileInputStream.o: $(LIB_SRC)/FileInputStream.cpp $(LIB_INCLUDE)/FileInputStream.h \
  $(LIB_INCLUDE)/InputStream.h
	g++ -o $(LIBOBJ)/FileInputStream.o $(CFLAGS) -I $(LIB_INCLUDE) $(LIB_SRC)/FileInputStream.cpp
	
$(LIBOBJ)/HTTPInputStream.o: $(LIB_SRC)/HTTPInputStream.cpp $(LIB_INCLUDE)/CS240Exception.h \
  $(LIB_INCLUDE)/StringUtil.h $(LIB_INCLUDE)/HTTPInputStream.h $(LIB_INCLUDE)/InputStream.h
	g++ -o $(LIBOBJ)/HTTPInputStream.o $(CFLAGS) -I $(LIB_INCLUDE) $(LIB_SRC)/HTTPInputStream.cpp

$(LIBOBJ)/CommandRunner.o: $(LIB_SRC)/CommandRunner.cpp $(LIB_INCLUDE)/CS240Exception.h \
  $(LIB_INCLUDE)/StringUtil.h $(LIB_INCLUDE)/CommandRunner.h
	g++ -o $(LIBOBJ)/CommandRunner.o $(CFLAGS) -I $(LIB_INCLUDE) $(LIB_SRC)/CommandRunner.cpp

$(LIBOBJ)/FileSystem.o: $(LIB_SRC)/FileSystem.cpp $(LIB_INCLUDE)/FileSystem.h \
  $(LIB_INCLUDE)/CS240Exception.h $(LIB_INCLUDE)/UnitTest.h
	g++ -o $(LIBOBJ)/FileSystem.o $(CFLAGS) -I $(LIB_INCLUDE) $(LIB_SRC)/FileSystem.cpp

$(LIBOBJ)/HTMLToken.o: $(LIB_SRC)/HTMLToken.cpp $(LIB_INCLUDE)/HTMLToken.h
	g++ -o $(LIBOBJ)/HTMLToken.o $(CFLAGS) -I $(LIB_INCLUDE) $(LIB_SRC)/HTMLToken.cpp

$(LIBOBJ)/HTMLTokenizer.o: $(LIB_SRC)/HTMLTokenizer.cpp $(LIB_INCLUDE)/HTMLTokenizer.h \
  $(LIB_INCLUDE)/URLInputStream.h $(LIB_INCLUDE)/InputStream.h $(LIB_INCLUDE)/HTMLToken.h
	g++ -o $(LIBOBJ)/HTMLTokenizer.o $(CFLAGS) -I $(LIB_INCLUDE) $(LIB_SRC)/HTMLTokenizer.cpp

