CXX=$(TOOLPREFIX)g++
FLAGS=-Wall -g -c -std=c++17
OUTDIR=dist

TF=-I./vendor/tf/include -L./vendor/tf/lib

all: $(OUTDIR)/main

$(OUTDIR)/main: src/main.cpp | $(OUTDIR) 
	$(CXX) $(TF) -Wall -g -std=c++17 -o $@ $^ -ltensorflow

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR)

run: all
	./$(OUTDIR)/main
