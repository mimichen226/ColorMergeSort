CMP = g++
CLASS1 = color-rgb
CLASS2 = display
MAIN = final
GFX = gfx
EXEC = color

$(EXEC): $(CLASS2).o $(CLASS1).o $(MAIN).o $(GFX).o
	$(CMP) -std=c++11 -lX11 $(CLASS2).o $(CLASS1).o $(MAIN).o $(GFX).o -o $(EXEC)

$(CLASS1).o: $(CLASS1).cpp $(CLASS1).h
	$(CMP) -std=c++11 -c $(CLASS1).cpp -o $(CLASS1).o

$(CLASS2).o: $(CLASS2).cpp $(CLASS2).h $(CLASS1).h
	$(CMP) -std=c++11 -c $(CLASS2).cpp -o $(CLASS2).o


$(MAIN).o: $(MAIN).cpp $(CLASS1).h $(CLASS2).h
	$(CMP) -std=c++11 -c $(MAIN).cpp -o $(MAIN).o

clean:
	rm $(CLASS1).o $(MAIN).o $(CLASS2).o
	rm $(EXEC)

