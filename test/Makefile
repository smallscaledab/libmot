.PHONY : clean

LDFLAGS= -L.. -lmot -std=c++11 -stdlib=libc++

SOURCES = $(shell echo *.cpp)
HEADERS = $(shell echo *.h) $(shell echo *.hpp)
CPPFLAGS = -I../src -std=c++11 -stdlib=libc++ #-Weverything
TARGETS = test_mot test_transportid

all: $(TARGETS)

clean:
	rm $(TARGETS)
