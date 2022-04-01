tcpserver: main.o logic_server.o logic_response.o
	gcc main.o logic_server.o logic_response.o -lm -o tcpserver -pthread

main.o: main.c
	gcc main.c -lm -c

logic_server.o: logic_server.c logic_server.h
	gcc logic_server.c -lm -c

logic_response.o: logic_response.c logic_response.h
	gcc logic_response.c -lm -c
