SRCS := $(wildcard *.cpp)
EXES := $(patsubst %.cpp,%,$(SRCS))
CPPFLAGS := -O3

.PHONY: all

all: $(EXES)

%: %.cpp
	g++ -o $@ $< $(CPPFLAGS)

.PHONY: clean

clean:
	rm $(EXES)