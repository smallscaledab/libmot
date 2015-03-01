.PHONY : clean

CPPFLAGS= -g -O2 -I../src -std=c++11 -I..
LDFLAGS= -L../src -lmot

SOURCES = $(shell echo *.cpp)
HEADERS = $(shell echo *.h) $(shell echo *.hpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGETS = $(OBJECTS:.o=.exe)

all: $(TARGETS)

clean:
	rm -f $(OBJECTS) $(TARGETS)
	
%.o : %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<
	
%.exe : %.o
	@echo target
	$(CXX) $< -o $@ $(LDFLAGS)