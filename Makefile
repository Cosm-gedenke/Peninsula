PORT=8080
SERVER=./peninsula
all: 
	gcc -o peninsula ErrorT.c Connection/clientIP.c Connection/rawhttp.c  transportlayer/tcp.c Requestparsing/request.c Requestparsing/parsing.c conf/parseconfig.c  peninsula.c
