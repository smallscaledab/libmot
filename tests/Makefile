.PHONY : clean

LDFLAGS= -L.. -lmot -std=c++11 -stdlib=libc++

SOURCES = $(shell echo *.cpp)
HEADERS = $(shell echo *.h) $(shell echo *.hpp)
OBJECTS = $(SOURCES:.cpp=.o)

UNAME := $(shell uname)
ifeq ($(UNAME), Windows_NT)
	CPPFLAGS = -I../src
	TARGETS = $(OBJECTS:.o=.exe)
else
	CXX = clang++ 
	CPPFLAGS = -I../src -std=c++11 -stdlib=libc++ #-Weverything
	TARGETS = $(OBJECTS:.o=)
endif

all: $(TARGETS)

clean:
	rm $(OBJECTS) $(TARGETS)
	
%.o : %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<
	
%.exe : %.o
	@echo target
	$(CXX) $< -o $@ $(LDFLAGS)
	chmod +x $@