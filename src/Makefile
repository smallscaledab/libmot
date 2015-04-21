.PHONY : clean

TARGET = libmot.a

CPPFLAGS = -I../../libmot/src -g -std=c++11 -stdlib=libc++
LDFLAGS= -shared -stdlib=libc++

SOURCES = $(shell echo *.cpp)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

clean:
	rm $(OBJECTS)

$(TARGET) : $(OBJECTS)
	$(CXX) $(OBJECTS) -o ../$@ $(LDFLAGS)
