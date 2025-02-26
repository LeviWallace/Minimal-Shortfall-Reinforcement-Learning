CXX=$(TOOLPREFIX)g++
FLAGS=-Wall -g -c -std=c++17
OUTDIR=dist

all: $(OUTDIR)/main

$(OUTDIR)/main: src/main.cpp | $(OUTDIR) 
	$(CXX) -Wall -g -std=c++17 -o $@ $^

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR)

run: all
	./$(OUTDIR)/main
