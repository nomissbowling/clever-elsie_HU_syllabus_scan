OPT=-finput-charset=utf-8 -fexec-charset=utf-8 -std=c++2a
MAIN=src/main.cpp
MAINP=src/main.py

CFL = $(BKE) $(ITR)

build: $(MAIN) $(MAINP)
	cd ~ && sudo apt update
	cd ~ && sudo apt upgrade
	cd ~ && sudo apt install build-essential
	cd ~ && sudo apt install python3 -y
	python3 -m pip install --upgrade pip
	python3 -m pip install requests
	python3 -m pip install beautifulsoup4
	@if [ -d syll ]; then \
		rm -rf syll; \
	fi
	mkdir syll
	python3 $(MAINP)
	g++ $(OPT) $(MAIN) -o main
	$(MAKE) test
./main: $(MAIN)
	g++ $(OPT) $(MAIN) -o main

run: ./main
	./main 1

test:$(MAIN)
	./main
