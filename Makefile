CXX = g++
CXXFLAGS = -std=c++11 -g -Wall 


OBJECTS = myshell.o parse.o 

myshell:  $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) *.o main final myshell
