OPT=-finput-charset=utf-8 -fexec-charset=utf-8 -std=c++2a
MAIN=src/main.cpp
MAINP=src/main.py
BACK=src/bin/backend.cpp
INTR=src/bin/interactive.cpp

build: $(MAIN) $(MAINP) $(BACK) $(INTR)
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
	g++ $(MAIN) -o main $(BACK) $(INTR) $(OPT)
	./main
run:$(MAIN) $(MAINP) $(BACK) $(INTR)
	g++ $(MAIN) -o main $(BACK) $(INTR) $(OPT)
	./main