Scheduling: driver.o Coach.o
	g++ -o Scheduling driver.o Coach.o Node.o Player.o

driver.o: driver.cpp Coach.h
	g++ -c -Wall -Werror -pedantic driver.cpp

Coach.o: Coach.cpp Coach.h Node.o
	g++ -c -Wall -Werror -pedantic Coach.cpp

Node.o: Node.cpp Node.h Player.o
	g++ -c -Wall -Werror -pedantic Node.cpp

Player.o: Player.cpp Player.h
	g++ -c -Wall -Werror -pedantic Player.cpp