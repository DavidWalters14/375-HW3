Q=submission
FLAGS=g++ -Wall -Wextra -std=c++14 -g -DDEBUG

all: $(Q)
	./$(Q) mediumInput.txt mediumOutputBacktracking.txt 2

$(Q): $(Q).o
	$(FLAGS) -o $(Q) $(Q).o
$(Q).o: $(Q).cpp
	$(FLAGS) -c $(Q).cpp

run: all
	./$(Q) input.txt output.txt

clean: all
	rm -rf $(Q) *.o
