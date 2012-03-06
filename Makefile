# Macros and existing pseudo-targets should not be modified.
# There is a section to add new pseudo-targets commented below.

CFLAGS = -c -g -Wall -Werror
LFLAGS = -L lib/ -l cs240utils

LIBOBJ = utils/obj
LIBOBJ_FILES = $(LIBOBJ)/StringUtil.o $(LIBOBJ)/URLInputStream.o \
  $(LIBOBJ)/FileInputStream.o $(LIBOBJ)/HTTPInputStream.o \
  $(LIBOBJ)/CommandRunner.o $(LIBOBJ)/FileSystem.o $(LIBOBJ)/HTMLToken.o \
  $(LIBOBJ)/HTMLTokenizer.o

SRC_OBJ = obj
SRC_OBJ_FILES = $(SRC_OBJ)/URL.o $(SRC_OBJ)/Page.o $(SRC_OBJ)/PageQueue.o \
  $(SRC_OBJ)/PageSet.o $(SRC_OBJ)/StopWords.o $(SRC_OBJ)/Occurrence.o \
  $(SRC_OBJ)/WordIndex.o

SRC = src
INCLUDE = inc
LIB_INCLUDE = utils/include

LIB_SRC = utils/src

bin: bin/crawler 
lib: lib/libcs240utils.a
test: bin/testdriver run-test
clean: 
	- rm -f bin/* lib/*.a $(SRC_OBJ)/* $(LIBOBJ)/*
run-test:
	bin/testdriver
check-style:
	~cs240ta/bin/CppCheckStyle/CppCheckStyle $(SRC)/*.cpp $(INCLUDE)/*.h
valgrind: bin/testdriver
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	  --show-reachable=yes --suppressions=valgrind/string.supp bin/testdriver

# Add new pseudo-targets here

.PHONY: bin lib test clean run-test check-style


# These are the only dependency lines that may change during development

bin/crawler: $(SRC_OBJ)/helloMake.o lib/libcs240utils.a
	g++ -o bin/crawler $(SRC_OBJ)/helloMake.o $(LFLAGS)

bin/testdriver: $(SRC_OBJ)/testDriver.o $(SRC_OBJ_FILES) lib/libcs240utils.a
	g++ -o bin/testdriver $(SRC_OBJ)/testDriver.o $(SRC_OBJ_FILES) $(LFLAGS)


# Dependencies lines beyond this point should not change

lib/libcs240utils.a: $(LIBOBJ_FILES)
	ar r lib/libcs240utils.a $(LIBOBJ_FILES)

$(SRC_OBJ)/helloMake.o: $(SRC)/helloMake.cpp
	g++ -o $(SRC_OBJ)/helloMake.o $(CFLAGS) $(SRC)/helloMake.cpp

$(SRC_OBJ)/URL.o: $(SRC)/URL.cpp $(INCLUDE)/URL.h $(LIB_INCLUDE)/UnitTest.h
	g++ -o $(SRC_OBJ)/URL.o $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) $(SRC)/URL.cpp

$(SRC_OBJ)/Page.o: $(SRC)/Page.cpp $(INCLUDE)/URL.h $(INCLUDE)/Page.h
	g++ -o $(SRC_OBJ)/Page.o $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) $(SRC)/Page.cpp

$(SRC_OBJ)/PageQueue.o: $(SRC)/PageQueue.cpp $(INCLUDE)/*.h $(LIB_INCLUDE)/*.h
	g++ -o $(SRC_OBJ)/PageQueue.o $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) $(SRC)/PageQueue.cpp

$(SRC_OBJ)/PageSet.o: $(SRC)/PageSet.cpp $(INCLUDE)/*.h $(LIB_INCLUDE)/*.h
	g++ -o $(SRC_OBJ)/PageSet.o $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) $(SRC)/PageSet.cpp

$(SRC_OBJ)/StopWords.o: $(SRC)/StopWords.cpp $(INCLUDE)/*.h $(LIB_INCLUDE)/*.h
	g++ -o $(SRC_OBJ)/StopWords.o $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) $(SRC)/StopWords.cpp

$(SRC_OBJ)/Occurrence.o: $(SRC)/Occurrence.cpp $(INCLUDE)/*.h $(LIB_INCLUDE)/*.h
	g++ -o $(SRC_OBJ)/Occurrence.o $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) $(SRC)/Occurrence.cpp

$(SRC_OBJ)/WordIndex.o: $(SRC)/WordIndex.cpp $(INCLUDE)/*.h $(LIB_INCLUDE)/*.h
	g++ -o $(SRC_OBJ)/WordIndex.o $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) $(SRC)/WordIndex.cpp

$(SRC_OBJ)/testDriver.o: $(SRC)/testDriver.cpp $(INCLUDE)/* $(LIB_INCLUDE)/UnitTest.h
	g++ -o $(SRC_OBJ)/testDriver.o $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) $(SRC)/testDriver.cpp

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

