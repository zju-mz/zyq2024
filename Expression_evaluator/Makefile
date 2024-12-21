CXX = g++
CXXFLAGS = -O2 -Wall

LATEX = xelatex

SORT_TARGET = SORT
REPORT_TARGET = report

all: $(SORT_TARGET) $(REPORT_TARGET).pdf

$(SORT_TARGET): c.cpp expression_evaluator.h
	$(CXX) $(CXXFLAGS) -o $@ main.cpp

$(REPORT_TARGET).pdf: $(REPORT_TARGET).tex
	$(LATEX) $(REPORT_TARGET).tex
	$(LATEX) $(REPORT_TARGET).tex

run: $(SORT_TARGET)
	./$(SORT_TARGET)
report: $(REPORT_TARGET).pdf

clean:
	rm -f $(SORT_TARGET) $(REPORT_TARGET).aux $(REPORT_TARGET).log $(REPORT_TARGET).out $(REPORT_TARGET).toc $(REPORT_TARGET).pdf

.PHONY: run clean
