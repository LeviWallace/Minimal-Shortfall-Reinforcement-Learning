CXX=$(TOOLPREFIX)g++
FLAGS=-Wall -g -c -std=c++17
TF=-I./vendor/tf/include -L./vendor/tf/lib

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
	$(CXX) $(TF) -Wall -g -std=c++17 -o $(TARGET) $(OBJS)  -ltensorflow

$(OUTDIR)/%.o: $(SRCDIR)/%.cpp | $(OUTDIR)
	$(CXX) $(FLAGS) $(TF) -o $@ $<

create:
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR) $(TARGET)

run: create build	
	./msrl
