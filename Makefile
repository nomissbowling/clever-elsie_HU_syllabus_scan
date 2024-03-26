OPT=-finput-charset=utf-8 -fexec-charset=utf-8 -std=c++2a
MAIN=src/main.cpp
MAINP=src/main.py
BACK=src/bin/backend.cpp
INTR=src/bin/interactive.cpp
MKSH=src/make.sh
release: $(MAIN) $(MAINP) $(BACK) $(INTR) $(MKSH) 
	./$(MKSH)
	g++ $(MAIN) -o main $(BACK) $(INTR) $(OPT)
	./main
