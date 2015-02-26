.PHONY : clean

CXX=g++
CPPFLAGS= -g -O2 -I. -ltypes
LDFLAGS= -shared 

SOURCES = $(shell echo *.cpp)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.cpp=.o)

TARGET=mot.so

all: $(TARGET) tests

clean:
	rm -f $(OBJECTS) $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	
tests: test_mot

test_mot : test_mot.o
	$(CXX) $(CFLAGS) test_mot.o -o $@ $(LDFLAGS) -L. -lmot

