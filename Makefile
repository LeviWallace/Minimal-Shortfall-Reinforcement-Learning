CXX=$(TOOLPREFIX)g++
FLAGS=-Wall -g -c -std=c++17

SRCDIR=src
OUTDIR=dist

all: $(OUTDIR)

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OUTDIR)/%.o, $(SRCS))

TARGET=msrl

all: run

test:
	echo $(TARGET)

build: $(OBJS) | $(OUTDIR)
	$(CXX) -Wall -g -std=c++17 -o $(TARGET) $(OBJS)  -ltensorflow

$(OUTDIR)/%.o: $(SRCDIR)/%.cpp | $(OUTDIR)
	$(CXX) $(FLAGS) -o $@ $<

create:
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR) $(TARGET)

run: create build	
	./msrl
