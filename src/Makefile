.PHONY : clean

CPPFLAGS= -g -O2 -I. -std=c++11 
LDFLAGS= -shared 

SOURCES = $(shell echo *.cpp)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.cpp=.o)

TARGET=mot.dll

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	cp mot.dll ..
